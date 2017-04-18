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

class Torus {
public:
    Torus(unsigned int row, unsigned int column, unsigned int pipeRadius, unsigned int torusRadius);

    std::vector<float> vertexColor_;
    std::vector<float> vertexPos_;
    std::vector<unsigned short> vertexIndex_;
    
private:
    std::vector<float> hsva2rgb(int h, float s, float v, float a);
};

#endif /* Torus_hpp */
