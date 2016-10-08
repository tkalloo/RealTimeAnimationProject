#pragma once
#include <d3d11.h>
#include <DirectXMath.h> 
#pragma comment (lib, "d3d11.lib")
using namespace DirectX;
using namespace std; 
#include "RenderSet.h"

#define BUFFER_WIDTH 1280
#define BUFFER_HEIGHT 720

struct VertexInfo
{
	XMFLOAT3 Position;
	XMFLOAT3 Normals;
	XMFLOAT4 Color;
	XMFLOAT2 UVs;
	XMINT4 JointWeightIndices; 
	XMFLOAT4 JointWeights; 
};

struct ViewAndProjectionMatrices
{
	XMFLOAT4X4 ViewMatrix;
	XMFLOAT4X4 ProjectionMatrix;
};
struct Skeleton; 
class RenderSet; 
class Interpolator; 
class XTime;
class Renderer
{
public:
	
	static IDXGISwapChain * SwapChain;
	static ID3D11Device * Device;
	static ID3D11DeviceContext * DeviceContext;
	static ID3D11RenderTargetView * RenderTargetView;
	static D3D11_VIEWPORT Viewport;
	static D3D_FEATURE_LEVEL * FeatureLevel;
	static ID3D11Resource * Backbuffer;
	static ID3D11Buffer * LoadedObjectBuffer;
	static ID3D11VertexShader * StationaryModelVertexShader;
	static ID3D11PixelShader * StationaryModelPixelShader;
	static ID3D11DepthStencilView * DepthStencilView; 

	static ID3D11Buffer * PerObjectConstantBuffer;
	static ID3D11Buffer * PerSkinnedObjectConstantBuffer;

	static ID3D11Texture2D * DepthBuffer;
	static ID3D11PixelShader * PixelShaderPtr; 
	static ID3D11VertexShader * VertexShaderPtr; 

	static XMFLOAT4X4 WorldMatrix;
	static XMFLOAT4X4 ViewMatrix;
	static XMFLOAT4X4 ProjectionMatrix;
	static ID3D11Buffer * MeshVertexBuffer;
	static ID3D11Buffer * MeshIndexBuffer;

	static ID3D11Buffer * MatrixBuffer;
	static ID3D11Buffer * WorldMatrixBuffer;
	static XMFLOAT4X4 ObjectPositionMatrix;

	static ID3D11VertexShader *AnimationVertexShaderPtr;
	//create the constant buffer we will use to interface with the shader side world and model-view-projection matrices

	static void BuildPerObjectConstantBuffers(); 
	static ViewAndProjectionMatrices ViewAndProjMatr;
	static ID3D11InputLayout * InputLayout;

	static UINT NumIndices;
	static ID3D11RasterizerState * RasterizerState;
	static ID3D11RasterizerState * FrontCullRasterizerState;

	Renderer();
	~Renderer();

	static void Initialize(HWND	*hWindow); 
	static void Render();
	static void Shutdown(); 
	static void PresentSwapChain(); 
	static void CameraMovement();
	static ID3D11Texture2D * Texture;
	static ID3D11Resource * TextureResource;
	static ID3D11ShaderResourceView* TextureResourceView;
	static ID3D11SamplerState * TextureSamplerState;
	static VertexInfo* SkeletalJoints; 

	static ID3D11VertexShader * SkeletalJointVertexShaderPtr;
	static ID3D11PixelShader * SkeletalJointPixelShaderPtr;

	static ID3D11Buffer * SkeletonJointVertexBuffers;
	static ID3D11Buffer * SkeletonJointIndexBuffers;

	static ID3D11Buffer * SkeletonJointIndexBuffer;


	static ID3D11Buffer * JointVertexBuffer; 
	//ID3D11Buffer * SkeletonJointIndexBuffer;
	static ID3D11Buffer * RenderJoints();

	static void RenderKeyFrames(void);

	//static int numJointsToRender;

	static XMFLOAT4X4 JointBindMatrices;

	//static XMFLOAT4X4 JointBinds[37];
	//static ID3D11Buffer * JointBindBuffers[37];

