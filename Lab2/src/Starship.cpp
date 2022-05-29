#include "Starship.h"
#include "TextureManager.h"


Starship::Starship() :m_startPos(glm::vec2(400.0f, 400.0f))
{
	TextureManager::Instance().Load("../Assets/textures/d7_small.png", "d7");

	const auto size = TextureManager::Instance().GetTextureSize("d7");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetTransform()->position = m_startPos;
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;

	SetType(GameObjectType::SPACE_SHIP);
}

Starship::~Starship()
= default;

void Starship::Draw()
{
	// draw the Starship
	TextureManager::Instance().Draw("d7", GetTransform()->position, 0, 255, true);
}

void Starship::Update()
{
	Move();
	CheckBounds();
}

void Starship::Clean()
{
}

void Starship::Move()
{
	GetTransform()->position = GetTransform()->position + GetRigidBody()->velocity * 5.0f;
}

void Starship::CheckBounds()
{
}

void Starship::Reset()
{
	GetTransform()->position = m_startPos;
}
