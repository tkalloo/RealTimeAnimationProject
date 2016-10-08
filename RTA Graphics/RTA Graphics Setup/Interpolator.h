#pragma once
#include "Animation.h"
//#include <vector> 

class Interpolator : public Animation
{
	float currentTime; 
	Joint * CurrentJoint; 
	Animation * animation; 
	Keyframe * CurrentFrame; 
	Keyframe * PreviousFrame; 
	Keyframe * NextFrame; 
	float TotalTime; 
public:
	Interpolator();
	~Interpolator();

	inline void SetAnimation( Animation* _animation) { animation = _animation;  }
	inline void SetTime(float _time) { currentTime = _time; }
	inline void SetTotalTime(float _totaltime) { TotalTime = _totaltime; }
	inline void AddTime(float _additionalTime) { currentTime += _additionalTime;  }

	XMFLOAT4X4 Process(Joint* jointToProcess, float currTime);
	XMFLOAT4X4 ProcessBackwards(Joint* jointToProcess, float currTime, float totalAnimationTime);
};

