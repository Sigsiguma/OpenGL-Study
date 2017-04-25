#version 150 core
precision mediump float;

out vec4 fragment;
uniform mat4 invMatrix;
uniform vec3 lightPosition;
uniform vec4 ambientColor;
uniform vec3 eyeDirection;
in vec3 vPosition;
in vec4 vColor;
in vec3 vNormal;

void main() {
    vec3 lightVec = lightPosition - vPosition;
    vec3 invLight = normalize(invMatrix * vec4(lightVec, 0.0)).xyz;
    vec3 invEye = normalize(invMatrix * vec4(eyeDirection, 0.0)).xyz;
    vec3 halfLE = normalize(invLight + invEye);
    float diffuse = clamp(dot(vNormal, invLight), 0.0, 1.0) + 0.2;
    float specular = pow(clamp(dot(vNormal, halfLE), 0.0, 1.0), 50.0);
    fragment = vColor * vec4(vec3(diffuse), 1.0) + vec4(vec3(specular), 1.0) + ambientColor;
}
