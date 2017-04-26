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


    const ProgramObjectCreator programCreator = ProgramObjectCreator("point.vert", "point.frag");
    const GLuint program = programCreator.GetProgramObject();
    glUseProgram(program);

    GLuint vao;
    //頂点配列オブジェクトの作成
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    std::vector<int> attLocation;
    attLocation.emplace_back(glGetAttribLocation(program, "position"));
    attLocation.emplace_back(glGetAttribLocation(program, "color"));
    attLocation.emplace_back(glGetAttribLocation(program, "textureCoord"));

    std::vector<int> attStride;
    attStride.emplace_back(3);
    attStride.emplace_back(4);
    attStride.emplace_back(2);

    //UniformのLocationを作成
    std::vector<int> uniLocation;
    uniLocation.emplace_back(glGetUniformLocation(program, "mvpMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "utexture"));

    std::vector<float> texturePosition = {
            -1.0, 1.0, 0.0,
            1.0, 1.0, 0.0,
            -1.0, -1.0, 0.0,
            1.0, -1.0, 0.0
    };

    std::vector<float> textureColor = {
            1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0
    };

    std::vector<float> textureCoord = {
            0.0, 0.0,
            1.0, 0.0,
            0.0, 1.0,
            1.0, 1.0
    };

    std::vector<unsigned short> textureIndex = {
            0, 1, 2,
            3, 2, 1
    };


    VBO position(texturePosition.size() * sizeof(float), &texturePosition[0]);
    position.SetAttrib(attLocation[0], attStride[0]);
    VBO color(textureColor.size() * sizeof(float), &textureColor[0]);
    color.SetAttrib(attLocation[1], attStride[1]);
    VBO coord(textureCoord.size() * sizeof(float), &textureCoord[0]);
    coord.SetAttrib(attLocation[2], attStride[2]);
    GLuint index = Util::createIBO(textureIndex.size() * sizeof(unsigned short), &textureIndex[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

    int count = 0;

    //MVP行列の作成
    glm::vec3 camPosition(0.0, 5.0, 10.0);
    glm::vec3 camUpDirection(0.0, 1.0, 0.0);

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f,
                                                  100.0f);
    glm::mat4 mvp;

    MouseDrag mouseDrag(width, height);

    Texture texture0("./texture0.png");
    Texture texture1("./texture1.png");

    GLuint tex0 = texture0.GetTexture();
    GLuint tex1 = texture1.GetTexture();

    bool onclicked = false;
    double startX, startY;

    glm::quat quaternion(glm::vec3(0, 0, 0));

    glm::mat4 mMatrix = modelMatrix;

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

    while (glfwWindowShouldClose(window) == GL_FALSE) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ++count;

        Util::calcFPS(window, 1.0, "Test:");

        double rad = (count % 180) * M_PI / 90;
        double rad2 = (count % 720) * M_PI / 360;

        glm::mat4 viewMatrix = glm::lookAt(camPosition, glm::vec3(0.0, 0.0, 0.0),
                                           camUpDirection);
        glm::mat4 invMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), camPosition, camUpDirection);

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
            invMatrix = invMatrix * quatMat;
        } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            onclicked = false;
        }

        invMatrix = glm::inverse(invMatrix);


        mMatrix = glm::rotate(modelMatrix, static_cast<float>(M_PI_2), glm::vec3(1.0f, 0.0f, 0.0f));
        mMatrix = glm::scale(mMatrix, glm::vec3(3.0, 3.0, 1.0));
        mvp = projectionMatrix * viewMatrix * mMatrix;
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex1);
        glUniform1i(uniLocation[1], 0);

        glDrawElements(GL_TRIANGLES, textureIndex.size(), GL_UNSIGNED_SHORT, 0);

        mMatrix = glm::translate(modelMatrix, glm::vec3(0.0, 1.0, 0.0));
        mMatrix = mMatrix * invMatrix;
        mvp = projectionMatrix * viewMatrix * mMatrix;
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex0);
        glUniform1i(uniLocation[1], 1);

        glDrawElements(GL_TRIANGLES, textureIndex.size(), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}
