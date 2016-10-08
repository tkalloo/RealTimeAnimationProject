//#pragma pack_matrix(row_major)
texture2D imgTexture: register(t0); 

SamplerState filter : register(s0);

struct VertexInfo
{
	float4 position : POSITION;
	float3 normals : NORMALS;
	float4 color : COLOR; 
	float2 uvs : UV;
	int4 joints : JOINTS; 
	float4 weights : WEIGHTS; 
};

struct Input_info
{
	float4 coordinate : SV_POSITION;
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

cbuffer VIEWS : register(b1)
{
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
};


float4 main(Input_info input) : SV_TARGET
{
	float4 ReturnTexture = (float4)0;
	ReturnTexture = imgTexture.Sample(filter, input.uvs);
	return ReturnTexture;
}