//
// Created by  Siguma Rin on 2017/04/18.
//

#ifndef OPENGL_UTILITY_H
#define OPENGL_UTILITY_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Util {
    double calcFPS(GLFWwindow *window, double theTimeInterval, std::string theWindowTitle);

    GLuint createIBO(GLsizeiptr size, GLvoid *data);
}
#endif //OPENGL_UTILITY_H