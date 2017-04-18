//
//  Torus.cpp
//  OpenGL-Study
//
//  Created by  Siguma Rin on 2017/04/16.
//  Copyright © 2017年  Siguma Rin. All rights reserved.
//

#include "Torus.h"

Torus::Torus(unsigned int row, unsigned int column, unsigned int pipeRadius, unsigned int torusRadius) {
        for(int i = 0; i <= row; ++i) {
            double r = M_PI * 2 / row * i;
            double rr = cos(r);
            double ry = sin(r);
            for(int ii = 0; ii <= column; ++ii) {
                double tr = M_PI * 2 / column * ii;
                double tx = (rr * pipeRadius + torusRadius) * cos(tr);
                double ty = ry * pipeRadius;
                double tz = (rr * pipeRadius + torusRadius) * sin(tr);
                vertexPos_.emplace_back(tx, ty, tz);
                vertexColor_.push_back(hsva2rgb(360 / column * ii, 1, 1, 1));
            }
        }
    
    for(int i = 0; i < row; ++i) {
        for(int ii = 0; ii < column; ++ii) {
            double r = (column + 1) * i + ii;
            vertexIndex_.push_back(r);
            vertexIndex_.push_back(r + column +1);
            vertexIndex_.push_back(r + 1);
            vertexIndex_.push_back(r + column + 1);
            vertexIndex_.push_back(r + column + 2);
            vertexIndex_.push_back(r + 1);
        }
    }
}

Color Torus::hsva2rgb(int h, double s, double v, double a) {
    if(s > 1 || v > 1 || a > 1) {return Color(1, 1, 1, 1);}
    
    double th = h % 360;
    double i = floor(th / 60);
    double f = th / 60 - i;
    double m = v * (1 -s);
    double n = v * (1 - s * f);
    double k = v * (1 -s * (1- f));
    
    std::vector<double> r = { v, n, m, m, k, v};
    std::vector<double> g = { k, v, v, n, m, m};
    std::vector<double> b = { m, m, k, v, v, n};
    return Color(r[i], g[i], b[i], a);
}
