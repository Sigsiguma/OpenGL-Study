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

	std::vector<int> attStride;
	attStride.emplace_back(3);
	attStride.emplace_back(4);
	attStride.emplace_back(3);

	//UniformのLocationを作成
	std::vector<int> uniLocation;
	uniLocation.emplace_back(glGetUniformLocation(program, "mvpMatrix"));
	uniLocation.emplace_back(glGetUniformLocation(program, "invMatrix"));
	uniLocation.emplace_back(glGetUniformLocation(program, "lightDirection"));
	uniLocation.emplace_back(glGetUniformLocation(program, "eyeDirection"));

	GLuint torusVAO;
	glGenVertexArrays(1, &torusVAO);
	glBindVertexArray(torusVAO);

	Torus torus(64, 64, 1.0, 2.0);
	VBO torusPosition(torus.vertexPos_.size() * sizeof(Vector3), &torus.vertexPos_[0]);
	torusPosition.SetAttrib(attLocation[0], attStride[0]);
	VBO torusColor(torus.vertexColor_.size() * sizeof(Color), &torus.vertexColor_[0]);
	torusColor.SetAttrib(attLocation[1], attStride[1]);
	VBO torusNormal(torus.normal_.size() * sizeof(Vector3), &torus.normal_[0]);
	torusNormal.SetAttrib(attLocation[2], attStride[2]);
	GLuint torusIndex = Util::createIBO(torus.vertexIndex_.size() * sizeof(unsigned short), &torus.vertexIndex_[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, torusIndex);

	const ProgramObjectCreator sobelProgramObject = ProgramObjectCreator("sobel.vert", "sobel.frag");
	const GLuint sobelProgram = sobelProgramObject.GetProgramObject();
	glUseProgram(sobelProgram);

	std::vector<int> gAttLocation;
	gAttLocation.emplace_back(glGetAttribLocation(sobelProgram, "position"));
	gAttLocation.emplace_back(glGetAttribLocation(sobelProgram, "texCoord"));

	std::vector<int> gAttStride;
	gAttStride.emplace_back(3);
	gAttStride.emplace_back(2);

	std::vector<int> gUniLocation;
	gUniLocation.emplace_back(glGetUniformLocation(sobelProgram, "tex"));
	gUniLocation.emplace_back(glGetUniformLocation(sobelProgram, "sobel"));
	gUniLocation.emplace_back(glGetUniformLocation(sobelProgram, "hCoef"));
	gUniLocation.emplace_back(glGetUniformLocation(sobelProgram, "vCoef"));

	std::vector<float> position = {
			-1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f
	};

	std::vector<float> texCoord = {
			0.0, 0.0,
			1.0, 0.0,
			0.0, 1.0,
			1.0, 1.0
	};

	std::vector<unsigned short> index = {
			0, 2, 1,
			2, 3, 1
	};

	std::vector<float> hCoef = {
			1.0f, 0.0f, -1.0f,
			2.0f, 0.0f, -2.0f,
			1.0f, 0.0f, -1.0f
	};

	std::vector<float> vCoef = {
			1.0f, 2.0f, 1.0f,
			0.0f, 0.0f, 0.0f,
			-1.0f, -2.0f, -1.0f
	};


	GLuint boardVAO;
	glGenVertexArrays(1, &boardVAO);
	glBindVertexArray(boardVAO);

	VBO boardPosition(position.size() * sizeof(float), &position[0]);
	boardPosition.SetAttrib(gAttLocation[0], gAttStride[0]);
	VBO boardTexCoord(texCoord.size() * sizeof(float), &texCoord[0]);
	boardTexCoord.SetAttrib(gAttLocation[1], gAttStride[1]);
	GLuint boardIndex = Util::createIBO(index.size() * sizeof(unsigned short), &index[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boardIndex);

	int count = 0, count2 = 0;

	//MVP行列の作成
	glm::vec3 camPosition(0.0, 0.0, 30.0);
	glm::vec3 camUpDirection(0.0, 1.0, 0.0);

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	glm::mat4 mvp;

	MouseDrag mouseDrag(width, height);

	glm::quat quaternion(glm::vec3(0, 0, 0));

	glm::vec3 lightDirection(-0.5f, 0.5f, 0.5f);

	glm::mat4 mMatrix = modelMatrix;

	bool onclicked = false;
	double startX, startY;

	glm::vec4 edgeColor(0.0f, 0.0f, 0.0f, 1.0f);

	FrameBuffer frameBuffer(width, height);

	while (glfwWindowShouldClose(window) == GL_FALSE) {

		Util::calcFPS(window, 1.0, "Test:");

		++count;
		if (count % 2 == 0) { ++count2; }

		double rad = (count % 360) * M_PI / 180;

		glUseProgram(program);

		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.frameBuffer_);
		glViewport(0, 0, width, height);

		Color color = Util::hsva2rgb(count2 % 360, 1, 1, 1);
		glClearColor(color.r, color.g, color.b, color.a);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
			viewMatrix = viewMatrix * glm::toMat4(quaternion);
		} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			onclicked = false;
		}

		glBindVertexArray(torusVAO);

		for (int i = 0; i < 9; ++i) {
			mMatrix = glm::rotate(modelMatrix, static_cast<float>(i * 2 * M_PI / 9.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			mMatrix = glm::translate(mMatrix, glm::vec3(0.0, 0.0, 10.0));
			mMatrix = glm::rotate(mMatrix, static_cast<float>(rad), glm::vec3(1.0f, 1.0f, 0.0f));
			mvp = projectionMatrix * viewMatrix * mMatrix;
			glm::mat4 invMatrix = glm::inverse(mMatrix);
			glUniformMatrix4fv(uniLocation[0], 1, GL_FALSE, &mvp[0][0]);
			glUniformMatrix4fv(uniLocation[1], 1, GL_FALSE, &invMatrix[0][0]);
			glUniform3fv(uniLocation[2], 1, &lightDirection[0]);
			glUniform3fv(uniLocation[3], 1, &camPosition[0]);
			glDrawElements(GL_TRIANGLES, torus.vertexIndex_.size(), GL_UNSIGNED_SHORT, 0);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width * 2, height * 2);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(sobelProgram);
		glBindVertexArray(boardVAO);

		viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 0.5), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		projectionMatrix = glm::ortho(-1.0, 1.0, -1.0, 1.0, 0.1, 1.0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, frameBuffer.frameTexture_);

		mvp = projectionMatrix * viewMatrix * modelMatrix;
		glUniform1i(gUniLocation[0], 0);
		glUniform1i(gUniLocation[1], 1);
		glUniform1fv(gUniLocation[2], 9, &hCoef[0]);
		glUniform1fv(gUniLocation[3], 9, &vCoef[0]);
		glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_SHORT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

}
