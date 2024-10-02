#include <iostream>
#include <fstream>
#include <vector>

struct Vertex {
    float x, y, z;
};

bool readPLY(const std::string& filename, std::vector<Vertex>& vertices) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("element vertex") != std::string::npos) {
            size_t pos = line.find("vertex") + 7;
            size_t vertexCount = std::stoi(line.substr(pos));
            vertices.reserve(vertexCount);
        } else if (line.find("end_header") != std::string::npos) {
            break;
        }
    }

    while (std::getline(file, line)) {
        Vertex vertex;
        sscanf(line.c_str(), "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
        vertices.push_back(vertex);
    }

    file.close();
    return true;
}

int main() {
    std::vector<Vertex> vertices;
    if (!readPLY("/home/djoser/Documents/M2_MOSIG/Computer_Graphics/BVH_TP/viewer/models/teapot_wt.ply", vertices)) {
        std::cerr << "Error reading PLY file" << std::endl;
        return 1;
    }

    std::cout << "Read " << vertices.size() << " vertices" << std::endl;
    return 0;
}
