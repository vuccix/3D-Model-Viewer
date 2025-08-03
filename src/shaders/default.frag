#version 330 core

out vec4 FragColor;

in vec3 curPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;
in mat3 TBN;

uniform sampler2D diffuse0;
uniform sampler2D specular0; // R: AO, G: Rougness (rn specular), B: Metallic
uniform sampler2D normal0;

uniform vec3 lightPos;
uniform vec3 camPos;

vec4 lightColor = vec4(1., 1., 1., 1.);

vec3 getNormal() {
    vec3 normal = texture(normal0, texCoord).rgb;
    normal = normalize(normal * 2. - 1.); // transform from [0,1] to [-1,1]
    return normalize(TBN * normal);
}

void main() {
    vec3 normal   = getNormal(); // normalize(Normal);
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

    float specValue = specular * (1.0 - texture(specular0, texCoord).g); // <---- ** .g **
    FragColor = texture(diffuse0, texCoord) * lightColor * (diffuse + ambient) + specValue;
}
