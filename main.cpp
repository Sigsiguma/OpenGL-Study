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
#include "Torus.h"

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

    const ProgramObjectCreator programCreator = ProgramObjectCreator("point.vert", "point.frag");
    const GLuint program = programCreator.GetProgramObject();
    glUseProgram(program);

    GLuint vao;
    //頂点配列オブジェクトの作成
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    std::vector<int> attLocation;
    attLocation.emplace_back(glGetAttribLocation(program, "position"));
    attLocation.emplace_back(glGetAttribLocation(program, "normal"));
    attLocation.emplace_back(glGetAttribLocation(program, "color"));

    std::vector<int> attStride;
    attStride.emplace_back(3);
    attStride.emplace_back(3);
    attStride.emplace_back(4);

    //UniformのLocationを作成
    std::vector<int> uniLocation;
    uniLocation.emplace_back(glGetUniformLocation(program, "mvpMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "mMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "invMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "lightPosition"));
    uniLocation.emplace_back(glGetUniformLocation(program, "ambientColor"));
    uniLocation.emplace_back(glGetUniformLocation(program, "eyeDirection"));

    Torus torus(64, 64, 0.5, 1.5);
    std::vector<Vector3> torusPosition = torus.vertexPos_;
    std::vector<Vector3> torusNormal = torus.normal_;
    std::vector<Color> torusColor = torus.vertexColor_;
    std::vector<unsigned short> torusIndex = torus.vertexIndex_;

    VBO position(torusPosition.size() * sizeof(Vector3), &torusPosition[0]);
    position.SetAttrib(attLocation[0], attStride[0]);
    VBO normal(torusNormal.size() * sizeof(Vector3), &torusNormal[0]);
    normal.SetAttrib(attLocation[1], attStride[1]);
    VBO color(torusColor.size() * sizeof(Color), &torusColor[0]);
    color.SetAttrib(attLocation[2], attStride[2]);
    GLuint index = Util::createIBO(torusIndex.size() * sizeof(unsigned short), &torusIndex[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

    int count = 0;

    auto lightPosition = glm::vec3(15.0, 10.0, 15.0);
    auto ambientColor = glm::vec4(0.1, 0.1, 0.1, 1.0);
    auto eyeDirection = glm::vec3(0.0, 0.0, 10.0);
    glUniform3fv(uniLocation[3], 1, &lightPosition[0]);
    glUniform4fv(uniLocation[4], 1, &ambientColor[0]);
    glUniform3fv(uniLocation[5], 1, &eyeDirection[0]);


    //MVP行列の作成
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 invMatrix = glm::mat4(1.0f);

    glm::mat4 mvp;

    while (glfwWindowShouldClose(window) == GL_FALSE) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ++count;

        Util::calcFPS(window, 1.0, "Test:");

        double rad = (count % 180) * M_PI / 90;
        double rad2 = (count % 720) * M_PI / 360;

        glm::quat quaternion(glm::vec3(rad2, 0, 0));

        glm::vec3 camPosition(0.0, 0.0, 10.0);
        glm::vec3 camUpDirection(0.0, 1.0, 0.0);
        camPosition = quaternion * camPosition;
        camUpDirection = quaternion * camUpDirection;

        //torusの描画
        glm::mat4 viewMatrix = glm::lookAt(camPosition, glm::vec3(0.0, 0.0, 0.0),
                                           camUpDirection);
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f,
                                                      100.0f);
        mvp = projectionMatrix * viewMatrix * modelMatrix;
        invMatrix = glm::inverse(modelMatrix);

        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &modelMatrix[0][0]);
        glUniformMatrix4fv(uniLocation[2], 1, GL_FALSE, &invMatrix[0][0]);

        glDrawElements(GL_TRIANGLES, torusIndex.size(), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}
