#pragma once
#include "RenderNode.h"
#include "RenderSet.h"

class RenderContext : public RenderNode
{
	//contains the state of the renderer, such as currently active shaders
protected: 
	RenderSet* CurrentRenderSet;

	//Shaders and state objects go here

public:
	void AddNode(RenderNode* nodeToAdd);

	inline void CreateRenderSet(void) { CurrentRenderSet = new RenderSet;  }
	inline void ClearRenderSet(void) { CurrentRenderSet->ClearRenderSet(); }


	RenderContext();
	virtual ~RenderContext();

	static void ContextRenderFunction(RenderNode * Node); 
};

