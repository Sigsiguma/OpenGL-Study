//
// Created by  Siguma Rin on 2017/04/30.
//

#ifndef OPENGL_FRAMEBUFFER_H
#define OPENGL_FRAMEBUFFER_H

#include <GL/glew.h>

class FrameBuffer {
public:
   FrameBuffer(int width, int height);

    const GLuint frameBuffer_;
    const GLuint depthRenderBuffer_;
    const GLuint frameTexture_;

    const int frameWidth_;
    const int frameHeight_;
};

#endif //OPENGL_FRAMEBUFFER_H
