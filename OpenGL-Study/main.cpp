#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <vector>

GLboolean printShaderInfoLog(GLuint shader, const char* str) {
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if(status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;
    
    GLsizei bufSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
    
    if(bufSize > 1) {
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
        
        std::cerr << &infoLog[0] << std::endl;
    }
    
    return static_cast<GLboolean>(status);
}

GLboolean printProgramInfoLog(GLuint program) {
    
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    
    if(status == GL_FALSE) std::cerr << "Link Error." << std::endl;
    
    GLsizei bufSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
    
    if(bufSize > 1) {
        
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    
    return static_cast<GLboolean>(status);
}

GLuint createProgram(const char* vsrc, const char* fsrc) {
    
    const GLuint program(glCreateProgram());
    
    if(vsrc != nullptr) {
       
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj, 1, &vsrc, NULL);
        glCompileShader(vobj);
        
        if(printShaderInfoLog(vobj, "vertex shader"))
            glAttachShader(program, vobj);
        
        glDeleteShader(vobj);
    }
    
    if(fsrc != nullptr) {
        
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, NULL);
        glCompileShader(fobj);
        
        if(printShaderInfoLog(fobj, "fragment shader"))
            glAttachShader(program, fobj);
        
        glDeleteShader(fobj);
    }
    
    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "fragment");
    glLinkProgram(program);
    
    if(printProgramInfoLog(program))
        return program;
    
    glDeleteProgram(program);
    return 0;
}

int main(void)
{
    if(glfwInit() == GL_FALSE) {
        std::cerr << "Can't initialize GLFW" << std::endl;
        return 1;
    }
    
    atexit(glfwTerminate);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* const window = glfwCreateWindow(640, 480, "SAMPLE", NULL , NULL);
    
    if(window == nullptr) {
        std::cerr << "Can't create GLFW window." << std::endl;
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cerr << "Can't initialize GLEW" << std::endl;
        return 1;
    }
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    static const GLchar vsrc[] =
    "#version 150 core\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    " gl_Position = position;\n"
    "}\n";
    
    static const GLchar fsrc[] =
    "#version 150 core\n"
    "out vec4 fragment;"
    "void main()\n"
    "{\n"
    " fragment = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";
    
    const GLuint program(createProgram(vsrc, fsrc));

    while(glfwWindowShouldClose(window) == GL_FALSE) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        
        glfwSwapBuffers(window);
        
        glfwWaitEvents();
    }
    
}
