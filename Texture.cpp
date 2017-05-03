//
// Created by  Siguma Rin on 2017/04/24.
//

#include "Texture.h"
#include <opencv2/opencv.hpp>

Texture::Texture(std::string imgPath) {
    img_ = cv::imread(imgPath, cv::IMREAD_UNCHANGED);
    cv::cvtColor(img_, img_, cv::COLOR_BGRA2RGBA);

    if(img_.data == nullptr) {
        std::cerr << "TextureData Load Error" << std::endl;
        return;
    }

    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_.cols, img_.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 img_.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::ParameterSet(GLenum pname, GLint param) {
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexParameteri(GL_TEXTURE_2D, pname, param);
    glBindTexture(GL_TEXTURE_2D, 0);
}
