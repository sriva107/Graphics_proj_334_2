// Shader.h
#pragma once
#include <string>
#include <GL/freeglut.h>

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
    void use() const;
    void setMat4(const std::string& name, const float* value) const;
};
