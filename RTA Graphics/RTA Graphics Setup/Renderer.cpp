#include "Renderer.h"
#include "RenderMesh.h"
#include "VertexShader.csh"
#include "PixelShader.csh"
#include "DDSTextureLoader.h"
#include "SkeletonJointPixelShader.csh"
#include "SkeletonJointVertexShader.csh"
#include "SkyboxVertexShader.csh"
#include "SkyboxPixelShader.csh"
#include "Interpolator.h"
#include "XTime.h"
#include "AnimationVertexShader.csh"
Renderer::Renderer()
{
}

IDXGISwapChain * Renderer::SwapChain = nullptr; 
ID3D11Device * Renderer::Device = nullptr;
ID3D11DeviceContext * Renderer::DeviceContext = nullptr;
ID3D11RenderTargetView * Renderer::RenderTargetView = nullptr;
D3D11_VIEWPORT Renderer::Viewport;
D3D_FEATURE_LEVEL * Renderer::FeatureLevel = nullptr;
ID3D11Resource *Renderer::Backbuffer = nullptr;
ID3D11DepthStencilView * Renderer::DepthStencilView = nullptr; 
ID3D11Texture2D * Renderer::DepthBuffer = nullptr; 

ID3D11PixelShader * Renderer::PixelShaderPtr = nullptr;
ID3D11VertexShader * Renderer::VertexShaderPtr = nullptr;

ID3D11Buffer * Renderer::MeshVertexBuffer = nullptr; 
ID3D11Buffer * Renderer::MeshIndexBuffer = nullptr; 

ID3D11Buffer * Renderer::MatrixBuffer = nullptr;
ID3D11Buffer * Renderer::WorldMatrixBuffer = nullptr;
ID3D11Buffer * Renderer::SkyboxMatrixBuffer = nullptr;

ID3D11RasterizerState * Renderer::RasterizerState = nullptr; 
ID3D11RasterizerState * Renderer::FrontCullRasterizerState = nullptr;

XMFLOAT4X4 Renderer::WorldMatrix;

XMFLOAT4X4 Renderer::ObjectPositionMatrix;
ViewAndProjectionMatrices Renderer::ViewAndProjMatr;
UINT Renderer::NumIndices; 
ID3D11InputLayout * Renderer::InputLayout = nullptr; 

ID3D11Texture2D * Renderer::Texture = nullptr; 
ID3D11Resource * Renderer::TextureResource = nullptr; 
ID3D11ShaderResourceView* Renderer::TextureResourceView = nullptr;
ID3D11SamplerState * Renderer::TextureSamplerState = nullptr; 

ID3D11Buffer * Renderer::SkeletonJointVertexBuffers = nullptr; 
ID3D11Buffer * Renderer::SkeletonJointIndexBuffers = nullptr;

ID3D11Buffer * Renderer::SkeletonJointIndexBuffer = nullptr;

ID3D11VertexShader * Renderer::SkeletalJointVertexShaderPtr = nullptr;
ID3D11PixelShader * Renderer::SkeletalJointPixelShaderPtr = nullptr;

XMFLOAT4X4 Renderer::JointBindMatrices;

Skeleton * Renderer::ModelSkeleton;

ID3D11Buffer * Renderer::JointVertexBuffer = nullptr;
ID3D11Buffer * Renderer::SkyboxVertexBuffer = nullptr;
ID3D11Buffer * Renderer::SkyboxIndexBuffer = nullptr;
ID3D11Texture2D * Renderer::SkyboxDepthBuffer = nullptr;
ID3D11Resource * Renderer::SkyboxTextureResource = nullptr;
ID3D11ShaderResourceView* Renderer::SkyboxTextureResourceView = nullptr;
ID3D11SamplerState * Renderer::SkyboxTextureSamplerState = nullptr;
ID3D11VertexShader * Renderer::SkyboxVertexShaderPtr = nullptr;
ID3D11PixelShader  * Renderer::SkyboxPixelShaderPtr = nullptr;
ID3D11DepthStencilView * Renderer::SkyboxDepthStencilView = nullptr;
Interpolator * Renderer::JointInterpolator = nullptr; 

XMFLOAT4X4 Renderer::SkyboxPositionMatrix;
ID3D11Buffer * Renderer::GroundVertexBuffer = nullptr;
ID3D11Buffer * Renderer::GroundIndexBuffer = nullptr;

ID3D11Texture2D * Renderer::GroundTexture = nullptr;
ID3D11Resource * Renderer::GroundTextureResource = nullptr;
ID3D11ShaderResourceView* Renderer::GroundTextureResourceView = nullptr;
ID3D11SamplerState * Renderer::GroundTextureSamplerState = nullptr;

ID3D11VertexShader * Renderer::AnimationVertexShaderPtr = nullptr;


XTime Renderer::Timer;
int Renderer::numVertices = 0;
VertexInfo Renderer::ModelVerts[3588]; 
#pragma region Joint Info
XMFLOAT4X4 Renderer::JointTransforms;
XMFLOAT4X4 Renderer::JointTransforms2;
XMFLOAT4X4 Renderer::JointTransforms3;
XMFLOAT4X4 Renderer::JointTransforms4;
XMFLOAT4X4 Renderer::JointTransforms5;
XMFLOAT4X4 Renderer::JointTransforms6;
XMFLOAT4X4 Renderer::JointTransforms7;
XMFLOAT4X4 Renderer::JointTransforms8;
XMFLOAT4X4 Renderer::JointTransforms9;
XMFLOAT4X4 Renderer::JointTransforms10;
XMFLOAT4X4 Renderer::JointTransforms11;
XMFLOAT4X4 Renderer::JointTransforms12;
XMFLOAT4X4 Renderer::JointTransforms13;
XMFLOAT4X4 Renderer::JointTransforms14;
XMFLOAT4X4 Renderer::JointTransforms15;
XMFLOAT4X4 Renderer::JointTransforms16;
XMFLOAT4X4 Renderer::JointTransforms17;
XMFLOAT4X4 Renderer::JointTransforms18;
XMFLOAT4X4 Renderer::JointTransforms19;
XMFLOAT4X4 Renderer::JointTransforms20;
XMFLOAT4X4 Renderer::JointTransforms21;
XMFLOAT4X4 Renderer::JointTransforms22;
XMFLOAT4X4 Renderer::JointTransforms23;
XMFLOAT4X4 Renderer::JointTransforms24;
XMFLOAT4X4 Renderer::JointTransforms25;
XMFLOAT4X4 Renderer::JointTransforms26;
XMFLOAT4X4 Renderer::JointTransforms27;
XMFLOAT4X4 Renderer::JointTransforms28;
XMFLOAT4X4 Renderer::JointTransforms29;
XMFLOAT4X4 Renderer::JointTransforms30;
XMFLOAT4X4 Renderer::JointTransforms31;
XMFLOAT4X4 Renderer::JointTransforms32;
XMFLOAT4X4 Renderer::JointTransforms33;
XMFLOAT4X4 Renderer::JointTransforms34;
XMFLOAT4X4 Renderer::JointTransforms35;
XMFLOAT4X4 Renderer::JointTransforms36;
XMFLOAT4X4 Renderer::JointTransforms37;

ID3D11Buffer * Renderer::JointConstBuffers;
ID3D11Buffer * Renderer::JointConstBuffers2;
ID3D11Buffer * Renderer::JointConstBuffers3 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers4 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers5 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers6 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers7 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers8 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers9 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers10 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers11 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers12 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers13 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers14 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers15 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers16 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers17 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers18 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers19 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers20 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers21 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers22 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers23 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers24 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers25 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers26 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers27 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers28 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers29 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers30 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers31 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers32 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers33 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers34 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers35 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers36 = nullptr;
ID3D11Buffer * Renderer::JointConstBuffers37 = nullptr;

#pragma endregion




Renderer::~Renderer()
{
	Shutdown(); 
}

void Renderer::CameraMovement()
{
	if (GetAsyncKeyState('W'))
	{
		XMMATRIX Translation = XMMatrixTranslation(0.0f, 0.0f, -1.0f);
		XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
		XMMATRIX Sum = XMMatrixMultiply(TempView, Translation);
		XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Sum);
		 
		XMMATRIX SkyboxScale = XMMatrixScaling(500.0f, 500.0f, 500.0f); 
		XMMATRIX SkyboxTranslation = XMMatrixTranslation(ViewAndProjMatr.ViewMatrix._41 *2.0f, ViewAndProjMatr.ViewMatrix._42 *2.0f, ViewAndProjMatr.ViewMatrix._43 *2.0f);
		XMMATRIX SkyboxPos = SkyboxScale * SkyboxTranslation;
		XMStoreFloat4x4(&SkyboxPositionMatrix, SkyboxPos);
	}

	if (GetAsyncKeyState('A'))
	{
		XMMATRIX Translation = XMMatrixTranslation(1.0f, 0.0f, 0.0f);
		XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
		XMMATRIX Sum = XMMatrixMultiply(TempView, Translation);
		XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Sum);

		XMMATRIX SkyboxScale = XMMatrixScaling(500.0f, 500.0f, 500.0f);
		XMMATRIX SkyboxTranslation = XMMatrixTranslation(ViewAndProjMatr.ViewMatrix._41 *2.0f, ViewAndProjMatr.ViewMatrix._42 *2.0f, ViewAndProjMatr.ViewMatrix._43 *2.0f);
		XMMATRIX SkyboxPos = SkyboxScale * SkyboxTranslation;
		XMStoreFloat4x4(&SkyboxPositionMatrix, SkyboxPos);
	}

	if (GetAsyncKeyState('S'))
	{
		XMMATRIX Translation = XMMatrixTranslation(0.0f, 0.0f, 1.0f);
		XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
		XMMATRIX Sum = XMMatrixMultiply(TempView, Translation);
		XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Sum);

		XMMATRIX SkyboxScale = XMMatrixScaling(500.0f, 500.0f, 500.0f);
		XMMATRIX SkyboxTranslation = XMMatrixTranslation(ViewAndProjMatr.ViewMatrix._41 *2.0f, ViewAndProjMatr.ViewMatrix._42 *2.0f, ViewAndProjMatr.ViewMatrix._43 *2.0f);
		XMMATRIX SkyboxPos = SkyboxScale * SkyboxTranslation;
		XMStoreFloat4x4(&SkyboxPositionMatrix, SkyboxPos);
	}

	if (GetAsyncKeyState('D'))
	{
		XMMATRIX Translation = XMMatrixTranslation(-1.0f, 0.0f, 0.0f);
		XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
		XMMATRIX Sum = XMMatrixMultiply(TempView, Translation);
		XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Sum);

		XMMATRIX SkyboxScale = XMMatrixScaling(500.0f, 500.0f, 500.0f);
		XMMATRIX SkyboxTranslation = XMMatrixTranslation(ViewAndProjMatr.ViewMatrix._41 *2.0f, ViewAndProjMatr.ViewMatrix._42 *2.0f, ViewAndProjMatr.ViewMatrix._43 *2.0f);
		XMMATRIX SkyboxPos = SkyboxScale * SkyboxTranslation;
		XMStoreFloat4x4(&SkyboxPositionMatrix, SkyboxPos);
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		XMMATRIX Translation = XMMatrixTranslation(0.0f, -1.0f, 0.0f);
		XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
		XMMATRIX Sum = XMMatrixMultiply(TempView, Translation);
		XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Sum);

		XMMATRIX SkyboxScale = XMMatrixScaling(500.0f, 500.0f, 500.0f);
		XMMATRIX SkyboxTranslation = XMMatrixTranslation(ViewAndProjMatr.ViewMatrix._41 *2.0f, ViewAndProjMatr.ViewMatrix._42 *2.0f, ViewAndProjMatr.ViewMatrix._43 *2.0f);
		XMMATRIX SkyboxPos = SkyboxScale * SkyboxTranslation;
		XMStoreFloat4x4(&SkyboxPositionMatrix, SkyboxPos);
	}
	if (GetAsyncKeyState(VK_LSHIFT))
	{
		XMMATRIX Translation = XMMatrixTranslation(0.0f, 1.0f, 0.0f);
		XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
		XMMATRIX Sum = XMMatrixMultiply(TempView, Translation);
		XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Sum);

		XMMATRIX SkyboxScale = XMMatrixScaling(500.0f, 500.0f, 500.0f);
		XMMATRIX SkyboxTranslation = XMMatrixTranslation(ViewAndProjMatr.ViewMatrix._41 *2.0f, ViewAndProjMatr.ViewMatrix._42 *2.0f, ViewAndProjMatr.ViewMatrix._43 *2.0f);
		XMMATRIX SkyboxPos = SkyboxScale * SkyboxTranslation;
		XMStoreFloat4x4(&SkyboxPositionMatrix, SkyboxPos);
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
		XMMATRIX Rotation = XMMatrixMultiply(TempView, XMMatrixRotationY(0.01f));
		XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Rotation);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
		XMMATRIX Rotation = XMMatrixMultiply(TempView, XMMatrixRotationY(-0.01f));
		XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Rotation);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
		XMMATRIX Rotation = XMMatrixMultiply(TempView, XMMatrixRotationX(-0.01f));
		XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Rotation);
	}

	if (GetAsyncKeyState(VK_UP))
	{
		XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
		XMMATRIX Rotation = XMMatrixMultiply(TempView, XMMatrixRotationX(0.01f));
		XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Rotation);
	}
}

