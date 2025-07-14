#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 curPos;

uniform sampler2D albedo;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 lightColor = vec4(1., 1., 1., 1.);

void main() {
   vec3 normal   = normalize(Normal);
   vec3 lightDir = normalize(lightPos - curPos);

   float ambient = 0.2;
   float diffuse = max(dot(normal, lightDir), 0.);

   float specular = 0.;
   if (diffuse != 0.) {
      float specularLight = 0.5;
      vec3  viewDir       = normalize(camPos - curPos);
      vec3  halfwayVec    = normalize(viewDir + lightDir);
      float specAmount    = pow(max(dot(normal, halfwayVec), 0.), 16);
      specular            = specAmount * specularLight;
   }

   FragColor = texture(albedo, texCoord) * lightColor * (diffuse + ambient + specular);
}
