import matplotlib.pyplot as plt
from PIL import Image

from torchvision.transforms import transforms
from torchvision.datasets import ImageFolder

import torch
from torch.utils.data import DataLoader

import torchvision

import torch.nn.functional as F
from torch import nn

from tqdm.auto import tqdm

transform = transforms.Compose([transforms.Resize((224, 224)), transforms.ToTensor()])

# Create data loaders for training and testing datasets
#train_image_path = r"D:\Anaconda Projects\anomaly_detection\carpet\train"
#r"D:\Anaconda Projects\anomaly_detection\carpet\train\good\000.png"

good_dataset = ImageFolder(root=r"D:\Anaconda Projects\anomaly_detection\carpet\train", transform=transform)

BS = 16
train_dataset, test_dataset = torch.utils.data.random_split(good_dataset, [0.8, 0.2])

train_loader = DataLoader(train_dataset, batch_size=BS, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=BS, shuffle=True)

class Autoencoder(nn.Module):
    def __init__(self):
        super(Autoencoder, self).__init__()
    
        self.encoder = nn.Sequential(
            nn.Conv2d(3, 128, kernel_size=4),
            nn.ReLU(),
            nn.AvgPool2d(kernel_size=2, stride=2),
            nn.Conv2d(128, 256, kernel_size=4),
            nn.ReLU(),
            nn.AvgPool2d(kernel_size=2, stride=2),
            nn.Conv2d(256, 256, kernel_size=3),
            nn.ReLU(),
            nn.AvgPool2d(kernel_size=2, stride=2)
        )
        self.decoder = nn.Sequential(
            nn.ConvTranspose2d(256, 256, kernel_size=4, stride=2, output_padding=1),
            nn.ReLU(),
            nn.ConvTranspose2d(256, 128, kernel_size=5, stride=2, output_padding=1),
            nn.ReLU(),
            nn.ConvTranspose2d(128, 3, kernel_size=5, stride=2, output_padding=1),
            nn.Sigmoid()
        )

    def forward(self, x):
        x = self.encoder(x)
        x = self.decoder(x)
        return x

# Test the Autoencoder:
model = Autoencoder()
input_image = torch.randn(1, 3, 224, 224)
output_image = model(input_image)
print(output_image.shape)

# Load the model:
"""
ckpoints = torch.load("simple_autoencoder_12_loss.pth")
model.load_state_dict(ckpoints)
"""

# ---Training:---
model.cuda()

# Define loss Function and optimizer:
criterion = torch.nn.MSELoss()
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

# Define list to store training loss and validation loss:
Loss = []
Validation_Loss = []

num_epochs = 100

for epoch in tqdm(range(num_epochs)):
    model.train()
    for img, _ in train_loader:
        img = img.cuda()
        output = model(img)
        loss = criterion(output, img)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
    Loss.append(loss.item())

    # Calculate validation loss:
    model.eval()
    with torch.no_grad():
        val_loss_sum = 0.0
        num_batches = 0
        for img, _ in test_loader:
            img = img.cuda()
            output = model(img)
            val_loss = criterion(output, img)
            val_loss_sum += val_loss.item()
            num_batches += 1
        val_loss_avg = val_loss_sum / num_batches
        Validation_Loss.append(val_loss_avg)

    if epoch % 5 == 0:
        print("Epoch [{}/{}], Loss: {:.4f}, Validation Loss: {:.4f}".format(epoch + 1, num_epochs, loss.item(), val_loss_avg))

plt.plot(Loss, label="Training Loss")
plt.plot(Validation_Loss, label="Validation Loss")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.legend()
plt.show()

# Save the model:
torch.save(model.state_dict(), "simple_autoencoder_12_loss.pth")
model.eval()