ID3D11Buffer * Renderer::RenderJoints()
{
	VertexInfo NewCube[8]; 
	VertexInfo Temp; 
	Temp.Position.x = 1.0f;
	Temp.Position.y = 1.0f;
	Temp.Position.z = 1.0f;

	Temp.Color.x = 1.0f;
	Temp.Color.y = 1.0f;
	Temp.Color.z = 1.0f;
	Temp.Color.w = 1.0f;

	Temp.Normals.x = 1.0f;
	Temp.Normals.y = 1.0f;
	Temp.Normals.z = 1.0f;

	Temp.UVs.x = 1.0f;
	Temp.UVs.y = 1.0f;


	for (unsigned int i = 0; i < 8; i++)
	{
		NewCube[i].Color = Temp.Color;
		NewCube[i].Position = Temp.Position;
		NewCube[i].Normals = Temp.Normals;
		NewCube[i].UVs = Temp.UVs;
	}

	
	//WARNING: DOUBLE CHECK ROTATION 
	//Front Upper Left Corner
	NewCube[0].Position.x -= 5.0f;
	NewCube[0].Position.y += 5.0f;
	NewCube[0].Position.z += 5.0f;

	//Front Upper Right Corner
	NewCube[1].Position.x += 5.0f;
	NewCube[1].Position.y += 5.0f;
	NewCube[1].Position.z += 5.0f;

	//Front Lower Left Corner
	NewCube[2].Position.x -= 5.0f;
	NewCube[2].Position.y -= 5.0f;
	NewCube[2].Position.z += 5.0f;

	//Front Lower Right Corner
	NewCube[3].Position.x += 5.0f;
	NewCube[3].Position.y -= 5.0f;
	NewCube[3].Position.z += 5.0f;


	//Back Upper Left Corner
	NewCube[4].Position.x += 5.0f;
	NewCube[4].Position.y += 5.0f;
	NewCube[4].Position.z -= 5.0f;

	//Back Upper Right Corner
	NewCube[5].Position.x += 5.0f;
	NewCube[5].Position.y -= 5.0f;
	NewCube[5].Position.z -= 5.0f;

	//Back Lower Left Corner
	NewCube[6].Position.x -= 5.0f;
	NewCube[6].Position.y += 5.0f;
	NewCube[6].Position.z -= 5.0f;

	//Back Lower Right Corner
	NewCube[7].Position.x -= 5.0f;
	NewCube[7].Position.y -= 5.0f;
	NewCube[7].Position.z -= 5.0f;


	ID3D11Buffer * TempSkeletonVertexBuffer;
	D3D11_BUFFER_DESC CubeBufferDesc;
	ZeroMemory(&CubeBufferDesc, sizeof(CubeBufferDesc));

	CubeBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	CubeBufferDesc.ByteWidth = sizeof(VertexInfo) *8;
	CubeBufferDesc.CPUAccessFlags = NULL;
	CubeBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA CubeSubresourceData;
	CubeSubresourceData.SysMemPitch = 0;
	CubeSubresourceData.pSysMem = NewCube;
	CubeSubresourceData.SysMemSlicePitch = 0;

	HRESULT Result = Device->CreateBuffer(&CubeBufferDesc, &CubeSubresourceData, &TempSkeletonVertexBuffer);

	//SkeletonJointIndexBuffers[counter] = TempSkeletonVertexBuffer; 

	unsigned int CubeIndexArray[] = { 0, 1, 2,
									  1, 3, 2,
									  1, 4, 3,
									  4, 5, 3,
									  4, 6, 5,
									  6, 7, 5,
									  6, 0, 7,
									  0, 2, 7,
									  6, 4, 1,
									  6, 1, 0,
									  7, 5, 3,
									  7, 3, 2};

	D3D11_BUFFER_DESC CubeIndexBuffDesc;
	ZeroMemory(&CubeIndexBuffDesc, sizeof(CubeIndexBuffDesc));

	CubeIndexBuffDesc.ByteWidth = sizeof(int) * 36;
	CubeIndexBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CubeIndexBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	CubeIndexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	CubeIndexBuffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA CubeIndexSubresourceData;

	CubeIndexSubresourceData.pSysMem = CubeIndexArray;
	CubeIndexSubresourceData.SysMemPitch = 0;
	CubeIndexSubresourceData.SysMemSlicePitch = 0;

	Result = Device->CreateBuffer(&CubeIndexBuffDesc, &CubeIndexSubresourceData, &SkeletonJointIndexBuffer);
	return TempSkeletonVertexBuffer; 
}

void Renderer::Initialize(HWND *hWindow)
{
	RenderMesh Mesh; 
	HRESULT Result; 
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));

	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	SwapChainDesc.OutputWindow = *hWindow;
	SwapChainDesc.Windowed = true;

	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.Height = BUFFER_HEIGHT;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	SwapChainDesc.BufferDesc.Width = BUFFER_WIDTH;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	FeatureLevel = new D3D_FEATURE_LEVEL;

	UINT flag;
	if (_DEBUG)
		flag = D3D11_CREATE_DEVICE_DEBUG;
	else
		flag = D3D11_CREATE_DEVICE_SINGLETHREADED;

	Result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flag, NULL, NULL, D3D11_SDK_VERSION,
		&SwapChainDesc, &SwapChain, &Device, FeatureLevel, &DeviceContext);

 	Backbuffer = nullptr;
	Result = SwapChain->GetBuffer(0, __uuidof(Backbuffer), reinterpret_cast<void**>(&Backbuffer));

	Result = Device->CreateRenderTargetView(Backbuffer, NULL, &RenderTargetView);

	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	Viewport.Height = BUFFER_HEIGHT;
	Viewport.Width = BUFFER_WIDTH;
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;


	D3D11_TEXTURE2D_DESC DepthStencilDesc; 
	ZeroMemory(&DepthStencilDesc, sizeof(DepthStencilDesc)); 

	DepthStencilDesc.ArraySize = 1; 
	DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; 
	DepthStencilDesc.CPUAccessFlags = 0;
	DepthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT; 
	DepthStencilDesc.Height = BUFFER_HEIGHT; 
	DepthStencilDesc.Width = BUFFER_WIDTH; 
	DepthStencilDesc.MipLevels = 1; 
	DepthStencilDesc.MiscFlags = 0; 
	DepthStencilDesc.SampleDesc.Count = 1;
	DepthStencilDesc.SampleDesc.Quality = 0;
	DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT; 

	Result = Device->CreateTexture2D(&DepthStencilDesc, NULL, &DepthBuffer);


	D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc; 
	ZeroMemory(&DepthStencilViewDesc, sizeof(DepthStencilViewDesc)); 

	DepthStencilViewDesc.Flags = 0; 
	DepthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT; 
	DepthStencilViewDesc.Texture2D.MipSlice = 0; 
	DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; 
	Result = Device->CreateDepthStencilView(DepthBuffer, &DepthStencilViewDesc, &DepthStencilView);

	D3D11_INPUT_ELEMENT_DESC Layout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMALS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "JOINTS", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "WEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};

	XMStoreFloat4x4(&SkyboxPositionMatrix, XMMatrixIdentity());

	Result = Device->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &VertexShaderPtr);

	Result = Device->CreateVertexShader(AnimationVertexShader, sizeof(AnimationVertexShader), NULL, &AnimationVertexShaderPtr);


	Result = Device->CreateInputLayout(Layout, 6, VertexShader, sizeof(VertexShader), &InputLayout);

	Result = Device->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, &PixelShaderPtr);

	ModelSkeleton = new Skeleton;

	RenderMesh * NewMesh = Mesh.LoadMeshFromBinary("Teddy_Run.mesh"); 
	if (nullptr == NewMesh)
		return; //Should throw exception instead

	Mesh.LoadJointsFromBinary(ModelSkeleton, "Teddy_Run.Joint");

	Mesh.LoadAnimationFromBinary(ModelSkeleton, "Teddy_Run.animation");

	JointInterpolator = new Interpolator; 

	//ModelVerts = new VertexInfo[NewMesh->numVerts]; 
	int BlendInfoCounter = 0; 

	numVertices = NewMesh->numVerts;
	for (int i = 0; i < 3588 /*NewMesh->numVerts*/; i++)
	{
		//ModelVerts[i] = new VertexInfo;
		VertexInfo*  temp = new VertexInfo;
		ModelVerts[i].Position.x = NewMesh->Positions[i].x;
		ModelVerts[i].Position.y = NewMesh->Positions[i].y;
		ModelVerts[i].Position.z = NewMesh->Positions[i].z;

		ModelVerts[i].Normals.x = NewMesh->Normals[i].x;
		ModelVerts[i].Normals.y = NewMesh->Normals[i].y;
		ModelVerts[i].Normals.z = NewMesh->Normals[i].z;

		ModelVerts[i].UVs.x = NewMesh->UVs[i].x;
		ModelVerts[i].UVs.y = 1 - NewMesh->UVs[i].y;

		ModelVerts[i].JointWeights.x = 0.0f;
		ModelVerts[i].JointWeights.y = 0.0f;
		ModelVerts[i].JointWeights.z = 0.0f;
		ModelVerts[i].JointWeights.w = 0.0f;

		ModelVerts[i].JointWeightIndices.x = 0;
		ModelVerts[i].JointWeightIndices.y = 0;
		ModelVerts[i].JointWeightIndices.z = 0;
		ModelVerts[i].JointWeightIndices.w = 0;

		if (1 == NewMesh->NumberOfBlendInfo[i])
		{
			ModelVerts[i].JointWeights.x = NewMesh->BlendWeights[BlendInfoCounter];
			ModelVerts[i].JointWeightIndices.x = NewMesh->BlendIndices[BlendInfoCounter];
			BlendInfoCounter++;
		}
		if (2 == NewMesh->NumberOfBlendInfo[i])
		{
			ModelVerts[i].JointWeights.x = NewMesh->BlendWeights[BlendInfoCounter];
			ModelVerts[i].JointWeightIndices.x = NewMesh->BlendIndices[BlendInfoCounter];
			BlendInfoCounter++;
			ModelVerts[i].JointWeights.y = NewMesh->BlendWeights[BlendInfoCounter];
			ModelVerts[i].JointWeightIndices.y = NewMesh->BlendIndices[BlendInfoCounter];
			BlendInfoCounter++;
		}
		if (3 == NewMesh->NumberOfBlendInfo[i])
		{
			ModelVerts[i].JointWeights.x = NewMesh->BlendWeights[BlendInfoCounter];
			ModelVerts[i].JointWeightIndices.x = NewMesh->BlendIndices[BlendInfoCounter];
			BlendInfoCounter++;
			ModelVerts[i].JointWeights.y = NewMesh->BlendWeights[BlendInfoCounter];
			ModelVerts[i].JointWeightIndices.y = NewMesh->BlendIndices[BlendInfoCounter];
			BlendInfoCounter++;
			ModelVerts[i].JointWeights.z = NewMesh->BlendWeights[BlendInfoCounter];
			ModelVerts[i].JointWeightIndices.z = NewMesh->BlendIndices[BlendInfoCounter];
			BlendInfoCounter++;
		}
		if (4 == NewMesh->NumberOfBlendInfo[i])
		{
			ModelVerts[i].JointWeights.x = NewMesh->BlendWeights[BlendInfoCounter];
			ModelVerts[i].JointWeightIndices.x = NewMesh->BlendIndices[BlendInfoCounter];
			BlendInfoCounter++;
			ModelVerts[i].JointWeights.y = NewMesh->BlendWeights[BlendInfoCounter];
			ModelVerts[i].JointWeightIndices.y = NewMesh->BlendIndices[BlendInfoCounter];
			BlendInfoCounter++;
			ModelVerts[i].JointWeights.z = NewMesh->BlendWeights[BlendInfoCounter];
			ModelVerts[i].JointWeightIndices.z = NewMesh->BlendIndices[BlendInfoCounter];
			BlendInfoCounter++;
			ModelVerts[i].JointWeights.w = NewMesh->BlendWeights[BlendInfoCounter];
			ModelVerts[i].JointWeightIndices.w = NewMesh->BlendIndices[BlendInfoCounter];
			BlendInfoCounter++;
		}
	
	}
	int c = 0; 

	//for (int currJoint = 0; currJoint < ModelSkeleton->numJoints; currJoint++)
	//{
	//	Joint * LoadedJoint = new Joint;
	//	LoadedJoint->numKeyframes = JointMesh->KeyFrameNumberVec[currJoint];
	//	LoadedJoint->BindMatrix = JointMesh->BindMatrices[currJoint];
	//	
	//	LoadedJoint->Keyframes= JointMesh->EachJointsKeyFrames[currJoint];
	//	ModelSkeleton->Joints.push_back(LoadedJoint);
	//}

