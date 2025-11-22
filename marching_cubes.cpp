#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Gradient {
    float x, y, z;
};

class VolumeData {
private:
    std::vector<float> volume;
    std::vector<Gradient> gradients;
    int depth, height, width;

public:
    VolumeData(int d, int h, int w) : depth(d), height(h), width(w) {
        volume.resize(d * h * w);
        gradients.resize(d * h * w);
    }

    void read_img_txt(std::string filepath)
    {
        std::ifstream infile(filepath);
        if (!infile) {
            std::cerr << "Error opening file\n";
            return;
        }

        infile >> depth >> height >> width;
        size_t total_size = depth * height * width;
        volume.resize(total_size);

        for (size_t i = 0; i < total_size; ++i)
            infile >> volume[i];
        infile.close();
        std::cout << "Loaded volume with dimensions: " << depth << " x " << height << " x " << width << std::endl;
    }   

    float getValue(int x, int y, int z) const {
        if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth)
            return 0.0f;
        return volume[z * (height * width) + y * width + x];
    }

    Gradient getGradient(int x, int y, int z) const {
        if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth)
            return {0.0f, 0.0f, 0.0f};
        return gradients[z * (height * width) + y * width + x];
    }

    //preprocess 1
    void computeGradients() {
        std::cout << "Computing gradients using central differences..." << std::endl;
        
        for (int z = 0; z < depth; ++z) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int idx = z * (height * width) + y * width + x;

                    float gx = (getValue(x+1, y, z) - getValue(x-1, y, z)) / 2.0f;
                    float gy = (getValue(x, y+1, z) - getValue(x, y-1, z)) / 2.0f;
                    float gz = (getValue(x, y, z+1) - getValue(x, y, z-1)) / 2.0f;
                    
                    gradients[idx].x = gx;
                    gradients[idx].y = gy;
                    gradients[idx].z = gz;
                }
            }
        }
    }

    //preprocess 2
    void normalizeGradients() {
        std::cout << "Normalizing gradients to unit normals..." << std::endl;
        
        for (size_t i = 0; i < gradients.size(); ++i) {
            float magnitude = std::sqrt(gradients[i].x * gradients[i].x +
                                       gradients[i].y * gradients[i].y +
                                       gradients[i].z * gradients[i].z);
            
            // Avoid division by zero
            if (magnitude > 1e-6f) {
                gradients[i].x /= magnitude;
                gradients[i].y /= magnitude;
                gradients[i].z /= magnitude;
            } else {
                // Set to zero vector if magnitude is too small
                gradients[i].x = 0.0f;
                gradients[i].y = 0.0f;
                gradients[i].z = 0.0f;
            }
        }
    }

    //get funcs
    int getDepth() const { return depth; }
    int getHeight() const { return height; }
    int getWidth() const { return width; }
    const std::vector<float>& getVolume() const { return volume; }
    const std::vector<Gradient>& getGradients() const { return gradients; }
};


int main() {
    //initializing...
    VolumeData volumeData(0, 0, 0);
    volumeData.read_img_txt("selected_volume.txt");

    volumeData.computeGradients();
    volumeData.normalizeGradients();

    std::cout << "\nPreprocessing complete!" << std::endl;

    //IMPLEMENT MARCHING CUBES

    return 0;
}