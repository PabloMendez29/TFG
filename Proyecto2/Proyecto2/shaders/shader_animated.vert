#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set=0, binding = 0) uniform TransformInfo {
    mat4 MVP;
    mat4 ViewMatrix;
    mat4 ModelViewMatrix;
} Transform;

layout(set=0, binding = 3) readonly buffer JointInfo {
  mat4 matrices[];
} Joint;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec4 inJointWeights;
layout(location = 4) in ivec4 inJointIndices;

layout(location = 0) out vec3 Position;
layout(location = 1) out vec3 Normal;
layout(location = 2) out vec2 TexCoord;

void main() 
{
	mat4 skinMat = 
		inJointWeights.x * Joint.matrices[inJointIndices.x] +
		inJointWeights.y * Joint.matrices[inJointIndices.y] +
		inJointWeights.z * Joint.matrices[inJointIndices.z] +
		inJointWeights.w * Joint.matrices[inJointIndices.w];

	vec4 n4 = Transform.ModelViewMatrix*skinMat*vec4(inNormal, 0.0);
	vec4 v4 = Transform.ModelViewMatrix*skinMat*vec4(inPosition,1.0);
	Normal = vec3(n4);
	Position = vec3(v4);
        TexCoord = inTexCoord;
	gl_Position = Transform.MVP * skinMat * vec4(inPosition, 1.0);
}