//
//  Torus.cpp
//  OpenGL-Study
//
//  Created by  Siguma Rin on 2017/04/16.
//  Copyright © 2017年  Siguma Rin. All rights reserved.
//

#include "Torus.h"

Torus::Torus(unsigned int row, unsigned int column, unsigned int pipeRadius, unsigned int torusRadius) {
    for (int i = 0; i <= row; ++i) {
        double r = M_PI * 2 / row * i;
        double rr = cos(r);
        double ry = sin(r);
        for (int ii = 0; ii <= column; ++ii) {
            double tr = M_PI * 2 / column * ii;
            double tx = (rr * pipeRadius + torusRadius) * cos(tr);
            double ty = ry * pipeRadius;
            double tz = (rr * pipeRadius + torusRadius) * sin(tr);
            vertexPos_.emplace_back(tx, ty, tz);
            Color colors = hsva2rgb(360 / column * ii, 1, 1, 1);
            vertexColor_.emplace_back(colors);
        }
    }

    for (int i = 0; i < row; ++i) {
        for (int ii = 0; ii < column; ++ii) {
            int r = (column + 1) * i + ii;
            vertexIndex_.emplace_back(r);
            vertexIndex_.emplace_back(r + column + 1);
            vertexIndex_.emplace_back(r +1);
            vertexIndex_.emplace_back(r + column + 1);
            vertexIndex_.emplace_back(r + column + 2);
            vertexIndex_.emplace_back(r + 1);
        }
    }
}

Color Torus::hsva2rgb(int h, float s, float v, float a) {
    if (s > 1 || v > 1 || a > 1) { return Color(1, 1, 1, 1); }

    float th = h % 360;
    int i = static_cast<int>(floor(th / 60));
    float f = th / 60 - i;
    float m = v * (1 - s);
    float n = v * (1 - s * f);
    float k = v * (1 - s * (1 - f));

    std::vector<float> r = {v, n, m, m, k, v};
    std::vector<float> g = {k, v, v, n, m, m};
    std::vector<float> b = {m, m, k, v, v, n};
    return Color(r[i], g[i], b[i], a);
}
