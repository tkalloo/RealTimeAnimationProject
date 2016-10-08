#pragma once
#include "RenderNode.h"
class RenderSet : public RenderNode 
{
	//RenderSet is a linked list of render nodes to be drawn this frame 
	RenderNode * head;
	RenderNode * tail;

public:

	RenderSet();

	inline RenderNode* GetHead(void) { return head;  }
	inline RenderNode* GetTail(void) { return tail;  }

	virtual void AddNode(RenderNode* nodeToAdd); 

	void ClearRenderSet(void); 
	virtual ~RenderSet() {}
};

