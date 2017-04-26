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
#include "MouseDrag.h"

int main(void) {

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

    std::vector<int> attStride;
    attStride.emplace_back(3);
    attStride.emplace_back(4);

    //UniformのLocationを作成
    std::vector<int> uniLocation;
    uniLocation.emplace_back(glGetUniformLocation(program, "mvpMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "pointSize"));
    uniLocation.emplace_back(glGetUniformLocation(program, "textureData"));

    GLuint sphereVAO;
    //頂点配列オブジェクトの作成
    glGenVertexArrays(1, &sphereVAO);
    glBindVertexArray(sphereVAO);

    Sphere sphere(32, 32, 2.0);
    VBO spherePos(sphere.vertexPos_.size() * sizeof(Vector3), &sphere.vertexPos_[0]);
    spherePos.SetAttrib(attLocation[0], attStride[0]);
    VBO sphereColor(sphere.vertexColor_.size() * sizeof(Color), &sphere.vertexColor_[0]);
    spherePos.SetAttrib(attLocation[1], attStride[1]);

    GLuint lineVAO;
    //頂点配列オブジェクトの作成
    glGenVertexArrays(1, &lineVAO);
    glBindVertexArray(lineVAO);

    std::vector<float> linePosition = {
            -1.0, -1.0, 0.0,
            1.0, -1.0, 0.0,
            -1.0, 1.0, 0.0,
            1.0, 1.0, 0.0
    };

    std::vector<float> lineColor = {
            1.0, 1.0, 1.0, 1.0,
            1.0, 0.0, 0.0, 1.0,
            0.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 1.0
    };

    VBO position(linePosition.size() * sizeof(float), &linePosition[0]);
    position.SetAttrib(attLocation[0], attStride[0]);
    VBO color(lineColor.size() * sizeof(float), &lineColor[0]);
    color.SetAttrib(attLocation[1], attStride[1]);

    int count = 0;

    //MVP行列の作成
    glm::vec3 camPosition(0.0, 5.0, 10.0);
    glm::vec3 camUpDirection(0.0, 1.0, 0.0);

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f,
                                                  100.0f);
    glm::mat4 mvp;

    MouseDrag mouseDrag(width, height);

    Texture texture("./texture.png");

    GLuint tex = texture.GetTexture();

    bool onclicked = false;
    double startX, startY;

    glm::quat quaternion(glm::vec3(0, 0, 0));

    glm::mat4 mMatrix = modelMatrix;

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

    float pointSize = 32.0f;

    while (glfwWindowShouldClose(window) == GL_FALSE) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ++count;

        Util::calcFPS(window, 1.0, "Test:");

        double rad = (count % 360) * M_PI / 180;
        double rad2 = (count % 720) * M_PI / 360;

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

        glBindVertexArray(sphereVAO);
        mMatrix = glm::rotate(modelMatrix, static_cast<float>(rad), glm::vec3(0.0f, 1.0f, 0.0f));
        mvp = projectionMatrix * viewMatrix * mMatrix;
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniform1f(uniLocation[1], pointSize);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(uniLocation[2], 0);

        glDrawArrays(GL_POINTS, 0, sphere.vertexPos_.size());

        glBindVertexArray(lineVAO);
        mMatrix = glm::rotate(modelMatrix, static_cast<float>(M_PI / 2), glm::vec3(0.0f, 1.0f, 0.0f));
        mMatrix = glm::scale(mMatrix, glm::vec3(3.0f, 3.0f, 0.0f));
        mvp = projectionMatrix * viewMatrix * mMatrix;
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);

        glDrawArrays(GL_LINES, 0, linePosition.size() / 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}
