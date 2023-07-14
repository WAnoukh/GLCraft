#version 330 core
out vec4 FragColor;


uniform sampler2D ourTexture;

in vec2 c;

void main()
{
    vec4 fc = gl_FragCoord;
    fc /= 6;
    FragColor = vec4(vec3(gl_FragCoord.w),1.0);
}