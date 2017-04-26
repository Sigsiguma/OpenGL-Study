#version 150 core
precision mediump float;

out vec4 fragment;

uniform sampler2D textureData;

in vec4 vColor;

void main() {
    vec4 smpColor = texture(textureData, gl_PointCoord);

    if(smpColor.a == 0.0) {
        discard;
    }

    fragment = vColor * smpColor;
}
