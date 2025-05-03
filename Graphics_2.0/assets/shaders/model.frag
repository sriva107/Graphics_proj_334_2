#version 330 core
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightDir = normalize(vec3(-0.5, -1.0, -0.3));
uniform vec3 objectColor = vec3(0.6, 0.6, 0.8);

void main() {
    float diffuse = max(dot(normalize(Normal), -lightDir), 0.0);
    vec3 color = diffuse * objectColor;
    FragColor = vec4(color, 1.0);
}
