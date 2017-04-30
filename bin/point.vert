#version 150 core

in vec3 position;
in vec3 normal;
in vec4 color;
in vec2 texCoord;
uniform mat4 mvpMatrix;
uniform mat4 invMatrix;
uniform vec3 lightVec;
uniform bool useLight;
out vec4 vColor;
out vec2 vTexCoord;

void main() {
    if(useLight) {
        vec3 invLight = normalize(invMatrix * vec4(lightVec, 0.0)).xyz;
        float diffuse = clamp(dot(normal, invLight), 0.1, 1.0);
        vColor = color * vec4(vec3(diffuse), 1.0);
    } else {
        vColor = color;
    }
    vTexCoord = texCoord;
    gl_Position = mvpMatrix * vec4(position, 1.0);
}

