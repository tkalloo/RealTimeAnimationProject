#pragma once
#include "RenderNode.h"
#include "RenderContext.h"
#include "RenderMesh.h"

class RenderShape : public RenderNode
{
private: 
	RenderContext * Context; 
	RenderMesh * Mesh; 
	XMFLOAT4X4 worldMatrix; 

	static void ShapeRenderFunc(RenderNode * Node); 
public:
	RenderShape();
	virtual ~RenderShape();
	void * renderMesh;
};

