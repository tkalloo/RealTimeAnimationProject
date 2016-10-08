#include "RenderSet.h"


RenderSet::RenderSet()
{
	head = nullptr; 
	tail = nullptr; 
}


void RenderSet::AddNode(RenderNode* nodeToAdd)
{
	nodeToAdd->SetNext(nullptr); 

	if (nullptr == GetHead())
		head = nodeToAdd; 
	else
		tail->SetNext(nodeToAdd); 

	tail = nodeToAdd; 
}