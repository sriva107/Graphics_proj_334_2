// We'll begin with core source and header files:

// ===== include/Camera.h =====
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position, front, up;
    float yaw, pitch;
    Camera();
    glm::mat4 getViewMatrix();
    void processInput(unsigned char key);
};
