#version 150 core
precision mediump float;

out vec4 fragment;

uniform sampler2D textureData;
uniform bool useTexture;
in vec4 vColor;
in vec2 vTexCoord;

void main() {
    if(useTexture) {
        vec4 smpColor = texture(textureData, vTexCoord);
        fragment = smpColor;
    } else {
        fragment = vColor;
    }
}
