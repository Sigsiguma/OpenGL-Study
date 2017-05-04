#version 150 core
precision mediump float;

out vec4 fragment;

uniform mat4 invMatrix;
uniform vec3 lightDirection;
uniform sampler2D textureData;
uniform vec4 edgeColor;
in vec4 vColor;
in vec3 vNormal;

void main() {
    if(edgeColor.a > 0.0) {
        fragment = edgeColor;
    } else {
        vec3 invLight = normalize(invMatrix * vec4(lightDirection, 0.0)).xyz;
        float diffuse = clamp(dot(vNormal, invLight), 0.0, 1.0);
        vec4 smpColor = texture(textureData, vec2(diffuse, 0.0));
        fragment = vColor * smpColor;
    }
}
