//
// Created by  Siguma Rin on 2017/04/18.
//

#include "VBO.h"

VBO::VBO(GLsizeiptr vertexSize, const GLvoid *vertexData) {
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::SetAttrib(int attLocation, int attSize) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glVertexAttribPointer(attLocation, attSize, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attLocation);
}

