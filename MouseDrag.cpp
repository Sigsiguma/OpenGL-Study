//
// Created by  Siguma Rin on 2017/04/25.
//

#include "MouseDrag.h"
#include <cmath>

MouseDrag::MouseDrag(int windowWidth, int windowHeight)
        : scale_(2.0 * M_PI), windowWidth_(windowWidth), windowHeight_(windowHeight), scaleX_(1.0 / windowWidth),
          scaleY_(1.0 / windowHeight) {}

glm::mat4 MouseDrag::GetDragRotateMat(double startX, double startY, double currentX, double currentY,
                                      glm::quat currentQuat) {

    double dx = (currentX - startX) * scaleX_;
    double dy = (currentY - startY) * scaleY_;

    double a = sqrt(dx * dx + dy * dy);

    if (a != 0.0) {
        double ar = a * scale_ * 0.5;
        double as = sin(ar) / a;
        glm::quat dq(cos(ar), dy * as, dx * as, 0.0);

        glm::quat tq = dq;

        return glm::toMat4(tq);
    }
}
