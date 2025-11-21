#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream infile("images.txt");
    if (!infile) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    int depth, height, width;
    infile >> depth >> height >> width;

    size_t total_size = depth * height * width;
    std::vector<float> volume(total_size);

    for (size_t i = 0; i < total_size; ++i)
        infile >> volume[i];
    infile.close();

    std::cout << "Loaded volume with dimensions: " << depth << " x " << height << " x " << width << std::endl;

    

    return 0;
}