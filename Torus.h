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
#include <cmath>
#include "CommonData.h"

class Torus {
public:
    Torus(unsigned int row, unsigned int column, unsigned int pipeRadius, unsigned int torusRadius);

    std::vector<Color> vertexColor_;
    std::vector<Vector3> vertexPos_;
    std::vector<unsigned int> vertexIndex_;
    
private:
    Color hsva2rgb(int h, double s, double v, double a);
};

#endif /* Torus_hpp */
