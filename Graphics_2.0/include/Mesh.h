// include/Mesh.h
#pragma once
#include <vector>
#include <GL/freeglut.h>

struct Vertex {
    float position[3];
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void draw() const;
private:
    unsigned int VAO, VBO, EBO;
    unsigned int indexCount;
};
