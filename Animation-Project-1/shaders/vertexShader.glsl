// Vertex shader
#version 420

mat4 MVP;
uniform mat4 Model;
uniform mat4 ModelInverse;
uniform mat4 View;
uniform mat4 Projection;

in vec3 vPosition;
in vec3 vColour;
in vec3 vNormal;

in vec4 vUV2;
in vec4 vTangent;
in vec4 vBiNormal;
in vec4 vBoneID;
in vec4 vBoneWeight;

out vec3 colour;
out vec3 normal;
out vec3 worldlocation;

out vec4 uv2;
out vec4 tangent;
out vec4 biNormal;
out vec4 boneID;
out vec4 boneWeight;

void main()
{
	vec3 vertPosition = vPosition.xyz;

	MVP = Projection * View * Model;
	
	gl_Position = MVP * vec4(vertPosition, 1.f);

	worldlocation.xyz = (Model * vec4(vPosition, 1.f)).xyz;
	normal.xyz = (ModelInverse * vec4(vNormal, 1.f)).xyz;

	colour = vColour;
	uv2 = vUV2;

	tangent = vTangent;
	biNormal = vBiNormal;
	boneID = vBoneID;
	boneWeight = vBoneWeight;
}
