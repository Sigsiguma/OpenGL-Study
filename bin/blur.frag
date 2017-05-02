#version 150 core
precision mediump float;

out vec4 fragment;

uniform sampler2D textureData;
uniform bool useBlur;
in vec4 vColor;

void main() {
    vec2 tFrag = vec2(1.0 / 512.0);
    vec4 destColor = texture(textureData, gl_FragCoord.st * tFrag);
    if(useBlur){
        destColor *= 0.36;
        destColor += texture(textureData, (gl_FragCoord.st + vec2(-1.0,  1.0)) * tFrag) * 0.04;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 0.0,  1.0)) * tFrag) * 0.04;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 1.0,  1.0)) * tFrag) * 0.04;
        destColor += texture(textureData, (gl_FragCoord.st + vec2(-1.0,  0.0)) * tFrag) * 0.04;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 1.0,  0.0)) * tFrag) * 0.04;
        destColor += texture(textureData, (gl_FragCoord.st + vec2(-1.0, -1.0)) * tFrag) * 0.04;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 0.0, -1.0)) * tFrag) * 0.04;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 1.0, -1.0)) * tFrag) * 0.04;
        destColor += texture(textureData, (gl_FragCoord.st + vec2(-2.0,  2.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2(-1.0,  2.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 0.0,  2.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 1.0,  2.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 2.0,  2.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2(-2.0,  1.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 2.0,  1.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2(-2.0,  0.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 2.0,  0.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2(-2.0, -1.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 2.0, -1.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2(-2.0, -2.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2(-1.0, -2.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 0.0, -2.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 1.0, -2.0)) * tFrag) * 0.02;
        destColor += texture(textureData, (gl_FragCoord.st + vec2( 2.0, -2.0)) * tFrag) * 0.02;
    }
    fragment  = vColor * destColor;
}
