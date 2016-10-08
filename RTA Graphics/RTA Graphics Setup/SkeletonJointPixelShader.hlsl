struct Input_info
{
	float4 coordinate : SV_POSITION;
	float3 normals : NORMALS;
	float4 color : COLOR;
	float2 uvs : UV;
	int4 joints : JOINTS;
	float4 weights : WEIGHTS;
};

float4 main() : SV_TARGET
{
	return float4(0.0f, 1.0f, 1.0f, 1.0f);
}