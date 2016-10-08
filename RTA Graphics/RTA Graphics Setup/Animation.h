#pragma once
#include "Renderer.h"
#include <vector> 
class Animation; 
struct Keyframe
{
	float animationTime; 
	int currFrame; 

	XMFLOAT4X4 TransformationMatrix; 
	Keyframe * Next; 
	Animation * Animation; 
};

struct Joint
{
	int numKeyframes;
	XMFLOAT4X4 BindMatrix;

	vector<Keyframe*> Keyframes;
	int JointIndex; 
};

struct Skeleton
{
	int numJoints; 
	int numMaxKeyframes; 

	vector<Joint*> Joints; 
	float TotalAnimationDuration; 
	float AnimationFrequency; 
};

class Animation : public Renderer
{
	int numKeyFrames;
	float Duration;

public:
	Animation();
	~Animation();

	inline int GetNumKeyFrames(void) { return numKeyFrames; }
	inline float GetDuration(void) { return Duration;  }
	vector<Keyframe*> Keyframes;
};

