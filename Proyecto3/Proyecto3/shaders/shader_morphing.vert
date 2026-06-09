#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set=0, binding = 0) uniform TransformInfo {
    mat4 MVP;
    mat4 ViewMatrix;
    mat4 ModelViewMatrix;
} Transform;

layout(set=0, binding = 3) uniform  TimeInfo{
  float time;
} Time;

layout(location = 0) in vec3 inPosition1;
layout(location = 1) in vec3 inNormal1;
layout(location = 2) in vec3 inPosition2;
layout(location = 3) in vec3 inNormal2;
layout(location = 4) in vec2 inTexCoord;

layout(location = 0) out vec3 Position;
layout(location = 1) out vec3 Normal;
layout(location = 2) out vec2 TexCoord;

void main() 
{
	vec3 pos = mix(inPosition1, inPosition2, Time.time);
	vec3 norm = mix(inNormal1, inNormal2, Time.time);

	vec4 n4 = Transform.ModelViewMatrix*vec4(norm, 0.0);
	vec4 v4 = Transform.ModelViewMatrix*vec4(pos, 1.0);
	Normal = vec3(n4);
	Position = vec3(v4);
        TexCoord = inTexCoord;
	gl_Position = Transform.MVP * vec4(pos, 1.0);
}