#pragma region Joint Transform setup
	ModelSkeleton->TotalAnimationDuration *= 0.001f;

	for (int currJoint = 0; currJoint < ModelSkeleton->numJoints; currJoint++) //For each joint
	{
		XMMATRIX TempBind = XMMatrixTranspose(XMLoadFloat4x4(&ModelSkeleton->Joints[currJoint]->BindMatrix));
		XMStoreFloat4x4(&ModelSkeleton->Joints[currJoint]->BindMatrix, TempBind);


		for (int CurrKeyFrame = 0; CurrKeyFrame < ModelSkeleton->Joints[currJoint]->numKeyframes; CurrKeyFrame++) //For each keyframe in each joint
		{
			ModelSkeleton->Joints[currJoint]->Keyframes[CurrKeyFrame]->animationTime = (((CurrKeyFrame*1.0f) / (ModelSkeleton->Joints[currJoint]->numKeyframes*1.0f)) *  ModelSkeleton->TotalAnimationDuration);
			if (CurrKeyFrame + 1 < ModelSkeleton->Joints[currJoint]->numKeyframes)
				ModelSkeleton->Joints[currJoint]->Keyframes[CurrKeyFrame]->Next = ModelSkeleton->Joints[currJoint]->Keyframes[CurrKeyFrame + 1];
			else
				ModelSkeleton->Joints[currJoint]->Keyframes[CurrKeyFrame]->Next = nullptr; //NOTE: Set back to the beginning to loop? But that won't work if joint has less frames
		}
	}

	JointTransforms = ModelSkeleton->Joints[0]->Keyframes[0]->TransformationMatrix;

	XMMATRIX TempTranspose = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms));
	XMStoreFloat4x4(&JointTransforms, TempTranspose);
	JointTransforms.m[0][2] *= -1.0f;
	JointTransforms.m[1][2] *= -1.0f;
	JointTransforms.m[2][0] *= -1.0f;
	JointTransforms.m[2][1] *= -1.0f;
	JointTransforms.m[3][2] *= -1.0f;
	JointTransforms2 = ModelSkeleton->Joints[1]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose2 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms2));
	XMStoreFloat4x4(&JointTransforms2, TempTranspose2);

	//This is how to handle system handedness
	JointTransforms2.m[0][2] *= -1.0f;
	JointTransforms2.m[1][2] *= -1.0f;
	JointTransforms2.m[2][0] *= -1.0f; 
	JointTransforms2.m[2][1] *= -1.0f; 
	JointTransforms2.m[3][2] *= -1.0f; 


	JointTransforms3 = ModelSkeleton->Joints[2]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose3 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms3));
	XMStoreFloat4x4(&JointTransforms3, TempTranspose3);
	JointTransforms3.m[0][2] *= -1.0f;
	JointTransforms3.m[1][2] *= -1.0f;
	JointTransforms3.m[2][0] *= -1.0f;
	JointTransforms3.m[2][1] *= -1.0f;
	JointTransforms3.m[3][2] *= -1.0f;


	JointTransforms4 = ModelSkeleton->Joints[3]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose4 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms4));
	XMStoreFloat4x4(&JointTransforms4, TempTranspose4);
	JointTransforms4.m[0][2] *= -1.0f;
	JointTransforms4.m[1][2] *= -1.0f;
	JointTransforms4.m[2][0] *= -1.0f;
	JointTransforms4.m[2][1] *= -1.0f;
	JointTransforms4.m[3][2] *= -1.0f;

	JointTransforms5 = ModelSkeleton->Joints[4]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose5 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms5));
	XMStoreFloat4x4(&JointTransforms5, TempTranspose5);
	JointTransforms5._13 *= -1.0f;
	JointTransforms5._23 *= -1.0f;
	JointTransforms5._31 *= -1.0f;
	JointTransforms5._32 *= -1.0f;
	JointTransforms5._43 *= -1.0f;

	JointTransforms6 = ModelSkeleton->Joints[5]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose6 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms6));
	XMStoreFloat4x4(&JointTransforms6, TempTranspose6);
	JointTransforms6.m[0][2] *= -1.0f;
	JointTransforms6.m[1][2] *= -1.0f;
	JointTransforms6.m[2][0] *= -1.0f;
	JointTransforms6.m[2][1] *= -1.0f;
	JointTransforms6.m[3][2] *= -1.0f;



	JointTransforms7 = ModelSkeleton->Joints[6]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose7 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms7));
	XMStoreFloat4x4(&JointTransforms7, TempTranspose7);
	JointTransforms7.m[0][2] *= -1.0f;
	JointTransforms7.m[1][2] *= -1.0f;
	JointTransforms7.m[2][0] *= -1.0f;
	JointTransforms7.m[2][1] *= -1.0f;
	JointTransforms7.m[3][2] *= -1.0f;


	JointTransforms8 = ModelSkeleton->Joints[7]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose8 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms8));
	XMStoreFloat4x4(&JointTransforms8, TempTranspose8);
	JointTransforms8.m[0][2] *= -1.0f;
	JointTransforms8.m[1][2] *= -1.0f;
	JointTransforms8.m[2][0] *= -1.0f;
	JointTransforms8.m[2][1] *= -1.0f;
	JointTransforms8.m[3][2] *= -1.0f;


	JointTransforms9 = ModelSkeleton->Joints[8]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose9 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms9));
	XMStoreFloat4x4(&JointTransforms9, TempTranspose9);
	JointTransforms9.m[0][2] *= -1.0f;
	JointTransforms9.m[1][2] *= -1.0f;
	JointTransforms9.m[2][0] *= -1.0f;
	JointTransforms9.m[2][1] *= -1.0f;
	JointTransforms9.m[3][2] *= -1.0f;

	JointTransforms10 = ModelSkeleton->Joints[9]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose10 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms10));
	XMStoreFloat4x4(&JointTransforms10, TempTranspose10);
	JointTransforms10.m[0][2] *= -1.0f;
	JointTransforms10.m[1][2] *= -1.0f;
	JointTransforms10.m[2][0] *= -1.0f;
	JointTransforms10.m[2][1] *= -1.0f;
	JointTransforms10.m[3][2] *= -1.0f;


	JointTransforms11 = ModelSkeleton->Joints[10]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose11 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms11));
	XMStoreFloat4x4(&JointTransforms11, TempTranspose11);
	JointTransforms11.m[0][2] *= -1.0f;
	JointTransforms11.m[1][2] *= -1.0f;
	JointTransforms11.m[2][0] *= -1.0f;
	JointTransforms11.m[2][1] *= -1.0f;
	JointTransforms11.m[3][2] *= -1.0f;


	JointTransforms12 = ModelSkeleton->Joints[11]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose12 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms12));
	XMStoreFloat4x4(&JointTransforms12, TempTranspose12);
	JointTransforms12.m[0][2] *= -1.0f;
	JointTransforms12.m[1][2] *= -1.0f;
	JointTransforms12.m[2][0] *= -1.0f;
	JointTransforms12.m[2][1] *= -1.0f;
	JointTransforms12.m[3][2] *= -1.0f;


	JointTransforms13 = ModelSkeleton->Joints[12]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose13 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms13));
	XMStoreFloat4x4(&JointTransforms13, TempTranspose13);
	JointTransforms13.m[0][2] *= -1.0f;
	JointTransforms13.m[1][2] *= -1.0f;
	JointTransforms13.m[2][0] *= -1.0f;
	JointTransforms13.m[2][1] *= -1.0f;
	JointTransforms13.m[3][2] *= -1.0f;


	JointTransforms14 = ModelSkeleton->Joints[13]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose14 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms14));
	XMStoreFloat4x4(&JointTransforms14, TempTranspose14);
	JointTransforms14.m[0][2] *= -1.0f;
	JointTransforms14.m[1][2] *= -1.0f;
	JointTransforms14.m[2][0] *= -1.0f;
	JointTransforms14.m[2][1] *= -1.0f;
	JointTransforms14.m[3][2] *= -1.0f;


	JointTransforms15 = ModelSkeleton->Joints[14]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose15 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms15));
	XMStoreFloat4x4(&JointTransforms15, TempTranspose15);
	JointTransforms15.m[0][2] *= -1.0f;
	JointTransforms15.m[1][2] *= -1.0f;
	JointTransforms15.m[2][0] *= -1.0f;
	JointTransforms15.m[2][1] *= -1.0f;
	JointTransforms15.m[3][2] *= -1.0f;


	JointTransforms16 = ModelSkeleton->Joints[15]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose16 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms16));
	XMStoreFloat4x4(&JointTransforms16, TempTranspose16);
	JointTransforms16.m[0][2] *= -1.0f;
	JointTransforms16.m[1][2] *= -1.0f;
	JointTransforms16.m[2][0] *= -1.0f;
	JointTransforms16.m[2][1] *= -1.0f;
	JointTransforms16.m[3][2] *= -1.0f;


	JointTransforms17 = ModelSkeleton->Joints[16]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose17 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms17));
	XMStoreFloat4x4(&JointTransforms17, TempTranspose17);
	JointTransforms17.m[0][2] *= -1.0f;
	JointTransforms17.m[1][2] *= -1.0f;
	JointTransforms17.m[2][0] *= -1.0f;
	JointTransforms17.m[2][1] *= -1.0f;
	JointTransforms17.m[3][2] *= -1.0f;


	JointTransforms18 = ModelSkeleton->Joints[17]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose18 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms18));
	XMStoreFloat4x4(&JointTransforms18, TempTranspose18);
	JointTransforms18.m[0][2] *= -1.0f;
	JointTransforms18.m[1][2] *= -1.0f;
	JointTransforms18.m[2][0] *= -1.0f;
	JointTransforms18.m[2][1] *= -1.0f;
	JointTransforms18.m[3][2] *= -1.0f;


	JointTransforms19 = ModelSkeleton->Joints[18]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose19 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms19));
	XMStoreFloat4x4(&JointTransforms19, TempTranspose19);
	JointTransforms19.m[0][2] *= -1.0f;
	JointTransforms19.m[1][2] *= -1.0f;
	JointTransforms19.m[2][0] *= -1.0f;
	JointTransforms19.m[2][1] *= -1.0f;
	JointTransforms19.m[3][2] *= -1.0f;


	JointTransforms20 = ModelSkeleton->Joints[19]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose20 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms20));
	XMStoreFloat4x4(&JointTransforms20, TempTranspose20);
	JointTransforms20.m[0][2] *= -1.0f;
	JointTransforms20.m[1][2] *= -1.0f;
	JointTransforms20.m[2][0] *= -1.0f;
	JointTransforms20.m[2][1] *= -1.0f;
	JointTransforms20.m[3][2] *= -1.0f;

	JointTransforms21 = ModelSkeleton->Joints[20]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose21 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms21));
	XMStoreFloat4x4(&JointTransforms21, TempTranspose21);
	JointTransforms21.m[0][2] *= -1.0f;
	JointTransforms21.m[1][2] *= -1.0f;
	JointTransforms21.m[2][0] *= -1.0f;
	JointTransforms21.m[2][1] *= -1.0f;
	JointTransforms21.m[3][2] *= -1.0f;

	JointTransforms22 = ModelSkeleton->Joints[21]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose22 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms22));
	XMStoreFloat4x4(&JointTransforms22, TempTranspose22);
	JointTransforms22.m[0][2] *= -1.0f;
	JointTransforms22.m[1][2] *= -1.0f;
	JointTransforms22.m[2][0] *= -1.0f;
	JointTransforms22.m[2][1] *= -1.0f;
	JointTransforms22.m[3][2] *= -1.0f;

	JointTransforms23 = ModelSkeleton->Joints[22]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose23 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms23));
	XMStoreFloat4x4(&JointTransforms23, TempTranspose23);
	JointTransforms23.m[0][2] *= -1.0f;
	JointTransforms23.m[1][2] *= -1.0f;
	JointTransforms23.m[2][0] *= -1.0f;
	JointTransforms23.m[2][1] *= -1.0f;
	JointTransforms23.m[3][2] *= -1.0f;

	JointTransforms24 = ModelSkeleton->Joints[23]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose24 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms24));
	XMStoreFloat4x4(&JointTransforms24, TempTranspose24);
	JointTransforms24.m[0][2] *= -1.0f;
	JointTransforms24.m[1][2] *= -1.0f;
	JointTransforms24.m[2][0] *= -1.0f;
	JointTransforms24.m[2][1] *= -1.0f;
	JointTransforms24.m[3][2] *= -1.0f;

	JointTransforms25 = ModelSkeleton->Joints[24]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose25 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms25));
	XMStoreFloat4x4(&JointTransforms25, TempTranspose25);
	JointTransforms25.m[0][2] *= -1.0f;
	JointTransforms25.m[1][2] *= -1.0f;
	JointTransforms25.m[2][0] *= -1.0f;
	JointTransforms25.m[2][1] *= -1.0f;
	JointTransforms25.m[3][2] *= -1.0f;

	JointTransforms26 = ModelSkeleton->Joints[25]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose26 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms26));
	XMStoreFloat4x4(&JointTransforms26, TempTranspose26);
	JointTransforms26.m[0][2] *= -1.0f;
	JointTransforms26.m[1][2] *= -1.0f;
	JointTransforms26.m[2][0] *= -1.0f;
	JointTransforms26.m[2][1] *= -1.0f;
	JointTransforms26.m[3][2] *= -1.0f;

	JointTransforms27 = ModelSkeleton->Joints[26]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose27 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms27));
	XMStoreFloat4x4(&JointTransforms27, TempTranspose27);
	JointTransforms27.m[0][2] *= -1.0f;
	JointTransforms27.m[1][2] *= -1.0f;
	JointTransforms27.m[2][0] *= -1.0f;
	JointTransforms27.m[2][1] *= -1.0f;
	JointTransforms27.m[3][2] *= -1.0f;

	JointTransforms28 = ModelSkeleton->Joints[27]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose28 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms28));
	XMStoreFloat4x4(&JointTransforms28, TempTranspose28);
	JointTransforms28.m[0][2] *= -1.0f;
	JointTransforms28.m[1][2] *= -1.0f;
	JointTransforms28.m[2][0] *= -1.0f;
	JointTransforms28.m[2][1] *= -1.0f;
	JointTransforms28.m[3][2] *= -1.0f;

	JointTransforms29 = ModelSkeleton->Joints[28]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose29= XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms29));
	XMStoreFloat4x4(&JointTransforms29, TempTranspose29);
	JointTransforms29.m[0][2] *= -1.0f;
	JointTransforms29.m[1][2] *= -1.0f;
	JointTransforms29.m[2][0] *= -1.0f;
	JointTransforms29.m[2][1] *= -1.0f;
	JointTransforms29.m[3][2] *= -1.0f;

	JointTransforms30 = ModelSkeleton->Joints[29]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose30 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms30));
	XMStoreFloat4x4(&JointTransforms30, TempTranspose30);
	JointTransforms30.m[0][2] *= -1.0f;
	JointTransforms30.m[1][2] *= -1.0f;
	JointTransforms30.m[2][0] *= -1.0f;
	JointTransforms30.m[2][1] *= -1.0f;
	JointTransforms30.m[3][2] *= -1.0f;

	JointTransforms31 = ModelSkeleton->Joints[30]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose31= XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms31));
	XMStoreFloat4x4(&JointTransforms31, TempTranspose31);
	JointTransforms31.m[0][2] *= -1.0f;
	JointTransforms31.m[1][2] *= -1.0f;
	JointTransforms31.m[2][0] *= -1.0f;
	JointTransforms31.m[2][1] *= -1.0f;
	JointTransforms31.m[3][2] *= -1.0f;

	JointTransforms32 = ModelSkeleton->Joints[31]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose32 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms32));
	XMStoreFloat4x4(&JointTransforms32, TempTranspose32);
	JointTransforms32.m[0][2] *= -1.0f;
	JointTransforms32.m[1][2] *= -1.0f;
	JointTransforms32.m[2][0] *= -1.0f;
	JointTransforms32.m[2][1] *= -1.0f;
	JointTransforms32.m[3][2] *= -1.0f;


	JointTransforms33 = ModelSkeleton->Joints[32]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose33 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms33));
	XMStoreFloat4x4(&JointTransforms33, TempTranspose33);
	JointTransforms33.m[0][2] *= -1.0f;
	JointTransforms33.m[1][2] *= -1.0f;
	JointTransforms33.m[2][0] *= -1.0f;
	JointTransforms33.m[2][1] *= -1.0f;
	JointTransforms33.m[3][2] *= -1.0f;

	JointTransforms34 = ModelSkeleton->Joints[33]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose34 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms34));
	XMStoreFloat4x4(&JointTransforms34, TempTranspose34);
	JointTransforms34.m[0][2] *= -1.0f;
	JointTransforms34.m[1][2] *= -1.0f;
	JointTransforms34.m[2][0] *= -1.0f;
	JointTransforms34.m[2][1] *= -1.0f;
	JointTransforms34.m[3][2] *= -1.0f;

	JointTransforms35 = ModelSkeleton->Joints[34]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose35 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms35));
	XMStoreFloat4x4(&JointTransforms35, TempTranspose35);
	JointTransforms35.m[0][2] *= -1.0f;
	JointTransforms35.m[1][2] *= -1.0f;
	JointTransforms35.m[2][0] *= -1.0f;
	JointTransforms35.m[2][1] *= -1.0f;
	JointTransforms35.m[3][2] *= -1.0f;

	JointTransforms36 = ModelSkeleton->Joints[35]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose36 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms36));
	XMStoreFloat4x4(&JointTransforms36, TempTranspose36);
	JointTransforms36.m[0][2] *= -1.0f;
	JointTransforms36.m[1][2] *= -1.0f;
	JointTransforms36.m[2][0] *= -1.0f;
	JointTransforms36.m[2][1] *= -1.0f;
	JointTransforms36.m[3][2] *= -1.0f;

	JointTransforms37 = ModelSkeleton->Joints[36]->Keyframes[0]->TransformationMatrix;
	XMMATRIX TempTranspose37 = XMMatrixTranspose(XMLoadFloat4x4(&JointTransforms37));
	XMStoreFloat4x4(&JointTransforms37, TempTranspose37);
	JointTransforms37.m[0][2] *= -1.0f;
	JointTransforms37.m[1][2] *= -1.0f;
	JointTransforms37.m[2][0] *= -1.0f;
	JointTransforms37.m[2][1] *= -1.0f;
	JointTransforms37.m[3][2] *= -1.0f;
