//
// Created by  Siguma Rin on 2017/04/20.
//

#include "Sphere.h"
#include <cmath>

Sphere::Sphere(unsigned int row, unsigned int column, float rad) {

    for (int i = 0; i <= row; ++i) {
        double r = M_PI / row * i;
        double ry = cos(r);
        double rr = sin(r);
        for (int ii = 0; ii <= column; ++ii) {
            double tr = M_PI * 2 / column * ii;
            double tx = rr * rad * cos(tr);
            double ty = ry * rad;
            double tz = rr * rad * sin(tr);
            double rx = rr * cos(tr);
            double rz = rr * sin(tr);
            vertexPos_.emplace_back(tx, ty, tz);
            normal_.emplace_back(rx, ry, rz);
            Color colors = Util::hsva2rgb(360 / row * i, 1, 1, 1);
            vertexColor_.emplace_back(colors);
        }
    }

    for (int i = 0; i < row; ++i) {
        for (int ii = 0; ii < column; ++ii) {
            int r = (column + 1) * i + ii;
            vertexIndex_.emplace_back(r);
            vertexIndex_.emplace_back(r + 1);
            vertexIndex_.emplace_back(r + column + 2);
            vertexIndex_.emplace_back(r);
            vertexIndex_.emplace_back(r + column + 2);
            vertexIndex_.emplace_back(r + column + 1);
        }
    }

}
