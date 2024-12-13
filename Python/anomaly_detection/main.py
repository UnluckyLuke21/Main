import train
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

#good_dataset = ImageFolder(root=r"D:\Anaconda Projects\anomaly_detection\carpet\train", transform=transform)

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
    
model = Autoencoder()

# Load the trained model:
ckpoints = torch.load("simple_autoencoder_12_loss.pth")
model.load_state_dict(ckpoints)

with torch.no_grad():
    for data, _ in train_loader:
        data = data.cuda()
        recon = model(data)
        break

recon_error = ((data - recon) **2).mean(axis=1)
print(recon_error.shape)

plt.figure(dpi=250)
fig, ax = plt.subplots(3, 3, figsize=(5*4, 4*4))
for i in range(3):
    ax[0, i].imshow(data[i].cpu().numpy().transpose((1, 2, 0)))
    ax[1, i].imshow(recon[i].cpu().numpy().transpose((1, 2, 0)))
    ax[2, i].imshow(recon_error[i][0:-10, 0:-10].cpu().numpy(), cmap="jet", vmax=torch.max(recon_error[i]))
    ax[0, i].axis("OFF")
    ax[1, i].axis("OFF")
    ax[2, i].axis("OFF")
plt.show()