#pragma endregion 
#pragma region Joint Const Buffer setup region
	D3D11_BUFFER_DESC JointMatrixBufferDesc;
	ZeroMemory(&JointMatrixBufferDesc, sizeof(JointMatrixBufferDesc));
	JointMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc.ByteWidth = sizeof(XMFLOAT4X4);// *ModelSkeleton->numJoints;
	JointMatrixBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData;
	JointMatrixSubresourceData.pSysMem = &JointTransforms;
	JointMatrixSubresourceData.SysMemPitch = 0;
	JointMatrixSubresourceData.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc, &JointMatrixSubresourceData, &JointConstBuffers);

	D3D11_BUFFER_DESC JointMatrixBufferDesc2;
	ZeroMemory(&JointMatrixBufferDesc2, sizeof(JointMatrixBufferDesc2));
	JointMatrixBufferDesc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc2.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc2.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc2.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData2;
	JointMatrixSubresourceData2.pSysMem = &JointTransforms2;
	JointMatrixSubresourceData2.SysMemPitch = 0;
	JointMatrixSubresourceData2.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc2, &JointMatrixSubresourceData2, &JointConstBuffers2);

	D3D11_BUFFER_DESC JointMatrixBufferDesc3;
	ZeroMemory(&JointMatrixBufferDesc3, sizeof(JointMatrixBufferDesc3));
	JointMatrixBufferDesc3.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc3.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc3.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc3.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData3;
	JointMatrixSubresourceData3.pSysMem = &JointTransforms3;
	JointMatrixSubresourceData3.SysMemPitch = 0;
	JointMatrixSubresourceData3.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc3, &JointMatrixSubresourceData3, &JointConstBuffers3);


	D3D11_BUFFER_DESC JointMatrixBufferDesc4;
	ZeroMemory(&JointMatrixBufferDesc4, sizeof(JointMatrixBufferDesc4));
	JointMatrixBufferDesc4.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc4.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc4.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc4.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData4;
	JointMatrixSubresourceData4.pSysMem = &JointTransforms4;
	JointMatrixSubresourceData4.SysMemPitch = 0;
	JointMatrixSubresourceData4.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc4, &JointMatrixSubresourceData4, &JointConstBuffers4);

	D3D11_BUFFER_DESC JointMatrixBufferDesc5;
	ZeroMemory(&JointMatrixBufferDesc5, sizeof(JointMatrixBufferDesc5));
	JointMatrixBufferDesc5.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc5.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc5.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc5.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData5;
	JointMatrixSubresourceData5.pSysMem = &JointTransforms5;
	JointMatrixSubresourceData5.SysMemPitch = 0;
	JointMatrixSubresourceData5.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc5, &JointMatrixSubresourceData5, &JointConstBuffers5);

	D3D11_BUFFER_DESC JointMatrixBufferDesc6;
	ZeroMemory(&JointMatrixBufferDesc6 , sizeof(JointMatrixBufferDesc6));
	JointMatrixBufferDesc6.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc6.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc6.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc6.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData6;
	JointMatrixSubresourceData6.pSysMem = &JointTransforms6;
	JointMatrixSubresourceData6.SysMemPitch = 0;
	JointMatrixSubresourceData6.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc6, &JointMatrixSubresourceData6, &JointConstBuffers6);

	D3D11_BUFFER_DESC JointMatrixBufferDesc7;
	ZeroMemory(&JointMatrixBufferDesc7, sizeof(JointMatrixBufferDesc7));
	JointMatrixBufferDesc7.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc7.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc7.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc7.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData7;
	JointMatrixSubresourceData7.pSysMem = &JointTransforms7;
	JointMatrixSubresourceData7.SysMemPitch = 0;
	JointMatrixSubresourceData7.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc7, &JointMatrixSubresourceData7, &JointConstBuffers7);


	D3D11_BUFFER_DESC JointMatrixBufferDesc8;
	ZeroMemory(&JointMatrixBufferDesc8, sizeof(JointMatrixBufferDesc8));
	JointMatrixBufferDesc8.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc8.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc8.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc8.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData8;
	JointMatrixSubresourceData8.pSysMem = &JointTransforms8;
	JointMatrixSubresourceData8.SysMemPitch = 0;
	JointMatrixSubresourceData8.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc8, &JointMatrixSubresourceData8, &JointConstBuffers8);


	D3D11_BUFFER_DESC JointMatrixBufferDesc9;
	ZeroMemory(&JointMatrixBufferDesc9, sizeof(JointMatrixBufferDesc9));
	JointMatrixBufferDesc9.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc9.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc9.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc9.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData9;
	JointMatrixSubresourceData9.pSysMem = &JointTransforms9;
	JointMatrixSubresourceData9.SysMemPitch = 0;
	JointMatrixSubresourceData9.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc9, &JointMatrixSubresourceData9, &JointConstBuffers9);

	D3D11_BUFFER_DESC JointMatrixBufferDesc10;
	ZeroMemory(&JointMatrixBufferDesc10, sizeof(JointMatrixBufferDesc10));
	JointMatrixBufferDesc10.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc10.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc10.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc10.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData10;
	JointMatrixSubresourceData10.pSysMem = &JointTransforms10;
	JointMatrixSubresourceData10.SysMemPitch = 0;
	JointMatrixSubresourceData10.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc10, &JointMatrixSubresourceData10, &JointConstBuffers10);


	D3D11_BUFFER_DESC JointMatrixBufferDesc11;
	ZeroMemory(&JointMatrixBufferDesc11, sizeof(JointMatrixBufferDesc11));
	JointMatrixBufferDesc11.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc11.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc11.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc11.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData11;
	JointMatrixSubresourceData11.pSysMem = &JointTransforms11;
	JointMatrixSubresourceData11.SysMemPitch = 0;
	JointMatrixSubresourceData11.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc11, &JointMatrixSubresourceData11, &JointConstBuffers11);

	D3D11_BUFFER_DESC JointMatrixBufferDesc12;
	ZeroMemory(&JointMatrixBufferDesc12, sizeof(JointMatrixBufferDesc12));
	JointMatrixBufferDesc12.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc12.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc12.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc12.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData12;
	JointMatrixSubresourceData12.pSysMem = &JointTransforms12;
	JointMatrixSubresourceData12.SysMemPitch = 0;
	JointMatrixSubresourceData12.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc12, &JointMatrixSubresourceData12, &JointConstBuffers12);

	D3D11_BUFFER_DESC JointMatrixBufferDesc13;
	ZeroMemory(&JointMatrixBufferDesc13, sizeof(JointMatrixBufferDesc13));
	JointMatrixBufferDesc13.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc13.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc13.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc13.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData13;
	JointMatrixSubresourceData13.pSysMem = &JointTransforms13;
	JointMatrixSubresourceData13.SysMemPitch = 0;
	JointMatrixSubresourceData13.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc13, &JointMatrixSubresourceData13, &JointConstBuffers13);

	D3D11_BUFFER_DESC JointMatrixBufferDesc14;
	ZeroMemory(&JointMatrixBufferDesc14, sizeof(JointMatrixBufferDesc14));
	JointMatrixBufferDesc14.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc14.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc14.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc14.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData14;
	JointMatrixSubresourceData14.pSysMem = &JointTransforms14;
	JointMatrixSubresourceData14.SysMemPitch = 0;
	JointMatrixSubresourceData14.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc14, &JointMatrixSubresourceData14, &JointConstBuffers14);

	D3D11_BUFFER_DESC JointMatrixBufferDesc15;
	ZeroMemory(&JointMatrixBufferDesc15, sizeof(JointMatrixBufferDesc15));
	JointMatrixBufferDesc15.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc15.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc15.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc15.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData15;
	JointMatrixSubresourceData15.pSysMem = &JointTransforms15;
	JointMatrixSubresourceData15.SysMemPitch = 0;
	JointMatrixSubresourceData15.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc15, &JointMatrixSubresourceData15, &JointConstBuffers15);

	D3D11_BUFFER_DESC JointMatrixBufferDesc16;
	ZeroMemory(&JointMatrixBufferDesc16, sizeof(JointMatrixBufferDesc16));
	JointMatrixBufferDesc16.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc16.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc16.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc16.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData16;
	JointMatrixSubresourceData16.pSysMem = &JointTransforms16;
	JointMatrixSubresourceData16.SysMemPitch = 0;
	JointMatrixSubresourceData16.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc16, &JointMatrixSubresourceData16, &JointConstBuffers16);

	D3D11_BUFFER_DESC JointMatrixBufferDesc17;
	ZeroMemory(&JointMatrixBufferDesc17, sizeof(JointMatrixBufferDesc17));
	JointMatrixBufferDesc17.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc17.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc17.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc17.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData17;
	JointMatrixSubresourceData17.pSysMem = &JointTransforms17;
	JointMatrixSubresourceData17.SysMemPitch = 0;
	JointMatrixSubresourceData17.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc17, &JointMatrixSubresourceData17, &JointConstBuffers17);

	D3D11_BUFFER_DESC JointMatrixBufferDesc18;
	ZeroMemory(&JointMatrixBufferDesc18, sizeof(JointMatrixBufferDesc18));
	JointMatrixBufferDesc18.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc18.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc18.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc18.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData18;
	JointMatrixSubresourceData18.pSysMem = &JointTransforms18;
	JointMatrixSubresourceData18.SysMemPitch = 0;
	JointMatrixSubresourceData18.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc18, &JointMatrixSubresourceData18, &JointConstBuffers18);

	D3D11_BUFFER_DESC JointMatrixBufferDesc19;
	ZeroMemory(&JointMatrixBufferDesc19, sizeof(JointMatrixBufferDesc19));
	JointMatrixBufferDesc19.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc19.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc19.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc19.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData19;
	JointMatrixSubresourceData19.pSysMem = &JointTransforms19;
	JointMatrixSubresourceData19.SysMemPitch = 0;
	JointMatrixSubresourceData19.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc19, &JointMatrixSubresourceData19, &JointConstBuffers19);


	D3D11_BUFFER_DESC JointMatrixBufferDesc20;
	ZeroMemory(&JointMatrixBufferDesc20, sizeof(JointMatrixBufferDesc20));
	JointMatrixBufferDesc20.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc20.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc20.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc20.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData20;
	JointMatrixSubresourceData20.pSysMem = &JointTransforms20;
	JointMatrixSubresourceData20.SysMemPitch = 0;
	JointMatrixSubresourceData20.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc20, &JointMatrixSubresourceData20, &JointConstBuffers20);

	D3D11_BUFFER_DESC JointMatrixBufferDesc21;
	ZeroMemory(&JointMatrixBufferDesc21, sizeof(JointMatrixBufferDesc21));
	JointMatrixBufferDesc21.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc21.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc21.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc21.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData21;
	JointMatrixSubresourceData21.pSysMem = &JointTransforms21;
	JointMatrixSubresourceData21.SysMemPitch = 0;
	JointMatrixSubresourceData21.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc21, &JointMatrixSubresourceData21, &JointConstBuffers21);

	D3D11_BUFFER_DESC JointMatrixBufferDesc22;
	ZeroMemory(&JointMatrixBufferDesc22, sizeof(JointMatrixBufferDesc22));
	JointMatrixBufferDesc22.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc22.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc22.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc22.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData22;
	JointMatrixSubresourceData22.pSysMem = &JointTransforms22;
	JointMatrixSubresourceData22.SysMemPitch = 0;
	JointMatrixSubresourceData22.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc22, &JointMatrixSubresourceData22, &JointConstBuffers22);

	D3D11_BUFFER_DESC JointMatrixBufferDesc23;
	ZeroMemory(&JointMatrixBufferDesc23, sizeof(JointMatrixBufferDesc23));
	JointMatrixBufferDesc23.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc23.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc23.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc23.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData23;
	JointMatrixSubresourceData23.pSysMem = &JointTransforms23;
	JointMatrixSubresourceData23.SysMemPitch = 0;
	JointMatrixSubresourceData23.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc23, &JointMatrixSubresourceData23, &JointConstBuffers23);

	D3D11_BUFFER_DESC JointMatrixBufferDesc24;
	ZeroMemory(&JointMatrixBufferDesc24, sizeof(JointMatrixBufferDesc24));
	JointMatrixBufferDesc24.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc24.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc24.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc24.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData24;
	JointMatrixSubresourceData24.pSysMem = &JointTransforms24;
	JointMatrixSubresourceData24.SysMemPitch = 0;
	JointMatrixSubresourceData24.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc24, &JointMatrixSubresourceData24, &JointConstBuffers24);

	D3D11_BUFFER_DESC JointMatrixBufferDesc25;
	ZeroMemory(&JointMatrixBufferDesc25, sizeof(JointMatrixBufferDesc25));
	JointMatrixBufferDesc25.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc25.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc25.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc25.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData25;
	JointMatrixSubresourceData25.pSysMem = &JointTransforms25;
	JointMatrixSubresourceData25.SysMemPitch = 0;
	JointMatrixSubresourceData25.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc25, &JointMatrixSubresourceData25, &JointConstBuffers25);

	D3D11_BUFFER_DESC JointMatrixBufferDesc26;
	ZeroMemory(&JointMatrixBufferDesc26, sizeof(JointMatrixBufferDesc26));
	JointMatrixBufferDesc26.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc26.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc26.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc26.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData26;
	JointMatrixSubresourceData26.pSysMem = &JointTransforms26;
	JointMatrixSubresourceData26.SysMemPitch = 0;
	JointMatrixSubresourceData26.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc26, &JointMatrixSubresourceData26, &JointConstBuffers26);


	D3D11_BUFFER_DESC JointMatrixBufferDesc27;
	ZeroMemory(&JointMatrixBufferDesc27, sizeof(JointMatrixBufferDesc27));
	JointMatrixBufferDesc27.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc27.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc27.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc27.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData27;
	JointMatrixSubresourceData27.pSysMem = &JointTransforms27;
	JointMatrixSubresourceData27.SysMemPitch = 0;
	JointMatrixSubresourceData27.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc27, &JointMatrixSubresourceData27, &JointConstBuffers27);


	D3D11_BUFFER_DESC JointMatrixBufferDesc28;
	ZeroMemory(&JointMatrixBufferDesc28, sizeof(JointMatrixBufferDesc28));
	JointMatrixBufferDesc28.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc28.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc28.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc28.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData28;
	JointMatrixSubresourceData28.pSysMem = &JointTransforms28;
	JointMatrixSubresourceData28.SysMemPitch = 0;
	JointMatrixSubresourceData28.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc28, &JointMatrixSubresourceData28, &JointConstBuffers28);

	D3D11_BUFFER_DESC JointMatrixBufferDesc29;
	ZeroMemory(&JointMatrixBufferDesc29, sizeof(JointMatrixBufferDesc29));
	JointMatrixBufferDesc29.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc29.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc29.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc29.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData29;
	JointMatrixSubresourceData29.pSysMem = &JointTransforms29 ;
	JointMatrixSubresourceData29.SysMemPitch = 0;
	JointMatrixSubresourceData29.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc29, &JointMatrixSubresourceData29, &JointConstBuffers29);


	D3D11_BUFFER_DESC JointMatrixBufferDesc30;
	ZeroMemory(&JointMatrixBufferDesc30, sizeof(JointMatrixBufferDesc30));
	JointMatrixBufferDesc30.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc30.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc30.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc30.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData30;
	JointMatrixSubresourceData30.pSysMem = &JointTransforms30;
	JointMatrixSubresourceData30.SysMemPitch = 0;
	JointMatrixSubresourceData30.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc30, &JointMatrixSubresourceData30, &JointConstBuffers30);


	D3D11_BUFFER_DESC JointMatrixBufferDesc31;
	ZeroMemory(&JointMatrixBufferDesc31, sizeof(JointMatrixBufferDesc31));
	JointMatrixBufferDesc31.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc31.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc31.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc31.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData31;
	JointMatrixSubresourceData31.pSysMem = &JointTransforms31;
	JointMatrixSubresourceData31.SysMemPitch = 0;
	JointMatrixSubresourceData31.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc31, &JointMatrixSubresourceData31, &JointConstBuffers31);

	D3D11_BUFFER_DESC JointMatrixBufferDesc32;
	ZeroMemory(&JointMatrixBufferDesc32, sizeof(JointMatrixBufferDesc32));
	JointMatrixBufferDesc32.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc32.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc32.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc32.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData32;
	JointMatrixSubresourceData32.pSysMem = &JointTransforms32;
	JointMatrixSubresourceData32.SysMemPitch = 0;
	JointMatrixSubresourceData32.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc32, &JointMatrixSubresourceData32, &JointConstBuffers32);

	D3D11_BUFFER_DESC JointMatrixBufferDesc33;
	ZeroMemory(&JointMatrixBufferDesc33, sizeof(JointMatrixBufferDesc33));
	JointMatrixBufferDesc33.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc33.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc33.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc33.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData33;
	JointMatrixSubresourceData33.pSysMem = &JointTransforms33;
	JointMatrixSubresourceData33.SysMemPitch = 0;
	JointMatrixSubresourceData33.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc33, &JointMatrixSubresourceData33, &JointConstBuffers33);

	D3D11_BUFFER_DESC JointMatrixBufferDesc34;
	ZeroMemory(&JointMatrixBufferDesc34, sizeof(JointMatrixBufferDesc34));
	JointMatrixBufferDesc34.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc34.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc34.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc34.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData34;
	JointMatrixSubresourceData34.pSysMem = &JointTransforms34;
	JointMatrixSubresourceData34.SysMemPitch = 0;
	JointMatrixSubresourceData34.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc34, &JointMatrixSubresourceData34, &JointConstBuffers34);

	D3D11_BUFFER_DESC JointMatrixBufferDesc35;
	ZeroMemory(&JointMatrixBufferDesc35, sizeof(JointMatrixBufferDesc35));
	JointMatrixBufferDesc35.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc35.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc35.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc35.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData35;
	JointMatrixSubresourceData35.pSysMem = &JointTransforms35;
	JointMatrixSubresourceData35.SysMemPitch = 0;
	JointMatrixSubresourceData35.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc35, &JointMatrixSubresourceData35, &JointConstBuffers35);

	D3D11_BUFFER_DESC JointMatrixBufferDesc36;
	ZeroMemory(&JointMatrixBufferDesc36, sizeof(JointMatrixBufferDesc36));
	JointMatrixBufferDesc36.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc36.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc36.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc36.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData36;
	JointMatrixSubresourceData36.pSysMem = &JointTransforms36;
	JointMatrixSubresourceData36.SysMemPitch = 0;
	JointMatrixSubresourceData36.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc36, &JointMatrixSubresourceData36, &JointConstBuffers36);

	D3D11_BUFFER_DESC JointMatrixBufferDesc37;
	ZeroMemory(&JointMatrixBufferDesc37, sizeof(JointMatrixBufferDesc37));
	JointMatrixBufferDesc37.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	JointMatrixBufferDesc37.ByteWidth = sizeof(XMFLOAT4X4);
	JointMatrixBufferDesc37.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	JointMatrixBufferDesc37.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA JointMatrixSubresourceData37;
	JointMatrixSubresourceData37.pSysMem = &JointTransforms37;
	JointMatrixSubresourceData37.SysMemPitch = 0;
	JointMatrixSubresourceData37.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&JointMatrixBufferDesc37, &JointMatrixSubresourceData37, &JointConstBuffers37);
