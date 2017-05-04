#version 150 core
precision mediump float;

out vec4 fragment;

uniform sampler2D textureData;
uniform sampler2D textureData2;
uniform float height;
in vec4 vColor;
in vec2 vTexCoord;
in vec3 vEyeDirection;
in vec3 vLightDirection;

void main() {
    vec3 light = normalize(vLightDirection);
    vec3 eye = normalize(vEyeDirection);
    float hScale = texture(textureData2, vTexCoord).r * height;
    vec2 heightTexCoord = vTexCoord - eye.xy * hScale;
    vec3 mNormal = (texture(textureData, heightTexCoord) * 2.0 - 1.0).rgb;
    vec3 halfLE = normalize(light + eye);
    float diffuse = clamp(dot(mNormal, light), 0.1, 1.0);
    float specular = pow(clamp(dot(mNormal, halfLE), 0.0, 1.0), 100.0);
    fragment = vColor * vec4(vec3(diffuse), 1.0) + vec4(vec3(specular), 1.0);
}
