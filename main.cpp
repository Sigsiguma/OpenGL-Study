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
#include "FrameBuffer.h"
#include "Utility.h"
#include "Texture.h"
#include "Sphere.h"
#include "Torus.h"
#include "Cube.h"
#include "MouseDrag.h"

int main() {

    const int width = 256;
    const int height = 256;

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

    const ProgramObjectCreator blurProgramCreator = ProgramObjectCreator("blur.vert", "blur.frag");
    const GLuint blurProgram = blurProgramCreator.GetProgramObject();


    std::vector<int> bAttLocation;
    bAttLocation.emplace_back(glGetAttribLocation(blurProgram, "position"));
    bAttLocation.emplace_back(glGetAttribLocation(blurProgram, "color"));

    std::vector<int> bAttStride;
    bAttStride.emplace_back(3);
    bAttStride.emplace_back(4);

    //UniformのLocationを作成
    std::vector<int> bUniLocation;
    bUniLocation.emplace_back(glGetUniformLocation(blurProgram, "mvpMatrix"));
    bUniLocation.emplace_back(glGetUniformLocation(blurProgram, "textureData"));
    bUniLocation.emplace_back(glGetUniformLocation(blurProgram, "useBlur"));

    GLuint blurVAO;
    glGenVertexArrays(1, &blurVAO);
    glBindVertexArray(blurVAO);

    std::vector<float> position = {
            -1.0, 1.0, 0.0,
            1.0, 1.0, 0.0,
            -1.0, -1.0, 0.0,
            1.0, -1.0, 0.0
    };

    std::vector<float> color = {
            1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0
    };

    std::vector<unsigned short> index ={
           0, 1, 2,
           3, 2, 1
    };

    VBO blurPosition(position.size() * sizeof(float), &position[0]);
    blurPosition.SetAttrib(bAttLocation[0], bAttStride[0]);
    VBO blurColor(color.size() * sizeof(float), &color[0]);
    blurColor.SetAttrib(bAttLocation[1], bAttStride[1]);
    GLuint blurIndex = Util::createIBO(index.size() * sizeof(unsigned short), &index[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, blurIndex);

    int count = 0;

    //MVP行列の作成
    glm::vec3 camPosition(0.0, 0.0, 5.0);
    glm::vec3 camUpDirection(0.0, 1.0, 0.0);

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glm::mat4 mvp;

    MouseDrag mouseDrag(width, height);

    glm::quat quaternion(glm::vec3(0, 0, 0));

    glm::vec3 lightVec(1.0, 1.0, 1.0);

    glm::mat4 mMatrix = modelMatrix;

    Texture texture0("texture0.png");
    Texture texture1("texture1.png");
    GLuint tex0 = texture0.GetTexture();
    GLuint tex1 = texture1.GetTexture();
    glActiveTexture(GL_TEXTURE0);

    FrameBuffer fBuffer(512, 512);

    bool onclicked = false;
    double startX, startY;

    while (glfwWindowShouldClose(window) == GL_FALSE) {

        glBindFramebuffer(GL_FRAMEBUFFER, fBuffer.frameBuffer_);
        glViewport(0, 0, 512, 512);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ++count;

        Util::calcFPS(window, 1.0, "Test:");

        double rad = (count % 360) * M_PI / 180;

        glUseProgram(program);

        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f),
                                                      static_cast<float>(fBuffer.frameWidth_) / fBuffer.frameHeight_,
                                                      0.1f,
                                                      100.0f);
        glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 0.0),
                                           camUpDirection);

        glBindVertexArray(cubeVAO);
        mMatrix = glm::scale(modelMatrix, glm::vec3(50.0, 50.0, 50.0));
        mvp = projectionMatrix * viewMatrix * mMatrix;
        glm::mat4 invMatrix = glm::inverse(mMatrix);
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &invMatrix[0][0]);
        glBindTexture(GL_TEXTURE_2D, tex1);
        glUniform3fv(uniLocation[2], 1, &lightVec[0]);
        glUniform1i(uniLocation[3], 0);
        glUniform1i(uniLocation[4], false);
        glDrawElements(GL_TRIANGLES, cube.vertexIndex_.size(), GL_UNSIGNED_SHORT, 0);

        mMatrix = glm::rotate(modelMatrix, static_cast<float>(rad), glm::vec3(0.0f, 1.0f, 0.0f));
        mvp = projectionMatrix * viewMatrix * mMatrix;
        invMatrix = glm::inverse(mMatrix);
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &invMatrix[0][0]);
        glBindTexture(GL_TEXTURE_2D, tex0);
        glUniform3fv(uniLocation[2], 1, &lightVec[0]);
        glUniform1i(uniLocation[3], 0);
        glUniform1i(uniLocation[4], true);
        glDrawElements(GL_TRIANGLES, cube.vertexIndex_.size(), GL_UNSIGNED_SHORT, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, width * 2, height * 2);
        glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(blurProgram);
        glBindVertexArray(blurVAO);

        viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 0.5), glm::vec3(0.0, 0.0, 0.0),
                                 camUpDirection);
        projectionMatrix = glm::ortho(-1.0, 1.0, -1.0, 1.0, 0.1, 1.0);

        glBindTexture(GL_TEXTURE_2D, fBuffer.frameTexture_);
        mvp = projectionMatrix * viewMatrix * modelMatrix;
        invMatrix = glm::inverse(mMatrix);
        glUniformMatrix4fv(bUniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniform1i(bUniLocation[1], 0);

        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            glUniform1i(bUniLocation[2], true);
        } else {
            glUniform1i(bUniLocation[2], false);
        }
        glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}
