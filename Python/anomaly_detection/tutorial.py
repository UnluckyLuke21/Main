import matplotlib.pyplot as plt
from PIL import Image

from torchvision.transforms import transforms
from torchvision.datasets import ImageFolder

import torch
from torch.utils.data import DataLoader

import torchvision

#image_path = "carpet/test/hole/000.png"
#image = Image.open(image_path)
#print(image.size)

transform = transforms.Compose([transforms.Resize((224, 224)), transforms.ToTensor()])

#image = transform(image)

#print(image.shape)

#plt.imshow(image.permute(1, 2, 0))
#plt.show()

# Calculate the memory usage:
#memory_usage = image.numel() * image.element_size()
#print(f"Memory usage of the tensor: {memory_usage * 279//1024} KB")

train_image_path = "carpet/train"

good_dataset = ImageFolder(root=train_image_path, transform=transform)

x, y = good_dataset[0]
print("Image Shape:", x.shape)
print("Label: ", y)

train_dataset, test_dataset = torch.utils.data.random_split(good_dataset, [0.8, 0.2])

print("Total number of samples in the original dataset: ", len(good_dataset))
print("Number of samples in the training subset: ", len(train_dataset))
print("Number of samples in the testing subset", len(test_dataset))

# Set the Batch Size:
BS = 16

# Create Data Loaders for training and testing datasets:
train_loader = DataLoader(train_dataset, batch_size=BS, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=BS, shuffle=True)

# Get a batch of images and labels from the training loader:
image_batch, label_batch = next(iter(train_loader))

# Print the shape of the input images and labels:
print(f"Shape of input images: {image_batch.shape}")
print(f"Shape of labels: {label_batch.shape}")

# Calculate Memory usage:
memory_usage = image_batch.numel() * image_batch.element_size()

# Print Memory usage:
print(f"Memory usage of the tensor: {memory_usage//1024} KB")

# set figure size:
plt.figure(figsize=(12*4, 48*4))

grid = torchvision.utils.make_grid(image_batch[0:4], padding=5, nrow=4)
plt.imshow(grid.permute(1, 2, 0))

plt.title("Good Samples")
plt.show()

