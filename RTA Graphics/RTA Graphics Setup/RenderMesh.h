#pragma once
#include "RenderNode.h"
#include <vector> 
using namespace std; 
#include <DirectXMath.h> 
using namespace DirectX;
//#include "Utilities.h"
#include "Animation.h"
class RenderMesh : public RenderNode
{
public: 
	vector<XMFLOAT3> Positions; 
	vector<XMFLOAT2> UVs; 
	vector<XMFLOAT4> Colors; 
	vector<XMFLOAT3> Normals; 
	vector<int> BlendIndices; 
	vector<float> BlendWeights; 
	vector<int> NumberOfBlendInfo;
	vector<int> Indices;

	int numVerts;
	int startVertex;
	int startIndex;
	int numPrimitives; 
	int numJoints; 

	//vector<int> JointIndices;
	vector<int> KeyFrameNumberVec;
	vector<Keyframe*> KeyframeVector;
	int numKeyFrames; 
	float AnimationDuration; 
	unsigned int Frequency;
	int JointKeyFrameNumber = 0; 
	Skeleton * MeshSkeleton; 

	vector<XMFLOAT4X4> BindMatrices; 
	vector<Keyframe*> EachJointsKeyFrames;


public:
	RenderMesh();
	virtual ~RenderMesh();

	RenderMesh* LoadMeshFromBinary(const char* _filepath);
	void LoadJointsFromBinary(Skeleton * Model, const char* _filepath);
	void LoadAnimationFromBinary(Skeleton * Model, const char* _filepath);
};

