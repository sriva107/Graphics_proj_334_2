// src/Model.cpp
#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>

Model::Model(const std::string& path) {
    loadOBJ(path);
}

void Model::draw() const {
    for (const auto& mesh : meshes)
        mesh.draw();
}

void Model::loadOBJ(const std::string& path) {
    std::vector<float> positions;
    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;

    std::ifstream file(path);
    if (!file) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            positions.push_back(x);
            positions.push_back(y);
            positions.push_back(z);
        }
        else if (type == "f") {
            unsigned int idx[3];
            for (int i = 0; i < 3; ++i) {
                std::string vertexStr;
                iss >> vertexStr;
                std::istringstream vss(vertexStr);
                std::string indexStr;
                std::getline(vss, indexStr, '/'); // Only position index
                idx[i] = std::stoi(indexStr) - 1;
            }
            indices.push_back(idx[0]);
            indices.push_back(idx[1]);
            indices.push_back(idx[2]);
        }
    }

    vertices.resize(positions.size() / 3);
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].position[0] = positions[i * 3 + 0];
        vertices[i].position[1] = positions[i * 3 + 1];
        vertices[i].position[2] = positions[i * 3 + 2];
    }

    meshes.emplace_back(vertices, indices);
}
