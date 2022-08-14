
#pragma once
#ifndef __TORPEDOBASE__
#define __TORPEDOBASE__
#include "TorpedoAnimationState.h"
#include "Sprite.h"


class Torpedobase  : public  Sprite
{
public:
	Torpedobase();
	~Torpedobase();

	// Life Cycle Methods
	void Draw() override;
	void Update() override;
	void Clean() override;

	// setters
	void SetAnimationState(TorpedoAnimationState new_state);
private:
	void BuildAnimations();

	TorpedoAnimationState m_currentAnimationState;

	float m_speed;

	glm::vec2 m_direction;
};

#endif /* defined (__TORPEDO_K__)*/