//
// Created by  Siguma Rin on 2017/04/25.
//

#ifndef OPENGL_MOUSEDRAG_H
#define OPENGL_MOUSEDRAG_H
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>

class MouseDrag {
public:
    MouseDrag(int windowWidth, int windowHeight);

    glm::mat4 GetDragRotateMat(double startX, double startY, double currentX, double currentY, glm::quat currentQuat);

private:
    const double scale_;

    int windowWidth_;
    int windowHeight_;
    double scaleX_;
    double scaleY_;
};

#endif //OPENGL_MOUSEDRAG_H
