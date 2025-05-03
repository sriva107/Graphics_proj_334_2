// src/main.cpp
#include <GL/freeglut.h>
#include <iostream>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

Camera camera;
float lastX = 400, lastY = 300;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Shader* modelShader;
Shader* edgeShader;
Model* model;

void display() {
    float currentFrame = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float view[16];
    camera.GetViewMatrix(view);

    float projection[16];
    float fov = 45.0f;
    float aspect = 800.0f / 600.0f;
    float near = 0.1f, far = 100.0f;
    float f = 1.0f / tan(fov * 0.5f * 3.141592f / 180.0f);

    projection[0] = f / aspect;
    projection[1] = projection[2] = projection[3] = 0;
    projection[5] = f;
    projection[4] = projection[6] = projection[7] = 0;
    projection[8] = projection[9] = 0;
    projection[10] = (far + near) / (near - far);
    projection[11] = -1.0f;
    projection[12] = projection[13] = 0;
    projection[14] = (2 * far * near) / (near - far);
    projection[15] = 0.0f;

    modelShader->use();
    modelShader->setMat4("view", view);
    modelShader->setMat4("projection", projection);
    modelShader->setMat4("model", new float[16]{1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, -1.0f, 0, 1});
    model->draw();

    edgeShader->use();
    edgeShader->setMat4("view", view);
    edgeShader->setMat4("projection", projection);
    edgeShader->setMat4("model", new float[16]{1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, -1.0f, 0, 1});
    model->draw();

    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);

    if (key == 'w') camera.ProcessKeyboard(FORWARD, deltaTime);
    if (key == 's') camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (key == 'a') camera.ProcessKeyboard(LEFT, deltaTime);
    if (key == 'd') camera.ProcessKeyboard(RIGHT, deltaTime);
}

void motion(int x, int y) {
    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void initGL() {
    glewInit();
    glEnable(GL_DEPTH_TEST);

    modelShader = new Shader("assets/shaders/model.vert", "assets/shaders/model.frag");
    edgeShader = new Shader("assets/shaders/edge.vert", "assets/shaders/edge.frag", "assets/shaders/edge.geom");
    model = new Model("assets/models/teapot.obj");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Contour Shading with FreeGLUT");

    initGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(motion);

    glutMainLoop();
    return 0;
}