#pragma endregion 
	Result = Device->CreateVertexShader(SkeletonJointVertexShader, sizeof(SkeletonJointVertexShader), NULL, &SkeletalJointVertexShaderPtr);
	Result = Device->CreatePixelShader(SkeletonJointPixelShader, sizeof(SkeletonJointPixelShader), NULL, &SkeletalJointPixelShaderPtr);

	JointVertexBuffer = RenderJoints();

	NumIndices = NewMesh->Indices.size();
	int* IndexArray = new int[NumIndices];

	for (unsigned int i = 0; i < NumIndices; i++)
		IndexArray[i] = NewMesh->Indices[i]; 


	D3D11_SAMPLER_DESC TextureSamplerDesc; 
	TextureSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	TextureSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	TextureSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	TextureSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;//D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	TextureSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	TextureSamplerDesc.MaxAnisotropy = 1;
	TextureSamplerDesc.MaxLOD = FLT_MAX;
	TextureSamplerDesc.MinLOD = -FLT_MAX;
	TextureSamplerDesc.MipLODBias = 0.0f;

	Result = Device->CreateSamplerState(&TextureSamplerDesc, &TextureSamplerState); 
	Result = CreateDDSTextureFromFile(Device, L"Teddy_D.dds", &TextureResource, &TextureResourceView, 0);
	Device->CreateShaderResourceView(TextureResource, NULL, &TextureResourceView);