	static XMFLOAT4X4 JointTransforms;
	static XMFLOAT4X4 JointTransforms2;
	static XMFLOAT4X4 JointTransforms3;
	static XMFLOAT4X4 JointTransforms4;
	static XMFLOAT4X4 JointTransforms5;
	static XMFLOAT4X4 JointTransforms6;
	static XMFLOAT4X4 JointTransforms7;
	static XMFLOAT4X4 JointTransforms8;
	static XMFLOAT4X4 JointTransforms9;
	static XMFLOAT4X4 JointTransforms10;
	static XMFLOAT4X4 JointTransforms11;
	static XMFLOAT4X4 JointTransforms12;
	static XMFLOAT4X4 JointTransforms13;
	static XMFLOAT4X4 JointTransforms14;
	static XMFLOAT4X4 JointTransforms15;
	static XMFLOAT4X4 JointTransforms16;
	static XMFLOAT4X4 JointTransforms17;
	static XMFLOAT4X4 JointTransforms18;
	static XMFLOAT4X4 JointTransforms19;
	static XMFLOAT4X4 JointTransforms20;
	static XMFLOAT4X4 JointTransforms21;
	static XMFLOAT4X4 JointTransforms22;
	static XMFLOAT4X4 JointTransforms23;
	static XMFLOAT4X4 JointTransforms24;
	static XMFLOAT4X4 JointTransforms25;
	static XMFLOAT4X4 JointTransforms26;
	static XMFLOAT4X4 JointTransforms27;
	static XMFLOAT4X4 JointTransforms28;
	static XMFLOAT4X4 JointTransforms29;
	static XMFLOAT4X4 JointTransforms30;
	static XMFLOAT4X4 JointTransforms31;
	static XMFLOAT4X4 JointTransforms32;
	static XMFLOAT4X4 JointTransforms33;
	static XMFLOAT4X4 JointTransforms34;
	static XMFLOAT4X4 JointTransforms35;
	static XMFLOAT4X4 JointTransforms36;
	static XMFLOAT4X4 JointTransforms37;

	static ID3D11Buffer * JointConstBuffers;
	static ID3D11Buffer * JointConstBuffers2;
	static ID3D11Buffer * JointConstBuffers3;
	static ID3D11Buffer * JointConstBuffers4;
	static ID3D11Buffer * JointConstBuffers5;
	static ID3D11Buffer * JointConstBuffers6;
	static ID3D11Buffer * JointConstBuffers7;
	static ID3D11Buffer * JointConstBuffers8;
	static ID3D11Buffer * JointConstBuffers9;
	static ID3D11Buffer * JointConstBuffers10;
	static ID3D11Buffer * JointConstBuffers11;
	static ID3D11Buffer * JointConstBuffers12;
	static ID3D11Buffer * JointConstBuffers13;
	static ID3D11Buffer * JointConstBuffers14;
	static ID3D11Buffer * JointConstBuffers15;
	static ID3D11Buffer * JointConstBuffers16;
	static ID3D11Buffer * JointConstBuffers17;
	static ID3D11Buffer * JointConstBuffers18;
	static ID3D11Buffer * JointConstBuffers19;
	static ID3D11Buffer * JointConstBuffers20;
	static ID3D11Buffer * JointConstBuffers21;
	static ID3D11Buffer * JointConstBuffers22;
	static ID3D11Buffer * JointConstBuffers23;
	static ID3D11Buffer * JointConstBuffers24;
	static ID3D11Buffer * JointConstBuffers25;
	static ID3D11Buffer * JointConstBuffers26;
	static ID3D11Buffer * JointConstBuffers27;
	static ID3D11Buffer * JointConstBuffers28;
	static ID3D11Buffer * JointConstBuffers29;
	static ID3D11Buffer * JointConstBuffers30;
	static ID3D11Buffer * JointConstBuffers31;
	static ID3D11Buffer * JointConstBuffers32;
	static ID3D11Buffer * JointConstBuffers33;
	static ID3D11Buffer * JointConstBuffers34;
	static ID3D11Buffer * JointConstBuffers35;
	static ID3D11Buffer * JointConstBuffers36;
	static ID3D11Buffer * JointConstBuffers37;
	static Skeleton* ModelSkeleton;


	static ID3D11Buffer * SkyboxVertexBuffer;
	static ID3D11Buffer * SkyboxIndexBuffer;
	static ID3D11Texture2D * SkyboxDepthBuffer;
	static ID3D11Resource * SkyboxTextureResource;
	static ID3D11ShaderResourceView*SkyboxTextureResourceView;
	static ID3D11SamplerState * SkyboxTextureSamplerState;
	static ID3D11VertexShader * SkyboxVertexShaderPtr;
	static ID3D11PixelShader  * SkyboxPixelShaderPtr;
	static ID3D11DepthStencilView * SkyboxDepthStencilView;
	static Interpolator * JointInterpolator;
	static XMFLOAT4X4 SkyboxPositionMatrix;
	static XTime Timer;
	static ID3D11Buffer * SkyboxMatrixBuffer;
	static ID3D11Buffer * GroundVertexBuffer;
	static ID3D11Buffer * GroundIndexBuffer;

	static ID3D11Texture2D * GroundTexture;
	static ID3D11Resource * GroundTextureResource;
	static ID3D11ShaderResourceView* GroundTextureResourceView;
	static ID3D11SamplerState * GroundTextureSamplerState;

	static int numVertices;
	static VertexInfo ModelVerts[3588];
};

