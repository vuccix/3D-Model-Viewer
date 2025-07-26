#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 curPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;

uniform mat4 MVP;
uniform mat4 model;

void main() {
    curPos      = vec3(model * vec4(aPos, 1.));
    Normal      = aNormal;
    color       = aColor;
    texCoord    = aTex;
    gl_Position = MVP * vec4(curPos, 1.);
}
