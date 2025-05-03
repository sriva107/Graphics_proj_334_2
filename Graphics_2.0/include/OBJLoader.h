#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};

class OBJLoader {
public:
    static bool load(const std::string& path, std::vector<Vertex>& outVertices);
};
