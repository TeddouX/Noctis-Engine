#ifdef VERTEX

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout(std140, binding = 0) uniform CameraBuffer {
   mat4 projMat;
   mat4 viewMat;
} camera;

uniform int modelIdx;
layout(std430, binding = 2) buffer ModelMatrices {
   mat4 modelMatrices[];
} models;

out vec3 Pos;
out vec2 TexCoord;

void main()
{
   gl_Position = camera.projMat * camera.viewMat * models.modelMatrices[modelIdx] * vec4(aPos, 1.0);
   Pos = aPos;
   TexCoord = aTexCoord;
}

#endif



#ifdef FRAGMENT

in vec3 Pos;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D drone;

layout(std140, binding = 1) uniform TestBuffer {
   vec3 col;
} test;

void main()
{
   // FragColor = vec4(test.col, 1.0f);
   FragColor = texture(drone, TexCoord);
}

#endif
