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

cbuffer TRANSFORM : register(b0)
{
	float4x4 TransformMatrix;
}

cbuffer VIEWPROJ : register(b1)
{
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
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

OutputVertex main(VertexInfo input) 
{
	OutputVertex output; 
	float4 temp = float4(input.pos.xyz, 1);
	//temp = mul(temp, WorldMatrix);

	temp = mul(temp, TransformMatrix);
	//temp = mul(temp, BindMatrix);

	temp = mul(temp, ViewMatrix);
	temp = mul(temp, ProjectionMatrix);
	output.coordinate = temp; 
	output.normals = input.normals; 
	output.color = input.color; 
	output.uvs = input.uvs; 
	output.joints = input.joints; 
	output.weights = input.weights; 
	return output;
}