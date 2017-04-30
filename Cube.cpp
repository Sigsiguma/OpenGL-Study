//
// Created by  Siguma Rin on 2017/04/30.
//

#include "Cube.h"

Cube::Cube(float side) {
    float hs = side * 0.5f;

    vertexPos_.emplace_back(-hs, -hs, hs);
    vertexPos_.emplace_back(hs, -hs, hs);
    vertexPos_.emplace_back(hs, hs, hs);
    vertexPos_.emplace_back(-hs, hs, hs);
    vertexPos_.emplace_back(-hs, -hs, -hs);
    vertexPos_.emplace_back(-hs, hs, -hs);
    vertexPos_.emplace_back(hs, hs, -hs);
    vertexPos_.emplace_back(hs, -hs, -hs);
    vertexPos_.emplace_back(-hs, hs, -hs);
    vertexPos_.emplace_back(-hs, hs, hs);
    vertexPos_.emplace_back(hs, hs, hs);
    vertexPos_.emplace_back(hs, hs, -hs);
    vertexPos_.emplace_back(-hs, -hs, -hs);
    vertexPos_.emplace_back(hs, -hs, -hs);
    vertexPos_.emplace_back(hs, -hs, hs);
    vertexPos_.emplace_back(-hs, -hs, hs);
    vertexPos_.emplace_back(hs, -hs, -hs);
    vertexPos_.emplace_back(hs, hs, -hs);
    vertexPos_.emplace_back(hs, hs, hs);
    vertexPos_.emplace_back(hs, -hs, hs);
    vertexPos_.emplace_back(-hs, -hs, -hs);
    vertexPos_.emplace_back(-hs, -hs, hs);
    vertexPos_.emplace_back(-hs, hs, hs);
    vertexPos_.emplace_back(-hs, hs, -hs);

    normal_.emplace_back(-1.0, -1.0, 1.0);
    normal_.emplace_back(1.0, -1.0, 1.0);
    normal_.emplace_back(1.0, 1.0, 1.0);
    normal_.emplace_back(-1.0, 1.0, 1.0);
    normal_.emplace_back(-1.0, -1.0, -1.0);
    normal_.emplace_back(-1.0, 1.0, -1.0);
    normal_.emplace_back(1.0, 1.0, -1.0);
    normal_.emplace_back(1.0, -1.0, -1.0);
    normal_.emplace_back(-1.0, 1.0, -1.0);
    normal_.emplace_back(-1.0, 1.0, 1.0);
    normal_.emplace_back(1.0, 1.0, 1.0);
    normal_.emplace_back(1.0, 1.0, -1.0);
    normal_.emplace_back(-1.0, -1.0, -1.0);
    normal_.emplace_back(1.0, -1.0, -1.0);
    normal_.emplace_back(1.0, -1.0, 1.0);
    normal_.emplace_back(-1.0, -1.0, 1.0);
    normal_.emplace_back(1.0, -1.0, -1.0);
    normal_.emplace_back(1.0, 1.0, -1.0);
    normal_.emplace_back(1.0, 1.0, 1.0);
    normal_.emplace_back(1.0, -1.0, 1.0);
    normal_.emplace_back(-1.0, -1.0, -1.0);
    normal_.emplace_back(-1.0, -1.0, 1.0);
    normal_.emplace_back(-1.0, 1.0, 1.0);
    normal_.emplace_back(-1.0, 1.0, -1.0);

    for (int i = 0; i < vertexPos_.size(); ++i) {
        vertexColor_.emplace_back(Util::hsva2rgb(360 / vertexPos_.size() * 3 / 3 * i, 1, 1, 1));
    }

    texCoord_ = {
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0
    };

    vertexIndex_ = {
            0, 1, 2, 0, 2, 3,
            4, 5, 6, 4, 6, 7,
            8, 9, 10, 8, 10, 11,
            12, 13, 14, 12, 14, 15,
            16, 17, 18, 16, 18, 19,
            20, 21, 22, 20, 22, 23
    };
}
