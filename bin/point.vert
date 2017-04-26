#version 150 core

in vec3 position;
in vec4 color;
in vec2 textureCoord;
uniform mat4 mvpMatrix;
out vec4 vColor;
out vec2 vTextureCoord;

void main() {
    vColor = color;
    vTextureCoord = textureCoord;
    gl_Position = mvpMatrix * vec4(position, 1.0);
}

