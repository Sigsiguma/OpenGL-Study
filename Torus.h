//
//  Torus.hpp
//  OpenGL-Study
//
//  Created by  Siguma Rin on 2017/04/16.
//  Copyright © 2017年  Siguma Rin. All rights reserved.
//

#ifndef Torus_hpp
#define Torus_hpp

#include <vector>
#include "Utility.h"


class Torus {
public:
    Torus(unsigned int row, unsigned int column, float pipeRadius, float torusRadius);

    std::vector<Vector3> vertexPos_;
    std::vector<Vector3> normal_;
    std::vector<Color> vertexColor_;
    std::vector<unsigned short> vertexIndex_;
};


#endif /* Torus_hpp */
