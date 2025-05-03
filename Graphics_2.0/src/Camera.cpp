// ===== src/Camera.cpp =====
#include "Camera.h"

Camera::Camera() {
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = -90.0f;
    pitch = 0.0f;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::processInput(unsigned char key) {
    float speed = 0.1f;
    if (key == 'w') position += speed * front;
    if (key == 's') position -= speed * front;
    if (key == 'a') position -= glm::normalize(glm::cross(front, up)) * speed;
    if (key == 'd') position += glm::normalize(glm::cross(front, up)) * speed;
}
