#version 150 core
precision mediump float;

out vec4 fragment;

uniform sampler2D textureData;
uniform bool grayScale;
in vec2 vTexCoord;

const float redScale = 0.298912;
const float greenScale = 0.586611;
const float blueScale = 0.114478;
const vec3 monochromeScale = vec3(redScale, greenScale, blueScale);

void main() {
    vec4 smpColor = texture(textureData, vTexCoord);

    if(grayScale) {
        float grayColor = dot(smpColor.rgb, monochromeScale);
        smpColor = vec4(vec3(grayColor), 1.0);
    }

    fragment = smpColor;
}
