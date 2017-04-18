//
// Created by  Siguma Rin on 2017/04/18.
//

#ifndef OPENGL_VBO_H
#define OPENGL_VBO_H

#include <GL/glew.h>

class VBO {
public:
    VBO(GLsizeiptr vertexSize, const GLvoid* data);

    void SetAttrib(int attLocation, int attSize);

private:
    GLuint vbo_;
};

#endif //OPENGL_VBO_H
