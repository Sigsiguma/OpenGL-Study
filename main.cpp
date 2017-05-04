#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cstdlib>
#include <iostream>
#include "ProgramObjectCreator.h"
#include "VBO.h"
#include "FrameBuffer.h"
#include "Utility.h"
#include "Texture.h"
#include "Sphere.h"
#include "Torus.h"
#include "Cube.h"
#include "MouseDrag.h"

int main() {

    const int width = 512;
    const int height = 512;

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
    uniLocation.emplace_back(glGetUniformLocation(program, "mMatrix"));
    uniLocation.emplace_back(glGetUniformLocation(program, "lightPosition"));
    uniLocation.emplace_back(glGetUniformLocation(program, "eyePosition"));
    uniLocation.emplace_back(glGetUniformLocation(program, "textureData"));
    uniLocation.emplace_back(glGetUniformLocation(program, "textureData2"));
    uniLocation.emplace_back(glGetUniformLocation(program, "height"));


    GLuint cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    Cube cube(2.0);
    VBO cubePosition(cube.vertexPos_.size() * sizeof(Vector3), &cube.vertexPos_[0]);
    cubePosition.SetAttrib(attLocation[0], attStride[0]);
    VBO cubeColor(cube.vertexColor_.size() * sizeof(Color), &cube.vertexColor_[0]);
    cubeColor.SetAttrib(attLocation[1], attStride[1]);
    VBO cubeNormal(cube.normal_.size() * sizeof(Vector3), &cube.normal_[0]);
    cubeNormal.SetAttrib(attLocation[2], attStride[2]);
    VBO cubeTexCoord(cube.texCoord_.size() * sizeof(float), &cube.texCoord_[0]);
    cubeTexCoord.SetAttrib(attLocation[3], attStride[3]);
    GLuint cubeIndex = Util::createIBO(cube.vertexIndex_.size() * sizeof(unsigned short), &cube.vertexIndex_[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndex);

    int count = 0;

    //MVP行列の作成
    glm::vec3 camPosition(0.0, 0.0, 5.0);
    glm::vec3 camUpDirection(0.0, 1.0, 0.0);

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glm::mat4 mvp;

    MouseDrag mouseDrag(width, height);

    glm::quat quaternion(glm::vec3(0, 0, 0));

    glm::vec3 lightPos(-10.0f, 10.0f, 10.0f);

    glm::mat4 mMatrix = modelMatrix;

    Texture texture0("texture.png");
    Texture texture1("texture1.png");
    GLuint tex0 = texture0.GetTexture();
    GLuint tex1 = texture1.GetTexture();
    glActiveTexture(GL_TEXTURE0);

    bool onclicked = false;
    double startX, startY;

    while (glfwWindowShouldClose(window) == GL_FALSE) {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ++count;

        Util::calcFPS(window, 1.0, "Test:");

        double rad = (count % 360) * M_PI / 180;


        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height,
                                                      0.1f,
                                                      100.0f);
        glm::mat4 viewMatrix = glm::lookAt(camPosition, glm::vec3(0.0, 0.0, 0.0), camUpDirection);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (!onclicked) {
                onclicked = true;
                glfwGetCursorPos(window, &startX, &startY);
            }
            double currentX, currentY;
            glfwGetCursorPos(window, &currentX, &currentY);
            quaternion = mouseDrag.GetDragRotateMat(startX, startY, currentX, currentY, quaternion);
            viewMatrix =  viewMatrix * glm::toMat4(quaternion);
        } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            onclicked = false;
        }

        glBindVertexArray(cubeVAO);
        mMatrix = glm::rotate(modelMatrix, static_cast<float>(rad), glm::vec3(0.0f, 1.0, 0.0f));
        mvp = projectionMatrix * viewMatrix * mMatrix;
        glm::mat4 invMatrix = glm::inverse(mMatrix);
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &invMatrix[0][0]);
        glUniformMatrix4fv(uniLocation[2], 1, GL_FALSE, &mMatrix[0][0]);
        glUniform3fv(uniLocation[3], 1, &lightPos[0]);
        glUniform3fv(uniLocation[4], 1, &camPosition[0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex0);
        glUniform1i(uniLocation[5], 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex1);
        glUniform1i(uniLocation[6], 1);
        glUniform1f(uniLocation[7], 0.02f);

        glDrawElements(GL_TRIANGLES, cube.vertexIndex_.size(), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}
