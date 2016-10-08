#pragma once
class RenderNode; 

typedef void(*EDRenderFunc)(RenderNode &node); 

class RenderNode
{

protected: 
	RenderNode* next; 
	RenderNode* parent;
public:
	RenderNode() : next(nullptr), parent(nullptr) {}


	EDRenderFunc renderFunc; 

	void RenderProcess()
	{
		renderFunc(*this); 
	}

	inline RenderNode* GetNext(void) { return next;  }

	inline void SetNext(RenderNode * newNext) { next = newNext;  }

	inline RenderNode* GetParent(void) { return parent;  }

	inline void SetParent(RenderNode* newParent) { parent = newParent;  }


	//~RenderNode();
};

