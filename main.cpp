#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
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
    attLocation.emplace_back(glGetAttribLocation(program, "textureCoord"));

    std::vector<int> attStride;
    attStride.emplace_back(3);
    attStride.emplace_back(3);
    attStride.emplace_back(4);
    attStride.emplace_back(2);

    //MVP行列の作成
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 invMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0, 2.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f,
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
    uniLocation.emplace_back(glGetUniformLocation(program, "utexture"));

    int count = 0;

    auto lightPosition = glm::vec3(0.0, 0.0, 0.0);
    auto ambientColor = glm::vec4(0.1, 0.1, 0.1, 1.0);
    auto eyeDirection = glm::vec3(0.0, 0.0, 20.0);
    glUniform3fv(uniLocation[3], 1, &lightPosition[0]);
    glUniform4fv(uniLocation[4], 1, &ambientColor[0]);
    glUniform3fv(uniLocation[5], 1, &eyeDirection[0]);


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

    std::vector<float> textureCoord = {
            0.0, 0.0,
            1.0, 0.0,
            0.0, 1.0,
            1.0, 1.0
    };

    std::vector<unsigned short> index = {
            0, 1, 2,
            3, 2, 1
    };

    VBO vPosition = VBO(position.size() * sizeof(float), &position[0]);
    vPosition.SetAttrib(attLocation[0], attStride[0]);
    VBO vColor = VBO(color.size() * sizeof(float), &color[0]);
    vColor.SetAttrib(attLocation[2], attStride[2]);
    VBO vTextureCoord = VBO(textureCoord.size() * sizeof(float), &textureCoord[0]);
    vTextureCoord.SetAttrib(attLocation[3], attStride[3]);

    auto vIBO = Util::createIBO(index.size() * sizeof(unsigned short), &index[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vIBO);

    //テクスチャの表示
    cv::Mat img = cv::imread("./texture4.png", cv::IMREAD_UNCHANGED);
    cv::cvtColor(img, img, cv::COLOR_BGRA2RGBA);

    glActiveTexture(GL_TEXTURE0);

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.cols, img.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 img.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glUniform1i(uniLocation[6], 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
        mMatrix = glm::rotate(modelMatrix, static_cast<float>(rad), glm::vec3(0.1f, 1.0f, 0.0f));
        mvp = vp * mMatrix;
        invMatrix = glm::inverse(mMatrix);
        glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &mMatrix[0][0]);
        glUniformMatrix4fv(uniLocation[2], 1, GL_FALSE, &invMatrix[0][0]);
        glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}
