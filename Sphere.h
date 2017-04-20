//
// Created by  Siguma Rin on 2017/04/20.
//

#ifndef OPENGL_SPHERE_H
#define OPENGL_SPHERE_H

#include "Utility.h"
#include <vector>

class Sphere {

public:
    Sphere(unsigned int row, unsigned int column, float rad);

    std::vector<Vector3> vertexPos_;
    std::vector<Vector3> normal_;
    std::vector<Color> vertexColor_;
    std::vector<unsigned short> vertexIndex_;
};

#endif //OPENGL_SPHERE_H
