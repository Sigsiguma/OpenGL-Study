//
// Created by  Siguma Rin on 2017/04/30.
//

#include "FrameBuffer.h"
#include <iostream>

FrameBuffer::FrameBuffer(int width, int height) : frameWidth_(width), frameHeight_(height),
                                                  frameBuffer_([]() {
                                                      GLuint buffer;
                                                      glGenFramebuffers(1, &buffer);
                                                      return buffer;
                                                  }()),
                                                  depthRenderBuffer_([]() {
                                                      GLuint buffer;
                                                      glGenRenderbuffers(1, &buffer);
                                                      return buffer;
                                                  }()),
                                                  frameTexture_([]() {
                                                      GLuint tex;
                                                      glGenTextures(1, &tex);
                                                      return tex;
                                                  }()) {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, frameWidth_, frameHeight_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer_);
    glBindTexture(GL_TEXTURE_2D, frameTexture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, frameWidth_, frameHeight_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexture_, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Error FrameBuffer" << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
