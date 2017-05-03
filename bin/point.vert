#version 150 core

in vec3 position;
in vec3 normal;
in vec4 color;
in vec2 texCoord;
uniform mat4 mvpMatrix;
uniform mat4 invMatrix;
uniform mat4 mMatrix;
uniform vec3 lightPosition;
uniform vec3 eyePosition;
out vec4 vColor;
out vec2 vTexCoord;
out vec3 vEyeDirection;
out vec3 vLightDirection;

void main() {
    vec3 pos = (mMatrix * vec4(position, 0.0)).xyz;
    vec3 invEye = (invMatrix * vec4(eyePosition, 0.0)).xyz;
    vec3 invLight = (invMatrix * vec4(lightPosition, 0.0)).xyz;
    vec3 eye = invEye - pos;
    vec3 light = invLight - pos;
    vec3 n = normalize(normal);
    vec3 t = normalize(cross(normal, vec3(0.0, 1.0, 0.0)));
    vec3 b = cross(n, t);
    vEyeDirection.x = dot(t, eye);
    vEyeDirection.y = dot(b, eye);
    vEyeDirection.z = dot(n, eye);
    normalize(vEyeDirection);
    vLightDirection.x = dot(t, light);
    vLightDirection.y = dot(b, light);
    vLightDirection.z = dot(n, light);
    normalize(vLightDirection);
    vColor = color;
    vTexCoord = texCoord;
    gl_Position = mvpMatrix * vec4(position, 1.0);
}

