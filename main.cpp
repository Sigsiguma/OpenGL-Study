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

    std::vector<GLfloat> vertexPosition = {
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f
    };

    std::vector<GLfloat> vertexColor = {
            1.0, 0.0, 0.0, 1.0,
            0.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 1.0
    };

    std::vector<unsigned short> index = {
            0, 2, 1,
            1, 2, 3
    };

    Torus torus = Torus(32, 32, 1.0, 2.0);

    std::vector<Vector3> torusPosition = torus.vertexPos_;
    std::vector<Color> torusColor = torus.vertexColor_;
    std::vector<unsigned short> torusIndex = torus.vertexIndex_;


    std::vector<int> attLocation;
    attLocation.emplace_back(glGetAttribLocation(program, "position"));
    attLocation.emplace_back(glGetAttribLocation(program, "color"));

    std::vector<int> attStride;
    attStride.emplace_back(3);
    attStride.emplace_back(4);

    //頂点バッファオブジェクトの作成
    VBO positionVBO(torusPosition.size() * sizeof(Vector3), &torusPosition[0]);
    positionVBO.SetAttrib(attLocation[0], attStride[0]);

    VBO colorVBO(torusColor.size() * sizeof(Color), &torusColor[0]);
    colorVBO.SetAttrib(attLocation[1], attStride[1]);

    auto ibo = Util::createIBO(torusIndex.size() * sizeof(unsigned short), &torusIndex[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    //MVP行列の作成
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), static_cast<float>(width) / height, 0.1f,
                                                  100.0f);
    glm::mat4 vp = projectionMatrix * viewMatrix;


    auto uniLocation = glGetUniformLocation(program, "mvpMatrix");

    int count = 0;

    glm::mat4 mMatrix1;
    glm::mat4 mvp1;

    while (glfwWindowShouldClose(window) == GL_FALSE) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ++count;

        Util::calcFPS(window, 1.0, "Test:");

        double rad = (count % 360) * M_PI / 180;
        double x = cos(rad);
        double y = sin(rad);

        mMatrix1 = glm::rotate(modelMatrix, static_cast<float>(rad), glm::vec3(0.0f, 1.0f, 1.0f));
        mvp1 = vp * mMatrix1;
        glUniformMatrix4fv(uniLocation, 1, GL_FALSE, &mvp1[0][0]);
        glDrawElements(GL_TRIANGLES, torusIndex.size(), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}
