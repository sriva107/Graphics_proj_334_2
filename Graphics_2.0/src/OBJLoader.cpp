#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

bool OBJLoader::load(const std::string& path, std::vector<Vertex>& outVertices) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return false;
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> vertexIndices, normalIndices;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            glm::vec3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        } else if (prefix == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (prefix == "f") {
            unsigned int vi[3], ni[3];
            char slash;
            for (int i = 0; i < 3; ++i) {
                ss >> vi[i] >> slash >> slash >> ni[i];
                vertexIndices.push_back(vi[i] - 1);
                normalIndices.push_back(ni[i] - 1);
            }
        }
    }

    outVertices.clear();
    for (size_t i = 0; i < vertexIndices.size(); ++i) {
        Vertex v;
        v.position = positions[vertexIndices[i]];
        v.normal = normals[normalIndices[i]];
        outVertices.push_back(v);
    }

    return true;
}
