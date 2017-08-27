#version 150 core

in vec3 position;
in vec2 texCoord;
uniform mat4 mvpMatrix;
out vec2 vTexCoord;

void main() {
    vTexCoord = texCoord;
	gl_Position = mvpMatrix * vec4(position, 1.0);
}
