//
// Created by  Siguma Rin on 2017/04/17.
//

#ifndef OPENGL_PROGRAMOBJECTCREATOR_H
#define OPENGL_PROGRAMOBJECTCREATOR_H

#include <GL/glew.h>
#include <vector>

class ProgramObjectCreator {
public:
    ProgramObjectCreator(const char *vert, const char *frag);

    GLuint GetProgramObject() const {
        return programObject_;
    }

private:
    bool readShaderSource(const char *name, std::vector<GLchar> &buffer);

    GLuint createProgram(const char *vsrc, const char *fsrc);

    GLboolean printProgramInfoLog(GLuint program);

    GLboolean printShaderInfoLog(GLuint shader, const char *str);

    GLuint programObject_;
};

#endif //OPENGL_PROGRAMOBJECTCREATOR_H
