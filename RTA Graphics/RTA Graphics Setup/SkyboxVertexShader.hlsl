#pragma pack_matrix(row_major)
struct VertexInfo
{
	float3 pos : POSITION;
	float3 normals : NORMALS;
	float4 color : COLOR;
	float2 uvs : UV;
	int4 joints : JOINTS;
	float4 weights : WEIGHTS;
};

cbuffer WORLD : register(b0)
{
	float4x4 WorldMatrix;
}

cbuffer SKYBOX : register(b1)
{
	float4x4 SkyboxMatrix;
}


cbuffer VIEWS : register(b2)
{
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
};

struct OutputVertex
{
	float4 coordinate : SV_POSITION;
	float3 uvs : TEXCOORD0;
};

OutputVertex main(VertexInfo input)
{
	OutputVertex output = (OutputVertex)0; 
	float4 temp = float4(input.pos.xyz, 1);
	temp = mul(temp, SkyboxMatrix);

	temp = mul(temp, WorldMatrix);
	temp = mul(temp, ViewMatrix);
	temp = mul(temp, ProjectionMatrix);

	output.coordinate = temp.xyww; 
	output.uvs = input.pos.xyz; 
	return output;
}