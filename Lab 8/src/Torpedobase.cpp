#include "Torpedobase.h"
#include "TextureManager.h"

Torpedobase::Torpedobase()
{

}
Torpedobase::~Torpedobase()
= default;

void Torpedobase::Draw()
{
	
}

void Torpedobase::Update()
{
	GetTransform()->position += m_direction;
}

void Torpedobase::Clean()
{
}

void Torpedobase::SetAnimationState(const TorpedoAnimationState new_state)
{
	
}

void Torpedobase::BuildAnimations()
{
	auto fired_animation = Animation();

	fired_animation.name = "fired";
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired1"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired2"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired3"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired4"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired5"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired6"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired7"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired8"));

	SetAnimation(fired_animation);
}
