#pragma once
#include "Animation.h"
class TransformationNode //Joint?
{
	XMFLOAT4X4 WorldMatrix; 
	XMFLOAT4X4 LocalMatrix; 

	TransformationNode * ParentNode; 

	bool isDirty; 

	vector<TransformationNode*> Children; 

public:
	TransformationNode();
	~TransformationNode();

	XMFLOAT4X4& GetWorld();
	void MakeDirty(); 
	XMFLOAT4X4 & GetLocal(); 
};

