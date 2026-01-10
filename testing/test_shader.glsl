#ifdef VERTEX

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec2 aTexCoord;

layout (std140, binding = 0) uniform CameraBuffer {
  mat4 projMat;
  mat4 viewMat;
  vec3 pos;
} camera;


struct Object {
  mat4 modelMat;
  uint materialIdx;
};

layout (std430, binding = 1) buffer Objects {
  Object objects[];
} objects;


layout (location = 0) out vec2 fsTexCoord;
layout (location = 1) out flat uint fsMaterialIdx;


void main()
{
  Object obj = objects.objects[gl_DrawID];

  gl_Position = camera.projMat * camera.viewMat * obj.modelMat * vec4(aPos, 1.0);
  fsTexCoord = aTexCoord;
  fsMaterialIdx = obj.materialIdx;
}

#endif



#ifdef FRAGMENT

struct Material {
  vec4 baseColor;
  sampler2D albedo;
};

layout (std430, binding = 2) buffer Materials {
  Material materials[];
} materials;


layout (location = 0) in vec2 fsTexCoord;
layout (location = 1) in flat uint fsMaterialIdx;

layout (location = 0) out vec4 FragColor;


Material get_material() {
  return materials.materials[fsMaterialIdx];
}

vec4 get_albedo() {
  Material mat = get_material();
  return texture(mat.albedo, fsTexCoord);
}


void main()
{
  FragColor = get_albedo();
}

#endif
