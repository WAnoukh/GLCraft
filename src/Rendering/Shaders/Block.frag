#version 330 core
out vec4 FragColor;


uniform sampler2DArray ourTexture;


in vec3 c;

void main()
{
    float fogMin = 0.00;
    float fogMax = 0.99;
    float near = 500.f;
    float far  = 1000.f;
    float dist = gl_FragCoord.z / gl_FragCoord.w;
    float intensity = clamp((dist - near)/ (far- near), fogMin, fogMax);
    FragColor = mix(texture(ourTexture,vec3(c.xy, c.z)), vec4(0.7f, 0.9f, 0.9f, 1.0f), intensity);
}