#pragma region Skybox Setup
	D3D11_TEXTURE2D_DESC SkyboxDepthStencilDesc;
	ZeroMemory(&SkyboxDepthStencilDesc, sizeof(SkyboxDepthStencilDesc));

	SkyboxDepthStencilDesc.ArraySize =0; //Needs to be 0, but gives errors
	SkyboxDepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	SkyboxDepthStencilDesc.CPUAccessFlags = 0;
	SkyboxDepthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
	SkyboxDepthStencilDesc.Height = BUFFER_HEIGHT;
	SkyboxDepthStencilDesc.Width = BUFFER_WIDTH;
	SkyboxDepthStencilDesc.MipLevels = 0;
	SkyboxDepthStencilDesc.MiscFlags = 0;
	SkyboxDepthStencilDesc.SampleDesc.Count = 1;
	SkyboxDepthStencilDesc.SampleDesc.Quality = 0;
	SkyboxDepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

	Result = Device->CreateTexture2D(&SkyboxDepthStencilDesc, NULL, &SkyboxDepthBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC SkyboxDepthStencilViewDesc;
	ZeroMemory(&SkyboxDepthStencilViewDesc, sizeof(SkyboxDepthStencilViewDesc));
	SkyboxDepthStencilViewDesc.Flags = 0;
	SkyboxDepthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	SkyboxDepthStencilViewDesc.Texture2D.MipSlice = 0;
	SkyboxDepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	Result = Device->CreateDepthStencilView(SkyboxDepthBuffer, &SkyboxDepthStencilViewDesc, &SkyboxDepthStencilView);

	D3D11_SAMPLER_DESC SkyboxTextureSamplerDesc;
	ZeroMemory(&SkyboxTextureSamplerDesc, sizeof(SkyboxTextureSamplerDesc));
	SkyboxTextureSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SkyboxTextureSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SkyboxTextureSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	SkyboxTextureSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;//D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	SkyboxTextureSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;//was D3D11_COMPARISON_ALWAYS
	SkyboxTextureSamplerDesc.MaxAnisotropy = 1;
	SkyboxTextureSamplerDesc.MaxLOD = FLT_MAX;
	SkyboxTextureSamplerDesc.MinLOD = -FLT_MAX;
	SkyboxTextureSamplerDesc.MipLODBias = 0.0f;
	SkyboxTextureSamplerDesc.BorderColor[0] = 0;
	SkyboxTextureSamplerDesc.BorderColor[1] = 0;
	SkyboxTextureSamplerDesc.BorderColor[2] = 0;
	SkyboxTextureSamplerDesc.BorderColor[3] = 0;
	Result = Device->CreateSamplerState(&SkyboxTextureSamplerDesc, &SkyboxTextureSamplerState);
	Result = CreateDDSTextureFromFile(Device, L"Skybox.dds", &SkyboxTextureResource, &SkyboxTextureResourceView, 0);
	Result = Device->CreateShaderResourceView(SkyboxTextureResource, NULL, &SkyboxTextureResourceView);

	VertexInfo SkyboxCube[8];
	VertexInfo Temp;
	Temp.Position.x = 1.0f;
	Temp.Position.y = 1.0f;
	Temp.Position.z = 1.0f;

	Temp.Color.x = 1.0f;
	Temp.Color.y = 1.0f;
	Temp.Color.z = 1.0f;
	Temp.Color.w = 1.0f;

	Temp.Normals.x = 1.0f;
	Temp.Normals.y = 1.0f;
	Temp.Normals.z = 1.0f;

	Temp.UVs.x = 1.0f;
	Temp.UVs.y = 1.0f;
	for (unsigned int i = 0; i < 8; i++)
	{
		SkyboxCube[i].Color = Temp.Color;
		SkyboxCube[i].Position = Temp.Position;
		SkyboxCube[i].Normals = Temp.Normals;
		SkyboxCube[i].UVs = Temp.UVs;
	}
	//Front Upper Left Corner
	SkyboxCube[0].Position.x -=500.0f;
	SkyboxCube[0].Position.y +=500.0f;
	SkyboxCube[0].Position.z +=500.0f;
	//Front Upper Right Corner
	SkyboxCube[1].Position.x +=500.0f;
	SkyboxCube[1].Position.y +=500.0f;
	SkyboxCube[1].Position.z +=500.0f;
	//Front Lower Left Corner
	SkyboxCube[2].Position.x -= 500.0f;
	SkyboxCube[2].Position.y -= 500.0f;
	SkyboxCube[2].Position.z += 500.0f;
	//Front Lower Right Corner
	SkyboxCube[3].Position.x += 500.0f;
	SkyboxCube[3].Position.y -= 500.0f;
	SkyboxCube[3].Position.z += 500.0f;
	//Back Upper Left Corner
	SkyboxCube[4].Position.x += 500.0f;
	SkyboxCube[4].Position.y += 500.0f;
	SkyboxCube[4].Position.z -= 500.0f;
	//Back Upper Right Corner
	SkyboxCube[5].Position.x +=500.0f;
	SkyboxCube[5].Position.y -=500.0f;
	SkyboxCube[5].Position.z -=500.0f;
	//Back Lower Left Corner
	SkyboxCube[6].Position.x -= 500.0f;
	SkyboxCube[6].Position.y += 500.0f;
	SkyboxCube[6].Position.z -= 500.0f;
	//Back Lower Right Corner
	SkyboxCube[7].Position.x -= 500.0f;
	SkyboxCube[7].Position.y -= 500.0f;
	SkyboxCube[7].Position.z -= 500.0f;

	D3D11_BUFFER_DESC SkyboxBufferDesc;
	ZeroMemory(&SkyboxBufferDesc, sizeof(SkyboxBufferDesc));
	SkyboxBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	SkyboxBufferDesc.ByteWidth = sizeof(VertexInfo) * 8;
	SkyboxBufferDesc.CPUAccessFlags = NULL;
	SkyboxBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	D3D11_SUBRESOURCE_DATA SkyboxSubresourceData;
	SkyboxSubresourceData.SysMemPitch = 0;
	SkyboxSubresourceData.pSysMem = SkyboxCube;
	SkyboxSubresourceData.SysMemSlicePitch = 0;

	Result = Device->CreateBuffer(&SkyboxBufferDesc, &SkyboxSubresourceData, &SkyboxVertexBuffer);
	Result = Device->CreateVertexShader(SkyboxVertexShader, sizeof(SkyboxVertexShader), NULL, &SkyboxVertexShaderPtr);
	Result = Device->CreatePixelShader(SkyboxPixelShader, sizeof(SkyboxPixelShader), NULL, &SkyboxPixelShaderPtr); 
#pragma endregion 
#pragma region GroundPlane Setup
	VertexInfo GroundPlane[4]; 
	for (int i = 0; i < 4; i++)
	{
		GroundPlane[i].Position.y = -1.0f; 

		GroundPlane[i].Normals.x = 0.0f;
		GroundPlane[i].Normals.y = 1.0f;
		GroundPlane[i].Normals.z = 0.0f;

		GroundPlane[i].Color.x = 1.0f;
		GroundPlane[i].Color.y = 0.0f;
		GroundPlane[i].Color.z = 0.0f;
		GroundPlane[i].Color.w = 1.0f;
	}

	GroundPlane[0].Position.x = -100.0f;
	GroundPlane[0].Position.z = -100.0f;
	GroundPlane[0].UVs.x = 0.0f;
	GroundPlane[0].UVs.y = 0.0f;

	GroundPlane[1].Position.x = 100.0f;
	GroundPlane[1].Position.z = -100.0f;
	GroundPlane[1].UVs.x = 1.0f;
	GroundPlane[1].UVs.y = 0.0f;

	GroundPlane[2].Position.x =100.0f;
	GroundPlane[2].Position.z =100.0f;
	GroundPlane[2].UVs.x = 1.0f;
	GroundPlane[2].UVs.y = 1.0f;

	GroundPlane[3].Position.x = -100.0f;
	GroundPlane[3].Position.z = 100.0f;
	GroundPlane[3].UVs.x = 0.0f;
	GroundPlane[3].UVs.y = 1.0f;

	int GroundIndex[] = { 0, 1, 2,
						  0, 2, 3 };

	D3D11_BUFFER_DESC GroundBufferDesc;
	ZeroMemory(&GroundBufferDesc, sizeof(GroundBufferDesc));
	GroundBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	GroundBufferDesc.ByteWidth = sizeof(VertexInfo) * 4;
	GroundBufferDesc.CPUAccessFlags = NULL;
	GroundBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA GroundSubresourceData;
	GroundSubresourceData.SysMemPitch = 0;
	GroundSubresourceData.pSysMem = GroundPlane;
	GroundSubresourceData.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&GroundBufferDesc, &GroundSubresourceData, &GroundVertexBuffer);

	D3D11_BUFFER_DESC GroundIndexBuffDesc;
	ZeroMemory(&GroundIndexBuffDesc, sizeof(GroundIndexBuffDesc));
	GroundIndexBuffDesc.ByteWidth = sizeof(int) * 6;
	GroundIndexBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GroundIndexBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	GroundIndexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	GroundIndexBuffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA GroundIndexSubresourceData;
	GroundIndexSubresourceData.pSysMem = GroundIndex;
	GroundIndexSubresourceData.SysMemPitch = 0;
	GroundIndexSubresourceData.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&GroundIndexBuffDesc, &GroundIndexSubresourceData, &GroundIndexBuffer);

	D3D11_SAMPLER_DESC GroundTextureSamplerDesc;
	GroundTextureSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	GroundTextureSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	GroundTextureSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	GroundTextureSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;//D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	GroundTextureSamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	GroundTextureSamplerDesc.MaxAnisotropy = 1;
	GroundTextureSamplerDesc.MaxLOD = FLT_MAX;
	GroundTextureSamplerDesc.MinLOD = -FLT_MAX;
	GroundTextureSamplerDesc.MipLODBias = 0.0f;

	Result = Device->CreateSamplerState(&GroundTextureSamplerDesc, &GroundTextureSamplerState);
	Result = CreateDDSTextureFromFile(Device, L"FullSailLogo.dds", &GroundTextureResource, &GroundTextureResourceView, 0);
	Device->CreateShaderResourceView(GroundTextureResource, NULL, &GroundTextureResourceView);
#pragma endregion

	D3D11_BUFFER_DESC BufferDesc; 
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; 
	BufferDesc.ByteWidth = sizeof(VertexInfo) * NewMesh->numVerts;
	BufferDesc.CPUAccessFlags = NULL; 
	BufferDesc.Usage = D3D11_USAGE_IMMUTABLE; 

	D3D11_SUBRESOURCE_DATA SubresourceData; 
	SubresourceData.SysMemPitch = 0; 
	SubresourceData.pSysMem = ModelVerts;
	SubresourceData.SysMemSlicePitch = 0; 
	Result = Device->CreateBuffer(&BufferDesc, &SubresourceData, &MeshVertexBuffer);


	D3D11_BUFFER_DESC IndexBuffDesc; 
	ZeroMemory(&IndexBuffDesc, sizeof(IndexBuffDesc));

	IndexBuffDesc.ByteWidth = sizeof(int) * NumIndices;
	IndexBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
	IndexBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	IndexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; 
	IndexBuffDesc.MiscFlags = 0; 

	D3D11_SUBRESOURCE_DATA IndexSubresourceData; 

	IndexSubresourceData.pSysMem = IndexArray;
	IndexSubresourceData.SysMemPitch = 0;
	IndexSubresourceData.SysMemSlicePitch = 0;

	Result = Device->CreateBuffer(&IndexBuffDesc, &IndexSubresourceData, &MeshIndexBuffer);

	XMStoreFloat4x4(&WorldMatrix, XMMatrixIdentity());

	XMMATRIX tempWorld = XMLoadFloat4x4(&WorldMatrix); 
	XMStoreFloat4x4(&WorldMatrix, tempWorld); 

#pragma region View And Proj Matrix setup
	float XScale, YScale, FarPlane, NearPlane, FrameOfView, AspectRatio; 
	AspectRatio = (float)BUFFER_HEIGHT / (float)BUFFER_WIDTH; 
	FrameOfView = 65.5f; 
	YScale = 1 / tanf(0.5f*(FrameOfView*(3.14f / 180.0f))); 
	XScale = YScale * AspectRatio; 
	NearPlane = 0.001f; 
	FarPlane = 1000.0f; 

	ViewAndProjMatr.ProjectionMatrix._11 = XScale;
	ViewAndProjMatr.ProjectionMatrix._12 = 0.0f;
	ViewAndProjMatr.ProjectionMatrix._13 = 0.0f;
	ViewAndProjMatr.ProjectionMatrix._14 = 0.0f;

	ViewAndProjMatr.ProjectionMatrix._21 = 0.0f;
	ViewAndProjMatr.ProjectionMatrix._22 = YScale;
	ViewAndProjMatr.ProjectionMatrix._23 = 0.0f;
	ViewAndProjMatr.ProjectionMatrix._24 = 0.0f;

	ViewAndProjMatr.ProjectionMatrix._31 = 0.0f;
	ViewAndProjMatr.ProjectionMatrix._32 = 0.0f;
	ViewAndProjMatr.ProjectionMatrix._33 = FarPlane / (FarPlane - NearPlane);
	ViewAndProjMatr.ProjectionMatrix._34 = 1.0f;

	ViewAndProjMatr.ProjectionMatrix._41 = 0.0f;
	ViewAndProjMatr.ProjectionMatrix._42 = 0.0f;
	ViewAndProjMatr.ProjectionMatrix._43 = -(FarPlane *NearPlane) / (FarPlane - NearPlane);
	ViewAndProjMatr.ProjectionMatrix._44 = 0.0f;

	XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, XMMatrixIdentity());
	XMMATRIX tempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
	XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, tempView);

	//XMMATRIX Translation = XMMatrixTranslation(30.0f, -30.0f, -30.0f);
	//XMMATRIX TempView = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
	//XMMATRIX Sum = XMMatrixMultiply(TempView, Translation);


	XMMATRIX TempViewRotY = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
	XMMATRIX Rotation = XMMatrixMultiply(TempViewRotY, XMMatrixRotationY(135.0f));
	XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, Rotation);

	XMMATRIX TempViewRotX = XMLoadFloat4x4(&ViewAndProjMatr.ViewMatrix);
	XMMATRIX RotationX = XMMatrixMultiply(TempViewRotX, XMMatrixRotationX(-45.0f));
	XMStoreFloat4x4(&ViewAndProjMatr.ViewMatrix, RotationX);

