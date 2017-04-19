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

class Vector3 {
public:
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {

    }

private:
    float x;
    float y;
    float z;
};

class Color {
public:
    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

private:
    float r;
    float g;
    float b;
    float a;
};

class Torus {
public:
    Torus(unsigned int row, unsigned int column, unsigned int pipeRadius, unsigned int torusRadius);

    std::vector<Vector3> vertexPos_;
    std::vector<Vector3> normal_;
    std::vector<Color> vertexColor_;
    std::vector<unsigned short> vertexIndex_;

private:
    Color hsva2rgb(int h, float s, float v, float a);
};


#endif /* Torus_hpp */
