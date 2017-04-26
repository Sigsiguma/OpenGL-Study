//
// Created by  Siguma Rin on 2017/04/18.
//

#ifndef OPENGL_UTILITY_H
#define OPENGL_UTILITY_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Vector3 {
public:
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {

    }

private:
    float x;
    float y;
    float z;
};

class Color {
public:
    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

private:
    float r;
    float g;
    float b;
    float a;
};

namespace Util {
    double calcFPS(GLFWwindow *window, double theTimeInterval, std::string theWindowTitle);

    GLuint createIBO(GLsizeiptr size, GLvoid *data);

    Color hsva2rgb(float h, float s, float v, float a);
}


#endif //OPENGL_UTILITY_H
