//
//  CommonData.hpp
//  OpenGL-Study
//
//  Created by  Siguma Rin on 2017/04/16.
//  Copyright © 2017年  Siguma Rin. All rights reserved.
//

#ifndef CommonData_hpp
#define CommonData_hpp

class Vector3 {
public:
    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
    
    double x;
    double y;
    double z;
};

class Color {
public:
    Color(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}
    
    double r;
    double g;
    double b;
    double a;
};

#endif /* CommonData_hpp */
