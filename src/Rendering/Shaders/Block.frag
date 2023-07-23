#version 330 core
out vec4 FragColor;


uniform sampler2DArray ourTexture;


in vec3 c;

void main()
{
    FragColor = texture(ourTexture,vec3(c.xy, c.z));
}