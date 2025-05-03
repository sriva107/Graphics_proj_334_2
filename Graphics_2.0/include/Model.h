// include/Model.h
#pragma once

#include "Vec3.h"
#include <vector>
#include <string>
#include <GL/freeglut.h>

class Model {
public:
    Model(const std::string& path);
    void draw() const;

private:
    std::vector<Vec3> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;

    void loadOBJ(const std::string& path);
    void setupBuffers();
};
