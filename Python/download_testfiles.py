import urllib.request
import tarfile

# "carpet": "https://www.mydrive.ch/shares/38536/3830184030e49fe74747669442f0f282/download/420937484-1629951672/carpet.tar.xz"

#urllib.request.urlretrieve("https://www.mydrive.ch/shares/38536/3830184030e49fe74747669442f0f282/download/420937484-1629951672/carpet.tar.xz")
import os

print("Current working directory:", os.getcwd())
with tarfile.open("carpet.tar.xz") as f:
    f.extractall('.')