#include "RenderMesh.h"
#include <iostream>
#include <fstream>
//#pragma comment(lib, "DirectXTK.lib")
#include "DDSTextureLoader.h"
//#include "Utilities.h"
RenderMesh::RenderMesh()
{
	numVerts = 0; 
	startVertex = 0; 
	startIndex = 0; 
	numPrimitives = 0; 
	numJoints = 0; 
	numKeyFrames = 0; 
	AnimationDuration = 0.0f; 
	Frequency = 0; 
	JointKeyFrameNumber = 0; 
}

RenderMesh::~RenderMesh()
{
}


void RenderMesh::LoadAnimationFromBinary(Skeleton * Model, const char* _filepath)
{
	if (nullptr == _filepath)
		return;
	fstream file;
	file.open(_filepath, std::ios_base::binary | std::ios_base::in);

	if (false == file.is_open())
	{
		file.clear();
		return;
	}
	file.read((char*)&Model->numMaxKeyframes, sizeof(Model->numMaxKeyframes));
	file.read((char*)&Model->TotalAnimationDuration, sizeof(Model->TotalAnimationDuration));
	file.read((char*)&Model->AnimationFrequency, sizeof(Model->AnimationFrequency));

	file.close();
}

void RenderMesh::LoadJointsFromBinary(Skeleton * Model, const char* _filepath)
{
	if (nullptr == _filepath)
		return;

	fstream file;
	file.open(_filepath, std::ios_base::binary | std::ios_base::in);

	if (false == file.is_open())
	{
		file.clear();
		return;
	}

	file.read((char*)&Model->numJoints, sizeof(unsigned int));

	for (int i = 0; i < Model->numJoints; i++)
	{
		Joint * tempJoint = new Joint;
		for (int Outer = 0; Outer < 4; Outer++)
			for (int Inner = 0; Inner < 4; Inner++)
				file.read((char*)&tempJoint->BindMatrix.m[Outer][Inner], sizeof(float));
		Model->Joints.push_back(tempJoint); 
	}
	
	for (int i = 0; i < Model->numJoints; i++)
	{
		file.read((char*)&Model->Joints[i]->JointIndex, sizeof(int));
		file.read((char*)&Model->Joints[i]->numKeyframes, sizeof(unsigned int));

		if (Model->Joints[i]->numKeyframes > 0)
		{
			for (int currKeyframe = 0; currKeyframe < Model->Joints[i]->numKeyframes; currKeyframe++)
			{
				Keyframe* TempKeyframe = new Keyframe;
				file.read((char*)&TempKeyframe->currFrame, sizeof(unsigned int));

				for (int Outer = 0; Outer < 4; Outer++)
					for (int Inner = 0; Inner < 4; Inner++)
						file.read((char*)&TempKeyframe->TransformationMatrix.m[Outer][Inner], sizeof(float));
				Model->Joints[i]->Keyframes.push_back(TempKeyframe);
			}
		}
		else
		{
			Keyframe* TempKeyframe = new Keyframe;
			XMStoreFloat4x4(&TempKeyframe->TransformationMatrix, XMMatrixIdentity()); 
			Model->Joints[i]->Keyframes.push_back(TempKeyframe);
		}
	}
	file.close();
}

RenderMesh* RenderMesh::LoadMeshFromBinary(const char* _filepath)
{
	if (nullptr == _filepath)
		return nullptr;

	fstream file;
	file.open(_filepath, std::ios_base::binary | std::ios_base::in);
	
	if (false == file.is_open())
	{
		file.clear(); 
		return nullptr; 
	}

	file.read((char*)&this->numVerts, sizeof(unsigned int));

	for (int i = 0; i <this->numVerts; i++)
	{
		XMFLOAT3 tempPos;
		XMFLOAT3 tempNorms;
		XMFLOAT2 tempUVs;
		
		file.read((char*)&tempPos.x, sizeof(float));
		file.read((char*)&tempPos.y, sizeof(float));
		file.read((char*)&tempPos.z, sizeof(float));
	
		file.read((char*)&tempNorms.x, sizeof(float));
		file.read((char*)&tempNorms.y, sizeof(float));
		file.read((char*)&tempNorms.z, sizeof(float));
	
		file.read((char*)&tempUVs.x, sizeof(float));
		file.read((char*)&tempUVs.y, sizeof(float));
	
		Positions.push_back(tempPos);
		Normals.push_back(tempNorms);
		UVs.push_back(tempUVs);

		int tempNumBlendInfo = 0;
		file.read((char*)&tempNumBlendInfo, sizeof(int)); 
		NumberOfBlendInfo.push_back(tempNumBlendInfo); 

		for (int BlendCount = 0; BlendCount< tempNumBlendInfo; BlendCount++) //Use a map instead?
		{
			int tempBlendIndex = 0; 
			float tempBlendWeight = 0.0f; 
			file.read((char*)&tempBlendIndex, sizeof(tempBlendIndex)); 
			file.read((char*)&tempBlendWeight, sizeof(tempBlendWeight)); 

			BlendIndices.push_back(tempBlendIndex); 
			BlendWeights.push_back(tempBlendWeight); 
		}

	}

	int numTriangles = 0;
	file.read((char*)&numTriangles, sizeof(numTriangles));
	
	for (int i = 0; i < numTriangles * 3; i++)
	{
		int Index = 0;
		file.read((char*)&Index, sizeof(Index));
		Indices.push_back(Index);
	}

	file.close(); 
	return this;
}