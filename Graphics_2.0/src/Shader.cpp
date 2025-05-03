// Shader.cpp
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

static std::string readFile(const char* path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

Shader::Shader(const char* vPath, const char* fPath)
    : Shader(vPath, fPath, nullptr) {}

Shader::Shader(const char* vPath, const char* fPath, const char* gPath) {
    std::string vCode = readFile(vPath);
    std::string fCode = readFile(fPath);

    const char* vShaderCode = vCode.c_str();
    const char* fShaderCode = fCode.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    unsigned int geometry;
    if (gPath) {
        std::string gCode = readFile(gPath);
        const char* gShaderCode = gCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, nullptr);
        glCompileShader(geometry);
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if (gPath) glAttachShader(ID, geometry);
    glLinkProgram(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (gPath) glDeleteShader(geometry);
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::setMat4(const std::string& name, const float* value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
}
