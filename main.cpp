#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cstdlib>
#include <iostream>
#include "ProgramObjectCreator.h"
#include "VBO.h"
#include "Utility.h"
#include "Texture.h"
#include "Sphere.h"
#include "Torus.h"
#include "Cube.h"
#include "MouseDrag.h"

int main() {

    const int width = 640;
    const int height = 480;

    if (glfwInit() == GL_FALSE) {
        std::cerr << "Can't initialize GLFW" << std::endl;
        return 1;
    }

    atexit(glfwTerminate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *const window = glfwCreateWindow(width, height, "SAMPLE", nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "Can't create GLFW window." << std::endl;
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Can't initialize GLEW" << std::endl;
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);


    const ProgramObjectCreator programCreator = ProgramObjectCreator("point.vert", "point.frag");
    const GLuint program = programCreator.GetProgramObject();
    glUseProgram(program);


    std::vector<int> attLocation;
    attLocation.emplace_back(glGetAttribLocation(program, "position"));
    attLocation.emplace_back(glGetAttribLocation(program, "color"));
    attLocation.emplace_back(glGetAttribLocation(program, "normal"));
    attLocation.emplace_back(glGetAttribLocation(program, "texCoord"));

    std::vector<int> attStride;
    attStride.emplace_back(3);
    attStride.emplace_back(4);
    attStride.emplace_back(3);
    attStride.emplace_back(2);

    //UniformのLocationを作成
    std::vector<int> uniLocation;
    uniLocation.emplace_back(glGetUniformLocation(program, "mvpMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "invMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "lightVec"));
    uniLocation.emplace_back(glGetUniformLocation(program, "textureData"));
    uniLocation.emplace_back(glGetUniformLocation(program, "useLight"));
    uniLocation.emplace_back(glGetUniformLocation(program, "outline"));
    uniLocation.emplace_back(glGetUniformLocation(program, "useTexture"));

    Cube cube(2.0);

    GLuint sphereVAO;
    //頂点配列オブジェクトの作成
    glGenVertexArrays(1, &sphereVAO);
    glBindVertexArray(sphereVAO);

    Sphere sphere(64, 64, 1.0);

    VBO spherePosition(sphere.vertexPos_.size() * sizeof(Vector3), &sphere.vertexPos_[0]);
    spherePosition.SetAttrib(attLocation[0], attStride[0]);
    VBO sphereColor(sphere.vertexColor_.size() * sizeof(Color), &sphere.vertexColor_[0]);
    sphereColor.SetAttrib(attLocation[1], attStride[1]);
    VBO sphereNormal(sphere.normal_.size() * sizeof(Vector3), &sphere.normal_[0]);
    sphereNormal.SetAttrib(attLocation[2], attStride[2]);
    GLuint sphereIndex = Util::createIBO(sphere.vertexIndex_.size() * sizeof(unsigned short), &sphere.vertexIndex_[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIndex);

    GLuint torusVAO;
    glGenVertexArrays(1, &torusVAO);
    glBindVertexArray(torusVAO);

    Torus torus(64, 64, 0.25, 1.0);
    VBO torusPosition(torus.vertexPos_.size() * sizeof(Vector3), &torus.vertexPos_[0]);
    torusPosition.SetAttrib(attLocation[0], attStride[0]);
    VBO torusColor(torus.vertexColor_.size() * sizeof(Color), &torus.vertexColor_[0]);
    torusColor.SetAttrib(attLocation[1], attStride[1]);
    VBO torusNormal(torus.normal_.size() * sizeof(Vector3), &torus.normal_[0]);
    torusNormal.SetAttrib(attLocation[2], attStride[2]);
    GLuint torusIndex = Util::createIBO(torus.vertexIndex_.size() * sizeof(unsigned short), &torus.vertexIndex_[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, torusIndex);

    int count = 0;

    //MVP行列の作成
    glm::vec3 camPosition(0.0, 0.0, 5.0);
    glm::vec3 camUpDirection(0.0, 1.0, 0.0);

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f,
                                                  100.0f);
    glm::mat4 mvp;

    MouseDrag mouseDrag(width, height);

    glm::quat quaternion(glm::vec3(0, 0, 0));

    glm::vec3 lightVec(1.0, 1.0, 1.0);
    glUniform3fv(uniLocation[2], 1, &lightVec[0]);

    glm::mat4 mMatrix = modelMatrix;

    glEnable(GL_BLEND);
    glClearStencil(0);

    Texture texture("texture1.png");
    GLuint tex = texture.GetTexture();

    bool onclicked = false;
    double startX, startY;

    while (glfwWindowShouldClose(window) == GL_FALSE) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        ++count;

        Util::calcFPS(window, 1.0, "Test:");

        double rad = (count % 360) * M_PI / 180;

        glm::mat4 viewMatrix = glm::lookAt(camPosition, glm::vec3(0.0, 0.0, 0.0),
                                           camUpDirection);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (!onclicked) {
                onclicked = true;
                glfwGetCursorPos(window, &startX, &startY);
            }
            double currentX, currentY;
            glfwGetCursorPos(window, &currentX, &currentY);
            quaternion = mouseDrag.GetDragRotateMat(startX, startY, currentX, currentY, quaternion);
            glm::mat4 quatMat = glm::toMat4(quaternion);
            viewMatrix = viewMatrix * quatMat;
        } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            onclicked = false;
        }

        glBindVertexArray(torusVAO);
        glEnable(GL_STENCIL_TEST);
        glColorMask(false, false, false, false);
        glDepthMask(false);
        glStencilFunc(GL_ALWAYS, 1, ~0);
        glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
        mMatrix = glm::rotate(modelMatrix, static_cast<float>(rad), glm::vec3(0.0, 1.0, 1.0));
        mvp = projectionMatrix * viewMatrix * mMatrix;
        glm::mat4 invMatrix = glm::inverse(mMatrix);
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &invMatrix[0][0]);
        glUniform1i(uniLocation[4], 0);
        glUniform1i(uniLocation[5], 1);
        glUniform1i(uniLocation[6], 0);
        glDrawElements(GL_TRIANGLES, torus.vertexIndex_.size(), GL_UNSIGNED_SHORT, 0);

        glBindVertexArray(sphereVAO);
        glColorMask(true, true, true, true);
        glDepthMask(true);
        glStencilFunc(GL_EQUAL, 0, ~0);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        mMatrix = glm::scale(modelMatrix, glm::vec3(50.0, 50.0, 50.0));
        mvp = projectionMatrix * viewMatrix * mMatrix;
        invMatrix = glm::inverse(mMatrix);
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &invMatrix[0][0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(uniLocation[3], 0);
        glUniform1i(uniLocation[4], 0);
        glUniform1i(uniLocation[5], 0);
        glUniform1i(uniLocation[6], 1);
        glDrawElements(GL_TRIANGLES, sphere.vertexIndex_.size(), GL_UNSIGNED_SHORT, 0);

        glBindVertexArray(torusVAO);
        glDisable(GL_STENCIL_TEST);
        mMatrix = glm::rotate(modelMatrix, static_cast<float>(rad), glm::vec3(0.0, 1.0, 1.0));
        mvp = projectionMatrix * viewMatrix * mMatrix;
        invMatrix = glm::inverse(mMatrix);
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &invMatrix[0][0]);
        glUniform1i(uniLocation[4], 1);
        glUniform1i(uniLocation[5], 0);
        glUniform1i(uniLocation[6], 0);
        glDrawElements(GL_TRIANGLES, torus.vertexIndex_.size(), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}
