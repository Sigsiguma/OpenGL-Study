#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <cstdlib>
#include <iostream>
#include "ProgramObjectCreator.h"
#include "VBO.h"
#include "Utility.h"
#include "Torus.h"
#include "Sphere.h"

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

    GLFWwindow *const window = glfwCreateWindow(width, height, "SAMPLE", NULL, NULL);

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
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    const ProgramObjectCreator programCreator = ProgramObjectCreator("point.vert", "point.frag");
    const GLuint program = programCreator.GetProgramObject();
    glUseProgram(program);

    GLuint vao;
    //頂点配列オブジェクトの作成
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Torus torus = Torus(64, 64, 0.5, 1.5);

    std::vector<Vector3> torusPosition = torus.vertexPos_;
    std::vector<Vector3> torusNormal = torus.normal_;
    std::vector<Color> torusColor = torus.vertexColor_;
    std::vector<unsigned short> torusIndex = torus.vertexIndex_;

    Sphere sphere = Sphere(64, 64, 2.0);
    std::vector<Vector3> spherePosition = sphere.vertexPos_;
    std::vector<Vector3> sphereNormal = sphere.normal_;
    std::vector<Color> sphereColor = sphere.vertexColor_;
    std::vector<unsigned short> sphereIndex = sphere.vertexIndex_;


    std::vector<int> attLocation;
    attLocation.emplace_back(glGetAttribLocation(program, "position"));
    attLocation.emplace_back(glGetAttribLocation(program, "normal"));
    attLocation.emplace_back(glGetAttribLocation(program, "color"));

    std::vector<int> attStride;
    attStride.emplace_back(3);
    attStride.emplace_back(3);
    attStride.emplace_back(4);

    //頂点バッファオブジェクトの作成
    GLuint torusVAO;
    glGenVertexArrays(1, &torusVAO);
    glBindVertexArray(torusVAO);

    VBO torusPositionVBO(torusPosition.size() * sizeof(Vector3), &torusPosition[0]);
    torusPositionVBO.SetAttrib(attLocation[0], attStride[0]);

    VBO torusNormalVBO(torusNormal.size() * sizeof(Vector3), &torusNormal[0]);
    torusNormalVBO.SetAttrib(attLocation[1], attStride[1]);

    VBO torusColorVBO(torusColor.size() * sizeof(Color), &torusColor[0]);
    torusColorVBO.SetAttrib(attLocation[2], attStride[2]);

    auto torusIbo = Util::createIBO(torusIndex.size() * sizeof(unsigned short), &torusIndex[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, torusIbo);

    GLuint  sphereVAO;
    glGenVertexArrays(1, &sphereVAO);
    glBindVertexArray(sphereVAO);

    VBO spherePositionVBO(spherePosition.size() * sizeof(Vector3), &spherePosition[0]);
    spherePositionVBO.SetAttrib(attLocation[0], attStride[0]);

    VBO sphereNormalVBO(sphereNormal.size() * sizeof(Vector3), &sphereNormal[0]);
    sphereNormalVBO.SetAttrib(attLocation[1], attStride[1]);

    VBO sphereColorVBO(sphereColor.size() * sizeof(Color), &sphereColor[0]);
    sphereColorVBO.SetAttrib(attLocation[2], attStride[2]);

    auto sphereIBO = Util::createIBO(sphereIndex.size() * sizeof(unsigned short), &sphereIndex[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBO);

    //MVP行列の作成
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 invMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), static_cast<float>(width) / height, 0.1f,
                                                  100.0f);
    glm::mat4 vp = projectionMatrix * viewMatrix;

    //UniformのLocationを作成
    std::vector<int> uniLocation;
    uniLocation.emplace_back(glGetUniformLocation(program, "mvpMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "mMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "invMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "lightPosition"));
    uniLocation.emplace_back(glGetUniformLocation(program, "ambientColor"));
    uniLocation.emplace_back(glGetUniformLocation(program, "eyeDirection"));

    int count = 0;

    auto lightPosition = glm::vec3(0.0, 0.0, 0.0);
    auto ambientColor = glm::vec4(0.1, 0.1, 0.1, 1.0);
    auto eyeDirection = glm::vec3(0.0, 0.0, 20.0);
    glUniform3fv(uniLocation[3], 1, &lightPosition[0]);
    glUniform4fv(uniLocation[4], 1, &ambientColor[0]);
    glUniform3fv(uniLocation[5], 1, &eyeDirection[0]);

    glm::mat4 mMatrix;
    glm::mat4 mvp;

    while (glfwWindowShouldClose(window) == GL_FALSE) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ++count;

        Util::calcFPS(window, 1.0, "Test:");

        double rad = (count % 360) * M_PI / 180;
        double tx = cos(rad) * 3.5;
        double ty = sin(rad) * 3.5;
        double tz = sin(rad) * 3.5;

        //torusの描画
        mMatrix = glm::translate(modelMatrix, glm::vec3(-tx, ty, tz));
        mMatrix = glm::rotate(mMatrix, -static_cast<float>(rad), glm::vec3(0.0f, 1.0f, 1.0f));
        mvp = vp * mMatrix;
        invMatrix = glm::inverse(mMatrix);

        glBindVertexArray(torusVAO);
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &mMatrix[0][0]);
        glUniformMatrix4fv(uniLocation[2], 1, GL_FALSE, &invMatrix[0][0]);
        glDrawElements(GL_TRIANGLES, torusIndex.size(), GL_UNSIGNED_SHORT, 0);

        //sphereの描画
        mMatrix = glm::translate(modelMatrix, glm::vec3(tx, -ty, -tz));
        mvp = vp * mMatrix;
        invMatrix = glm::inverse(mMatrix);

        glBindVertexArray(sphereVAO);
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &mMatrix[0][0]);
        glUniformMatrix4fv(uniLocation[2], 1, GL_FALSE, &invMatrix[0][0]);
        glDrawElements(GL_TRIANGLES, sphereIndex.size(), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}
