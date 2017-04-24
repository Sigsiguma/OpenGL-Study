//
// Created by  Siguma Rin on 2017/04/24.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <string>
#include <opencv/cv.h>
#include <highgui.h>
#include <GL/glew.h>

class Texture {
public:
    Texture(std::string imgPath);

    GLuint GetTexture() {
        return texture_;
    }

    void ParameterSet(GLenum pname, GLint param);

private:
    cv::Mat img_;
    GLuint texture_;
};

#endif //OPENGL_TEXTURE_H
