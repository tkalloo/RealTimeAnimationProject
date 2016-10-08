#pragma pack_matrix(row_major)
TextureCube SkyboxTexture; 
struct InputVertex
{
	float4 coordinate : SV_POSITION;
	float3 uvs : TEXCOORD0;
};

SamplerState SkyboxSampler
{
	Filter = MIN_MAG_MIP_LINEAR; 
	AddressU = Wrap; 
	AddressV = Wrap; 
};

float4 main(InputVertex input) : SV_TARGET
{
	float4 Result = (float4)0;
	Result = SkyboxTexture.Sample(SkyboxSampler, input.uvs);
	return Result;
}