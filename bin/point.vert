#version 150 core

in vec3 position;
in vec3 normal;
in vec4 color;
uniform mat4 mvpMatrix;
uniform mat4 mMatrix;
out vec3 vPosition;
out vec3 vNormal;
out vec4 vColor;

void main() {
    vPosition = (mMatrix * vec4(position, 1.0)).xyz;
    vNormal = normal;
    vColor = color;
    gl_Position = mvpMatrix * vec4(position, 1.0);
}