#pragma endregion
#pragma region Matrix Buffer Creation
	D3D11_BUFFER_DESC WorldMatrixBufferDesc;
	ZeroMemory(&WorldMatrixBufferDesc, sizeof(WorldMatrixBufferDesc));
	WorldMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	WorldMatrixBufferDesc.ByteWidth = sizeof(XMFLOAT4X4);
	WorldMatrixBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	WorldMatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA WorldMatrixSubresourceData;
	WorldMatrixSubresourceData.pSysMem = &WorldMatrix;
	WorldMatrixSubresourceData.SysMemPitch = 0;
	WorldMatrixSubresourceData.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&WorldMatrixBufferDesc, &WorldMatrixSubresourceData, &WorldMatrixBuffer);

	D3D11_BUFFER_DESC MatrixBufferDesc; 
	ZeroMemory(&MatrixBufferDesc, sizeof(MatrixBufferDesc));
	MatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	MatrixBufferDesc.ByteWidth = sizeof(ViewAndProjectionMatrices);
	MatrixBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	MatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA MatrixSubresourceData;
	MatrixSubresourceData.pSysMem = &ViewAndProjMatr;
	MatrixSubresourceData.SysMemPitch = 0;
	MatrixSubresourceData.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&MatrixBufferDesc, &MatrixSubresourceData, &MatrixBuffer); 

	D3D11_BUFFER_DESC SkyboxMatrixBufferDesc;
	ZeroMemory(&SkyboxMatrixBufferDesc, sizeof(SkyboxMatrixBufferDesc));
	SkyboxMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	SkyboxMatrixBufferDesc.ByteWidth = sizeof(XMFLOAT4X4);
	SkyboxMatrixBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	SkyboxMatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SkyboxMatrixSubresourceData;
	SkyboxMatrixSubresourceData.pSysMem = &SkyboxPositionMatrix;
	SkyboxMatrixSubresourceData.SysMemPitch = 0;
	SkyboxMatrixSubresourceData.SysMemSlicePitch = 0;
	Result = Device->CreateBuffer(&SkyboxMatrixBufferDesc, &SkyboxMatrixSubresourceData, &SkyboxMatrixBuffer);
#pragma endregion

	D3D11_RASTERIZER_DESC RastDesc; 
	ZeroMemory(&RastDesc, sizeof(RastDesc)); 
	RastDesc.AntialiasedLineEnable = true; 
	RastDesc.CullMode = D3D11_CULL_BACK;
	RastDesc.DepthBias = 1;
	RastDesc.DepthBiasClamp = 0;
	RastDesc.DepthClipEnable = true;
	RastDesc.FillMode = D3D11_FILL_SOLID;// D3D11_FILL_WIREFRAME;// D3D11_FILL_SOLID;
	RastDesc.FrontCounterClockwise = true;
	RastDesc.MultisampleEnable = true;
	RastDesc.ScissorEnable = false;
	RastDesc.SlopeScaledDepthBias = 0;

	Result = Device->CreateRasterizerState(&RastDesc, &RasterizerState); 

	D3D11_RASTERIZER_DESC FrontRastDesc;
	ZeroMemory(&FrontRastDesc, sizeof(FrontRastDesc));
	FrontRastDesc.AntialiasedLineEnable = true;
	FrontRastDesc.CullMode = D3D11_CULL_FRONT;
	FrontRastDesc.DepthBias = true;
	FrontRastDesc.DepthBiasClamp = 0;
	FrontRastDesc.DepthClipEnable = false;
	FrontRastDesc.FillMode = D3D11_FILL_SOLID;// D3D11_FILL_WIREFRAME; //D3D11_FILL_SOLID;
	FrontRastDesc.FrontCounterClockwise = true;
	FrontRastDesc.MultisampleEnable = true;
	FrontRastDesc.ScissorEnable = false;
	FrontRastDesc.SlopeScaledDepthBias = 0;
	
	Result = Device->CreateRasterizerState(&FrontRastDesc, &FrontCullRasterizerState);

	JointInterpolator->SetTotalTime(ModelSkeleton->TotalAnimationDuration);
}

void Renderer::PresentSwapChain()
{
	SwapChain->Present(0, 0);
}

void Renderer::Render()
{
	CameraMovement(); 

#pragma region Animation Section
	Timer.Signal(); 
	float currTime = (float)Timer.TotalTime();
	XMFLOAT4X4 JointTransformArray[37];
	ID3D11Buffer* JointBuffersArr[37];
	//if (currTime > ModelSkeleton->TotalAnimationDuration && currTime < (2.0f * ModelSkeleton->TotalAnimationDuration))//Reverse
	//{
	//	for (int i = 0; i < ModelSkeleton->numJoints; i++)
	//	{
	//		JointTransformArray[i] = JointInterpolator->ProcessBackwards(ModelSkeleton->Joints[i], (currTime), ModelSkeleton->TotalAnimationDuration);
	//
	//		XMMATRIX tempTransform = XMLoadFloat4x4(&JointTransformArray[i]);
	//		XMMATRIX tempBind = XMLoadFloat4x4(&ModelSkeleton->Joints[i]->BindMatrix);
	//		XMMATRIX ResultingMatrix = XMMatrixMultiply(tempBind, tempTransform); //Switch them around?
	//		XMStoreFloat4x4(&JointTransformArray[i], ResultingMatrix);
	//	}
	//}
	 if ( currTime >= (ModelSkeleton->TotalAnimationDuration * 1.0f) ) //Reset
	{
		Timer.Restart();
		Timer.Signal();
		currTime = (float)Timer.TotalTime();
	}
	else //Normal Animation
	{
		for (int i = 0; i < ModelSkeleton->numJoints; i++)
		{
			JointTransformArray[i] = JointInterpolator->Process(ModelSkeleton->Joints[i], currTime);

			XMMATRIX tempTransform = XMLoadFloat4x4(&JointTransformArray[i]);
			XMMATRIX tempBind = XMLoadFloat4x4(&ModelSkeleton->Joints[i]->BindMatrix);
			XMMATRIX ResultingMatrix = XMMatrixMultiply(tempBind, tempTransform); //Switch them around?

			XMStoreFloat4x4(&JointTransformArray[i], ResultingMatrix);

		}
	}

	ID3D11Buffer * AnimationMatrixBuffer;
	D3D11_BUFFER_DESC AnimationMatrixBufferDesc;
	ZeroMemory(&AnimationMatrixBufferDesc, sizeof(AnimationMatrixBufferDesc));
	AnimationMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	AnimationMatrixBufferDesc.ByteWidth = sizeof(XMFLOAT4X4)  *ModelSkeleton->numJoints;
	AnimationMatrixBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	AnimationMatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA AnimationMatrixSubresourceData;
	AnimationMatrixSubresourceData.pSysMem = JointTransformArray;
	AnimationMatrixSubresourceData.SysMemPitch = 0;
	AnimationMatrixSubresourceData.SysMemSlicePitch = 0;
	HRESULT Result = Device->CreateBuffer(&AnimationMatrixBufferDesc, &AnimationMatrixSubresourceData, &AnimationMatrixBuffer);


	JointBuffersArr[0] = JointConstBuffers;
	JointBuffersArr[1] = JointConstBuffers2;
	JointBuffersArr[2] = JointConstBuffers3;
	JointBuffersArr[3] = JointConstBuffers4;
	JointBuffersArr[4] = JointConstBuffers5;
	JointBuffersArr[5] = JointConstBuffers6;
	JointBuffersArr[6] = JointConstBuffers7;
	JointBuffersArr[7] = JointConstBuffers8;
	JointBuffersArr[8] = JointConstBuffers9;
	JointBuffersArr[9] = JointConstBuffers10;
	JointBuffersArr[10] = JointConstBuffers11;
	JointBuffersArr[11] = JointConstBuffers12;
	JointBuffersArr[12] = JointConstBuffers13;
	JointBuffersArr[13] = JointConstBuffers14;
	JointBuffersArr[14] = JointConstBuffers15;
	JointBuffersArr[15] = JointConstBuffers16;
	JointBuffersArr[16] = JointConstBuffers17;
	JointBuffersArr[17] = JointConstBuffers18;
	JointBuffersArr[18] = JointConstBuffers19;
	JointBuffersArr[19] = JointConstBuffers20;
	JointBuffersArr[20] = JointConstBuffers21;
	JointBuffersArr[21] = JointConstBuffers22;
	JointBuffersArr[22] = JointConstBuffers23;
	JointBuffersArr[23] = JointConstBuffers24;
	JointBuffersArr[24] = JointConstBuffers25;
	JointBuffersArr[25] = JointConstBuffers26;
	JointBuffersArr[26] = JointConstBuffers27;
	JointBuffersArr[27] = JointConstBuffers28;
	JointBuffersArr[28] = JointConstBuffers29;
	JointBuffersArr[29] = JointConstBuffers30;
	JointBuffersArr[30] = JointConstBuffers31;
	JointBuffersArr[31] = JointConstBuffers32;
	JointBuffersArr[32] = JointConstBuffers33;
	JointBuffersArr[33] = JointConstBuffers34;
	JointBuffersArr[34] = JointConstBuffers35;
	JointBuffersArr[35] = JointConstBuffers36;
	JointBuffersArr[36] = JointConstBuffers37;
#pragma endregion

	DeviceContext->RSSetViewports(1, &Viewport);

	const float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	DeviceContext->ClearRenderTargetView(RenderTargetView, clearColor);
	DeviceContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


	ID3D11Buffer * SkyboxBuffers[3];
	SkyboxBuffers[0] = WorldMatrixBuffer;
	SkyboxBuffers[1] = SkyboxMatrixBuffer;
	SkyboxBuffers[2] = MatrixBuffer;

	ID3D11Buffer * Buffers[2];
	Buffers[0] = WorldMatrixBuffer; 
	Buffers[1] = MatrixBuffer;


	D3D11_MAPPED_SUBRESOURCE WorldMatrixSubresource;
	ZeroMemory(&WorldMatrixSubresource, sizeof(WorldMatrixSubresource));
	DeviceContext->Map(WorldMatrixBuffer, 0,  D3D11_MAP_WRITE_DISCARD, 0, &WorldMatrixSubresource);
	memcpy_s(WorldMatrixSubresource.pData, sizeof(XMFLOAT4X4), &WorldMatrix, sizeof(XMFLOAT4X4));
	DeviceContext->Unmap(WorldMatrixBuffer, 0); 

	D3D11_MAPPED_SUBRESOURCE SkyboxMatrixSubresource;
	ZeroMemory(&SkyboxMatrixSubresource, sizeof(SkyboxMatrixSubresource));
	DeviceContext->Map(SkyboxMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SkyboxMatrixSubresource);
	memcpy_s(SkyboxMatrixSubresource.pData, sizeof(XMFLOAT4X4), &SkyboxPositionMatrix, sizeof(XMFLOAT4X4));
	DeviceContext->Unmap(SkyboxMatrixBuffer, 0);

	D3D11_MAPPED_SUBRESOURCE MatrixSubresource; 
	ZeroMemory(&MatrixSubresource, sizeof(MatrixSubresource)); 
	DeviceContext->Map(MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MatrixSubresource); 
	memcpy_s(MatrixSubresource.pData, sizeof(ViewAndProjectionMatrices), &ViewAndProjMatr, sizeof(ViewAndProjectionMatrices)); 
	DeviceContext->Unmap(MatrixBuffer, 0); 

	DeviceContext->VSSetConstantBuffers(0, 3, SkyboxBuffers);

	DeviceContext->IASetInputLayout(InputLayout);

	const UINT Offset = 0;
	const UINT Size = sizeof(VertexInfo);

	//DeviceContext->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, SkyboxDepthStencilView);
	DeviceContext->OMSetBlendState(0, 0, 0xffffffff);

	DeviceContext->RSSetState(RasterizerState);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Skybox
	DeviceContext->VSSetShader(SkyboxVertexShaderPtr, 0, 0);
	DeviceContext->PSSetShaderResources(0, 1, &SkyboxTextureResourceView);
	DeviceContext->PSSetSamplers(0, 1, &SkyboxTextureSamplerState);
	DeviceContext->PSSetShader(SkyboxPixelShaderPtr, 0, 0);
	DeviceContext->IASetVertexBuffers(0, 1, &SkyboxVertexBuffer, &Size, &Offset);
	DeviceContext->IASetIndexBuffer(SkeletonJointIndexBuffer, DXGI_FORMAT_R32_UINT, Offset);
	DeviceContext->RSSetState(RasterizerState);
	DeviceContext->DrawIndexed(36, 0, 0);
	DeviceContext->RSSetState(FrontCullRasterizerState);
	DeviceContext->DrawIndexed(36, 0, 0);
	//End skybox

	DeviceContext->VSSetConstantBuffers(0, 2, Buffers);
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);
	DeviceContext->VSSetShader(VertexShaderPtr, 0, 0);

	//Ground Plane
	DeviceContext->PSSetShaderResources(0, 1, &GroundTextureResourceView); 
	DeviceContext->PSSetSamplers(0, 1, &GroundTextureSamplerState); 
	DeviceContext->PSSetShader(PixelShaderPtr, 0, 0);
	DeviceContext->IASetVertexBuffers(0, 1, &GroundVertexBuffer, &Size, &Offset);
	DeviceContext->IASetIndexBuffer(GroundIndexBuffer, DXGI_FORMAT_R32_UINT, Offset);
	DeviceContext->RSSetState(RasterizerState);
	DeviceContext->DrawIndexed(6, 0, 0);
	//End Ground Plane

	ID3D11Buffer * AnimationBuffers[3];
	AnimationBuffers[0] = WorldMatrixBuffer;
	AnimationBuffers[1] = MatrixBuffer;
	AnimationBuffers[2] = AnimationMatrixBuffer;



	D3D11_MAPPED_SUBRESOURCE AnimationSubresource;
	ZeroMemory(&AnimationSubresource, sizeof(AnimationSubresource));
	DeviceContext->Map(AnimationMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &AnimationSubresource);
	memcpy_s(AnimationSubresource.pData, sizeof(XMFLOAT4X4) * 37, &JointTransformArray, sizeof(XMFLOAT4X4) * 37);
	DeviceContext->Unmap(AnimationMatrixBuffer, 0);

	DeviceContext->VSSetConstantBuffers(0, 3, AnimationBuffers);
	
	DeviceContext->VSSetShader(AnimationVertexShaderPtr, 0, 0);

	DeviceContext->PSSetShaderResources(0, 1, &TextureResourceView);
	DeviceContext->PSSetSamplers(0, 1, &TextureSamplerState);
	DeviceContext->PSSetShader(PixelShaderPtr, 0, 0);

	DeviceContext->IASetVertexBuffers(0, 1, &MeshVertexBuffer, &Size, &Offset);
	DeviceContext->IASetIndexBuffer(MeshIndexBuffer, DXGI_FORMAT_R32_UINT, Offset);

	DeviceContext->RSSetState(RasterizerState);
	DeviceContext->DrawIndexed(NumIndices, 0, 0);

	DeviceContext->RSSetState(FrontCullRasterizerState);
	DeviceContext->DrawIndexed(NumIndices, 0, 0);

	DeviceContext->IASetIndexBuffer(SkeletonJointIndexBuffer, DXGI_FORMAT_R32_UINT, Offset);
	DeviceContext->VSSetShader(SkeletalJointVertexShaderPtr, 0,0); 
	DeviceContext->IASetVertexBuffers(0, 1, &JointVertexBuffer, &Size, &Offset);
	//End model
	DeviceContext->VSSetShader(VertexShaderPtr, 0, 0);


	//for (int i = 0; i < ModelSkeleton->numJoints; i++)
	//{
	//	ID3D11Buffer * JointBuffers[2];
	//	JointBuffers[0] = JointBuffersArr[i];
	//	JointBuffers[1] = MatrixBuffer;
	//
	//	D3D11_MAPPED_SUBRESOURCE JointMatrixSubresource;
	//	ZeroMemory(&JointMatrixSubresource, sizeof(JointMatrixSubresource));
	//	DeviceContext->Map(JointBuffersArr[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &JointMatrixSubresource);
	//	memcpy_s(JointMatrixSubresource.pData, sizeof(XMFLOAT4X4), &JointTransformArray[i], sizeof(XMFLOAT4X4));
	//	DeviceContext->Unmap(JointBuffersArr[i], 0);
	//
	//	DeviceContext->VSSetConstantBuffers(0, 2, JointBuffers);
	//
	//	DeviceContext->PSSetShader(SkeletalJointPixelShaderPtr, 0, 0);
	//	DeviceContext->DrawIndexed(36, 0, 0);
	//	DeviceContext->RSSetState(RasterizerState);
	//	DeviceContext->DrawIndexed(36, 0, 0);
	//}

	PresentSwapChain(); 
}

