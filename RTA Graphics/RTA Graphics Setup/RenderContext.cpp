#include "RenderContext.h"
#include "Renderer.h"

RenderContext::RenderContext()
{
}
RenderContext::~RenderContext()
{
	delete CurrentRenderSet; 
}

void RenderContext::AddNode(RenderNode* nodeToAdd)
{
	CurrentRenderSet->AddNode(nodeToAdd); 
	nodeToAdd->SetParent(this); 
}

void RenderContext::ContextRenderFunction(RenderNode * Node)
{
	RenderContext * context = (RenderContext*)Node; 

	//Apply rendering state changes like rast, blend, etc here
	//Set shaders here
	Renderer::Render();
	//set rendering state back 
}