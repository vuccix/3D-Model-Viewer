#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 texCoord;
out vec3 Normal;
out vec3 curPos;

uniform mat4 MVP;
uniform mat4 model;

void main() {
   curPos = vec3(model * vec4(aPos, 1.));

   gl_Position = MVP * vec4(curPos, 1.);
   color       = aColor;
   texCoord    = aTex;
   Normal      = aNormal;
}
