#version 150 core
precision mediump float;
out vec4 fragment;
in vec4 vColor;

void main() {
    fragment = vColor;
}
