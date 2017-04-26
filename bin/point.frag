#version 150 core
precision mediump float;

out vec4 fragment;

uniform sampler2D utexture;
in vec4 vColor;
in vec2 vTextureCoord;

void main() {
    vec4 smpColor = texture(utexture, vTextureCoord);
    fragment = vColor * smpColor;
}
