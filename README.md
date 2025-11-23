# Computer Graphics Project
Implementing the marching cubes algorithm in CPP/OpenGL.

# How to run:
1) Download .npz file online
2) Run dataset.py
3) Compile & run marching_cubes.cpp:`
g++ marching_cubes.cpp -o marching_cubes.exe
`

## Step 1: Reading Datasets
1) Downloaded MedMNIST 3d adrenal image dataset.
2) Extracted one of the images into a numpy array and converted to .txt
3) .txt file is read by CPP into a vector

## Step 2: Image-preprocessing
Compute and normalize the gradients.

## Step 3: Algorithm
Implemented the marching cubes algorithm to compute mesh vertices.

## Step 4: Visualization
Writing the vertices to `output.off` mesh.

