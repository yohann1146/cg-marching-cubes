import numpy as np
import random

# Load npz archive
data = np.load('adrenalmnist3d.npz')
# ['train_images', 'val_images', 'test_images', 'train_labels', 'val_labels', 'test_labels'] 

#4d array of images
imgs=data['train_images']
label=data['train_labels']

#selecting a random image
num_imgs = imgs.shape[0]
random_index = random.randint(0, num_imgs - 1)
print(f"Selecting random image #{random_index}")

volume=imgs[random_index]
flat_volume = volume.flatten()
with open('images.txt', 'w') as f:
    # Write dimensions first
    f.write(f"{volume.shape[0]} {volume.shape[1]} {volume.shape[2]}\n")
    # Write volume data
    for v in flat_volume:
        f.write(f"{v:.6f}\n")