#version 150 core
precision mediump float;

out vec4 fragment;

uniform sampler2D textureData;
in vec4 vColor;
in vec2 vTexCoord;

void main() {
    vec4 smpColor = texture(textureData, vTexCoord);
    fragment = vColor * smpColor;
}
