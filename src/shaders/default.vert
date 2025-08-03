#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;
layout (location = 4) in vec4 aTangent;

out vec3 curPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;
out mat3 TBN;

uniform mat4 MVP;
uniform mat4 model;

void main() {
    vec3 T = normalize(mat3(model) * aTangent.xyz);
    vec3 N = normalize(mat3(model) * aNormal);
    vec3 B = normalize(cross(N, T) * aTangent.w);

    curPos      = vec3(model * vec4(aPos, 1.));
    Normal      = aNormal;
    color       = aColor;
    texCoord    = aTex;
    TBN         = mat3(T, B, N);
    gl_Position = MVP * vec4(curPos, 1.);
}
