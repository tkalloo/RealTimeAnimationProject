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

struct OutputVertex
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

OutputVertex main(VertexInfo input)//main( float4 pos : POSITION ) : SV_POSITION
{
	OutputVertex Output = (OutputVertex)0; 

	float4 temp = float4(input.pos.xyz, 1);
	temp = mul(temp, WorldMatrix); 
	temp = mul(temp, ViewMatrix);
	temp = mul(temp, ProjectionMatrix);

	Output.coordinate = temp; 
	Output.normals = mul(float4(input.normals, 1), WorldMatrix).xyz; 
	Output.uvs = input.uvs; 
	Output.color = input.color; 
	Output.joints = input.joints; 
	Output.weights = input.weights; 


	return Output;
}