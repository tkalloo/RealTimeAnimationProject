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

cbuffer NEWPOS : register(b2)
{
	float4x4 NewPositions[37];
};

OutputVertex main(VertexInfo input)//main( float4 pos : POSITION ) : SV_POSITION
{
	OutputVertex Output = (OutputVertex)0;

	float4 temp = float4(input.pos.xyz, 1);

		float4x4 AnimationMatrix = NewPositions[input.joints.x];// *input.weights.x);
			 //AnimationMatrix +=(NewPositions[input.joints.y] * input.weights.y) * 20000;
			 //AnimationMatrix +=(NewPositions[input.joints.z] * input.weights.z) * 20000;
			 //AnimationMatrix +=(NewPositions[input.joints.w] * input.weights.w) * 20000;


	//temp = mul(temp, WorldMatrix);
	temp = mul(temp, AnimationMatrix); //X becomes NaN
	temp = mul(temp, ViewMatrix);
	temp = mul(temp, ProjectionMatrix);

	Output.coordinate = temp;
	Output.normals = mul(float4(input.normals, 1), AnimationMatrix).xyz;
	Output.uvs = input.uvs;
	Output.color = input.color;
	Output.joints = input.joints;
	Output.weights = input.weights;


	return Output;
}