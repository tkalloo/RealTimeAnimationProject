#include "TransformationNode.h"


TransformationNode::TransformationNode()
{
}


TransformationNode::~TransformationNode()
{
}


XMFLOAT4X4& TransformationNode::GetWorld()
{
	if (true == isDirty)
	{
		if (nullptr == this->ParentNode)
			WorldMatrix = LocalMatrix; 
		else
		{
			XMMATRIX TempWorld = XMLoadFloat4x4(&WorldMatrix); 
			XMMATRIX TempLocal = XMLoadFloat4x4(&LocalMatrix);
			XMMATRIX TempParent = XMLoadFloat4x4(&ParentNode->GetWorld());
			TempWorld = TempLocal * TempParent;

			XMStoreFloat4x4(&WorldMatrix, TempWorld); 
		}
		isDirty = false;
	}
	return WorldMatrix; 
}

void TransformationNode::MakeDirty()
{
	isDirty = true; 

	for each (TransformationNode* child in Children)
		child->MakeDirty();
	
}

XMFLOAT4X4 & TransformationNode::GetLocal()
{
	this->MakeDirty(); 
	return LocalMatrix; 
}