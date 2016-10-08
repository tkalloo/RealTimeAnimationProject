#include "Interpolator.h"


Interpolator::Interpolator()
{
	currentTime = 0.0f; 
	animation = nullptr; 
	CurrentFrame = nullptr; 
	PreviousFrame = nullptr;
	NextFrame = nullptr;
}


Interpolator::~Interpolator()
{
	delete JointInterpolator; 
}

XMFLOAT4X4 Interpolator::Process(Joint* jointToProcess, float currTime)
{
	XMFLOAT4X4 Error;
	XMStoreFloat4x4(&Error, XMMatrixIdentity()); 
	if (currTime < 0.0f || currTime > TotalTime || nullptr == jointToProcess)
		return Error;

	currentTime = currTime;
	CurrentJoint = jointToProcess; 
	float tweenTime = 0.0f; 
	float frameTime = 0.0f; 
	for (int i = 0; i < CurrentJoint->numKeyframes - 1; i++)
	{
		if (currentTime > CurrentJoint->Keyframes[i]->animationTime && currentTime < CurrentJoint->Keyframes[i + 1]->animationTime)
		{
			PreviousFrame = CurrentJoint->Keyframes[i];
			NextFrame = CurrentJoint->Keyframes[i + 1];
			tweenTime = CurrentJoint->Keyframes[i + 1]->animationTime - CurrentJoint->Keyframes[i]->animationTime;
			frameTime = currentTime - CurrentJoint->Keyframes[i]->animationTime;

			XMMATRIX prevMatrix = XMLoadFloat4x4(&PreviousFrame->TransformationMatrix);
			XMMATRIX nextMatrix = XMLoadFloat4x4(&NextFrame->TransformationMatrix);

			float t = frameTime / tweenTime;

			XMMATRIX currMatrix = (1 - t) * prevMatrix + t * nextMatrix;
			XMFLOAT4X4 ToReturn;
			XMStoreFloat4x4(&ToReturn, currMatrix);
			XMMATRIX TempTranspose = XMMatrixTranspose(XMLoadFloat4x4(&ToReturn));
			XMStoreFloat4x4(&ToReturn, TempTranspose);

			ToReturn.m[0][2] *= -1.0f;
			ToReturn.m[1][2] *= -1.0f;
			ToReturn.m[2][0] *= -1.0f;
			ToReturn.m[2][1] *= -1.0f;
			ToReturn.m[3][2] *= -1.0f;
			return ToReturn;
		}
	}
	return Error;
}


XMFLOAT4X4 Interpolator::ProcessBackwards(Joint* jointToProcess, float currTime, float totalAnimationTime)
{
	XMFLOAT4X4 Error;
	XMStoreFloat4x4(&Error, XMMatrixIdentity());

	currentTime = currTime;
	CurrentJoint = jointToProcess;
	float tweenTime = 0.0f;
	float frameTime = 0.0f;
	for (int i = CurrentJoint->numKeyframes -1 ; i > 0; i--)
	{
		if (currentTime  < ((totalAnimationTime - CurrentJoint->Keyframes[i]->animationTime) + totalAnimationTime) && currentTime > ((totalAnimationTime - CurrentJoint->Keyframes[i -1]->animationTime) + totalAnimationTime))
		{
			PreviousFrame = CurrentJoint->Keyframes[i];
			NextFrame = CurrentJoint->Keyframes[i];
			tweenTime = CurrentJoint->Keyframes[i]->animationTime - CurrentJoint->Keyframes[i - 1]->animationTime;
			frameTime = currentTime - CurrentJoint->Keyframes[i -1]->animationTime;

			XMMATRIX prevMatrix = XMLoadFloat4x4(&PreviousFrame->TransformationMatrix);
			XMMATRIX nextMatrix = XMLoadFloat4x4(&NextFrame->TransformationMatrix);

			float t = frameTime / tweenTime;

			XMMATRIX currMatrix = (1 - t) * prevMatrix + t * nextMatrix;
			XMFLOAT4X4 ToReturn;
			XMStoreFloat4x4(&ToReturn, currMatrix);
			XMMATRIX TempTranspose = XMMatrixTranspose(XMLoadFloat4x4(&ToReturn));
			XMStoreFloat4x4(&ToReturn, TempTranspose);

			ToReturn.m[0][2] *= -1.0f;
			ToReturn.m[1][2] *= -1.0f;
			ToReturn.m[2][0] *= -1.0f;
			ToReturn.m[2][1] *= -1.0f;
			ToReturn.m[3][2] *= -1.0f;
			return ToReturn;
		}
	}
	return Error;
}