void Renderer::Shutdown()
{
	SwapChain->SetFullscreenState(false, 0);

	//if (ModelVerts)
	//{
	//	delete[] ModelVerts; 
	//	ModelVerts = nullptr; 
	//}
	if (SkyboxMatrixBuffer)
	{
		SkyboxMatrixBuffer->Release(); 
		SkyboxMatrixBuffer = nullptr; 
	}
	//if (JointInterpolator)
	//{
	//	delete JointInterpolator; 
	//	JointInterpolator = nullptr; 
	//}
	if (SkyboxVertexShaderPtr)
	{
		SkyboxVertexShaderPtr->Release(); 
		SkyboxVertexShaderPtr = nullptr; 
	}
	if (SkyboxPixelShaderPtr)
	{
		SkyboxPixelShaderPtr->Release(); 
		SkyboxPixelShaderPtr = nullptr; 
	}
	if (SkyboxDepthBuffer)
	{
		SkyboxDepthBuffer->Release(); 
		SkyboxDepthBuffer = nullptr; 
	}
	if (SkyboxTextureResource)
	{
		SkyboxTextureResource->Release(); 
		SkyboxTextureResource = nullptr; 
	}
	if (SkyboxTextureResourceView)
	{
		SkyboxTextureResourceView->Release(); 
		SkyboxTextureResourceView = nullptr; 
	}
	if (SkyboxTextureSamplerState)
	{
		SkyboxTextureSamplerState->Release(); 
		SkyboxTextureSamplerState = nullptr; 
	}
	if (SkyboxVertexBuffer)
	{
		SkyboxVertexBuffer->Release(); 
		SkyboxVertexBuffer = nullptr; 
	}
	if (SkyboxIndexBuffer)
	{
		SkyboxIndexBuffer->Release(); 
		SkyboxIndexBuffer = nullptr; 
	}
	if (FeatureLevel)
		delete FeatureLevel;
	if (SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr; 
	}
	if (Device)
	{
		Device->Release();
		Device = nullptr;
	}
	if (DeviceContext)
	{
		DeviceContext->Release();
		DeviceContext = nullptr; 
	}
	if (RenderTargetView)
	{
		RenderTargetView->Release();
		RenderTargetView = nullptr; 
	}
	if (Backbuffer)
	{
		Backbuffer->Release();
		Backbuffer = nullptr;
	}
	if (DepthStencilView)
	{
		DepthStencilView->Release();
		DepthStencilView = nullptr; 
	}
	if (DepthBuffer)
	{
		DepthBuffer->Release();
		DepthBuffer = nullptr;
	}
	if (PixelShaderPtr)
	{
		PixelShaderPtr->Release(); 
		PixelShaderPtr = nullptr; 
	}
	if (VertexShaderPtr)
	{
		VertexShaderPtr->Release(); 
		VertexShaderPtr = nullptr; 
	}
	if (MeshVertexBuffer)
	{
		MeshVertexBuffer->Release(); 
		MeshVertexBuffer = nullptr; 
	}
	if (MeshIndexBuffer)
	{
		MeshIndexBuffer->Release();
		MeshIndexBuffer = nullptr; 
	}
	if (MatrixBuffer)
	{
		MatrixBuffer->Release(); 
		MatrixBuffer = nullptr; 
	}
	if (WorldMatrixBuffer)
	{
		WorldMatrixBuffer->Release(); 
		WorldMatrixBuffer = nullptr; 
	}
	if (InputLayout)
	{
		InputLayout->Release(); 
		InputLayout = nullptr; 
	}
	if (RasterizerState)
	{
		RasterizerState->Release(); 
		RasterizerState = nullptr; 
	}
	if (Texture)
	{
		Texture->Release(); 
		Texture = nullptr; 
	}
	if (TextureResource)
	{
		TextureResource->Release(); 
		TextureResource = nullptr; 
	}
	if (TextureResourceView)
	{
		TextureResourceView->Release(); 
		TextureResourceView = nullptr; 
	}
	if (TextureSamplerState)
	{
		TextureSamplerState->Release(); 
		TextureSamplerState = nullptr; 
	}
	if (FrontCullRasterizerState)
	{
		FrontCullRasterizerState->Release(); 
		FrontCullRasterizerState = nullptr; 
	}
	if (GroundVertexBuffer)
	{
		GroundVertexBuffer->Release();
		GroundVertexBuffer = nullptr; 
	}
	if (GroundIndexBuffer)
	{
		GroundIndexBuffer->Release(); 
		GroundIndexBuffer = nullptr; 
	}

#pragma region Joint cleanup
	if (SkeletalJointVertexShaderPtr)
	{
		SkeletalJointVertexShaderPtr->Release(); 
		SkeletalJointVertexShaderPtr = nullptr; 
	}
	if (SkeletalJointPixelShaderPtr)
	{
		SkeletalJointPixelShaderPtr->Release(); 
		SkeletalJointPixelShaderPtr = nullptr; 
	}
	if (JointConstBuffers2)
	{
		JointConstBuffers2->Release();
		JointConstBuffers2 = nullptr;
	}
	if (JointConstBuffers3)
	{
		JointConstBuffers3->Release(); 
		JointConstBuffers3 = nullptr; 
	}
	if (JointConstBuffers4)
	{
		JointConstBuffers4->Release();
		JointConstBuffers4 = nullptr;
	}
	if (JointConstBuffers5)
	{
		JointConstBuffers5->Release();
		JointConstBuffers5 = nullptr;
	}
	if (JointConstBuffers6)
	{
		JointConstBuffers6->Release();
		JointConstBuffers6 = nullptr;
	}
	if (JointConstBuffers7)
	{
		JointConstBuffers7->Release();
		JointConstBuffers7 = nullptr;
	}
	if (JointConstBuffers8)
	{
		JointConstBuffers8->Release();
		JointConstBuffers8 = nullptr;
	}
	if (JointConstBuffers9)
	{
		JointConstBuffers9->Release();
		JointConstBuffers9 = nullptr;
	}
	if (JointConstBuffers10)
	{
		JointConstBuffers10->Release();
		JointConstBuffers10 = nullptr;
	}
	if (JointConstBuffers11)
	{
		JointConstBuffers11->Release();
		JointConstBuffers11 = nullptr;
	}
	if (JointConstBuffers12)
	{
		JointConstBuffers12->Release();
		JointConstBuffers12 = nullptr;
	}
	if (JointConstBuffers13)
	{
		JointConstBuffers13->Release();
		JointConstBuffers13 = nullptr;
	}
	if (JointConstBuffers14)
	{
		JointConstBuffers14->Release();
		JointConstBuffers14 = nullptr;
	}
	if (JointConstBuffers15)
	{
		JointConstBuffers15->Release();
		JointConstBuffers15 = nullptr;
	}
	if (JointConstBuffers16)
	{					  
		JointConstBuffers16->Release();
		JointConstBuffers16 = nullptr;
	}
	if (JointConstBuffers17)
	{					
		JointConstBuffers17->Release();
		JointConstBuffers17 = nullptr;
	}
	if (JointConstBuffers18)
	{					 
		JointConstBuffers18->Release();
		JointConstBuffers18 = nullptr;
	}
	if (JointConstBuffers19)
	{					  
		JointConstBuffers19->Release();
		JointConstBuffers19 = nullptr;
	}
	if (JointConstBuffers20)
	{					 
		JointConstBuffers20->Release();
		JointConstBuffers20 = nullptr;
	}
	if (JointConstBuffers21)
	{					  
		JointConstBuffers21->Release();
		JointConstBuffers21 = nullptr;
	}
	if (JointConstBuffers22)
	{					  
		JointConstBuffers22->Release();
		JointConstBuffers22 = nullptr;
	}
	if (JointConstBuffers23)
	{					  
		JointConstBuffers23->Release();
		JointConstBuffers23 = nullptr;
	}
	if (JointConstBuffers24)
	{					  
		JointConstBuffers24->Release();
		JointConstBuffers24 = nullptr;
	}
	if (JointConstBuffers25)
	{					  
		JointConstBuffers25->Release();
		JointConstBuffers25 = nullptr;
	}
	if (JointConstBuffers26)
	{					  
		JointConstBuffers26->Release();
		JointConstBuffers26 = nullptr;
	}
	if (JointConstBuffers27)
	{					  
		JointConstBuffers27->Release();
		JointConstBuffers27 = nullptr;
	}
	if (JointConstBuffers28)
	{					 
		JointConstBuffers28->Release();
		JointConstBuffers28 = nullptr;
	}
	if (JointConstBuffers29)
	{					 
		JointConstBuffers29->Release();
		JointConstBuffers29 = nullptr;
	}
	if (JointConstBuffers30)
	{					
		JointConstBuffers30->Release();
		JointConstBuffers30 = nullptr;
	}
	if (JointConstBuffers31)
	{					  
		JointConstBuffers31->Release();
		JointConstBuffers31 = nullptr;
	}
	if (JointConstBuffers32)
	{					  
		JointConstBuffers32->Release();
		JointConstBuffers32 = nullptr;
	}
	if (JointConstBuffers33)
	{					
		JointConstBuffers33->Release();
		JointConstBuffers33 = nullptr;
	}
	if (JointConstBuffers34)
	{				
		JointConstBuffers34->Release();
		JointConstBuffers34 = nullptr;
	}
	if (JointConstBuffers35)
	{			
		JointConstBuffers35->Release();
		JointConstBuffers35 = nullptr;
	}
	if (JointConstBuffers36)
	{		
		JointConstBuffers36->Release();
		JointConstBuffers36 = nullptr;
	}
	if (JointConstBuffers37)
	{					  
		JointConstBuffers37->Release();
		JointConstBuffers37 = nullptr;
	}
#pragma endregion
}
