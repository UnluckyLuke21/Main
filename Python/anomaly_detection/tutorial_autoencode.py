import matplotlib.pyplot as plt
from PIL import Image

from torchvision.transforms import transforms
from torchvision.datasets import ImageFolder

import torch
from torch.utils.data import DataLoader

import torchvision

import torch.nn.functional as F
from torch import nn

transform = transforms.Compose([transforms.Resize((224, 224)), transforms.ToTensor()])

input_image = Image.open(r"D:\Anaconda Projects\anomaly_detection\carpet\train\good\000.png")
input_image = transform(input_image)

print(input_image.shape)

input_image = input_image.unsqueeze(0) # Add extra dimension for representing batch size
print(input_image.shape)

c1 = nn.Conv2d(in_channels=3, out_channels=128, kernel_size=4)
x = c1(input_image)
print(x.shape)

ap1 = nn.AvgPool2d(kernel_size=2, stride=2)
x = ap1(x)
print(x.shape)

c2 = nn.Conv2d(in_channels=128, out_channels=256, kernel_size=4)
ap2 = nn.AvgPool2d(kernel_size=2, stride=2)
x = ap2(c2(x))
print(x.shape)

c3 = nn.Conv2d(in_channels=256, out_channels=256, kernel_size=3)
ap3 = nn.AvgPool2d(kernel_size=2, stride=2)
x = ap3(c3(x))
print(x.shape)

# Now scale up again

c4 = nn.ConvTranspose2d(in_channels=256, out_channels=256, kernel_size=4, stride=2, output_padding=1)
x = c4(x)
print(x.shape)

c5 = nn.ConvTranspose2d(in_channels=256, out_channels=128, kernel_size=5, stride=2, output_padding=1)
x = c5(x)
print(x.shape)

c6 = nn.ConvTranspose2d(in_channels=128, out_channels=3, kernel_size=5, stride=2, output_padding=1)
x = c6(x)
print(x.shape)