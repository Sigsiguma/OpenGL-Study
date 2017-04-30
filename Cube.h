//
// Created by  Siguma Rin on 2017/04/30.
//

#ifndef OPENGL_CUBE_H
#define OPENGL_CUBE_H

#include <vector>
#include "Utility.h"

class Cube {
public:
    Cube(float side);

    std::vector<Vector3> vertexPos_;
    std::vector<Vector3> normal_;
    std::vector<Color> vertexColor_;
    std::vector<float> texCoord_;
    std::vector<unsigned short> vertexIndex_;
};
#endif //OPENGL_CUBE_H
