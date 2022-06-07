#include "Agent.h"

#include "Util.h"

Agent::Agent()
{

}

Agent::~Agent()
= default;

glm::vec2 Agent::GetTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Agent::GetCurrentDirection() const
{
	return m_currentDirection;
}

float Agent::GetLOSDistance() const
{
	return m_LOSDistance;
}

bool Agent::HasLOS() const
{
	return m_hasLOS;
}

float Agent::GetCurrentHeading() const
{
	return m_currentHeading;
}

glm::vec4 Agent::GetLOSColour() const
{
	return m_LOSColour;
}

glm::vec2 Agent::GetLeftLOSEndPoint() const
{
	return m_leftLOSEEndPoint;
}

glm::vec2 Agent::GetMiddleLOSEndPoint() const
{
	return m_middleLOSEndPoint;
}

glm::vec2 Agent::GetRightLOSEndPoint() const
{
	return m_rightLOSEndPoint;
}



glm::vec2 Agent::GetRightLOSEndPointX() const
{
	return m_rightLOSEndPointX;
}

glm::vec2 Agent::GetLeftLOSEndPointX() const
{
	return m_leftLOSEEndPointX;
}




bool* Agent::GetCollisionWhiskers()
{
	return m_collisionWhiskers;
}

glm::vec4 Agent::GetLineColor(int index)
{
	return m_lineColour[index];
}

float Agent::GetWhiskerAngle() const
{
	return m_whiskerAnagle;
}

void Agent::SetTargetPosition(const glm::vec2 new_position)
{
	m_targetPosition = new_position;
}

void Agent::SetCurrentDirection(const glm::vec2 new_direction)
{
	m_currentDirection = new_direction;
}

void Agent::SetLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}

void Agent::SetHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1);
}

void Agent::SetCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	ChangeDirection();
}

void Agent::SetLOSColour(const glm::vec4 colour)
{
	m_LOSColour = colour;
}

void Agent::SetLeftLOSEndPoint(glm::vec2 point)
{
	m_leftLOSEEndPoint = point;
}

void Agent::SetMiddleLOSEndPoint(glm::vec2 point)
{
	m_middleLOSEndPoint = point;
}

void Agent::SetRightLOSEndPoint(glm::vec2 point)
{
	m_rightLOSEndPoint = point;
}


void Agent::SetRightLOSEndPointX(glm::vec2 point)
{
	m_rightLOSEndPointX = point;
}

void Agent::SetLeftLOSEndPointX(glm::vec2 point)
{
	m_leftLOSEEndPointX = point;
}




void Agent::SetLineColor(int index, glm::vec4 color)
{
	m_lineColour[index] = color;
}

void Agent::SetWhiskerAngle(float angle)
{
	m_whiskerAnagle = angle;
}

void Agent::UpdateWhiskers(float angle)
{
	SetWhiskerAngle(angle);
	SetMiddleLOSEndPoint(GetTransform()->position+GetCurrentDirection()*GetLOSDistance());

	float x = sin((GetCurrentHeading() - m_whiskerAnagle + 90) * Util::Deg2Rad);
	float y = cos((GetCurrentHeading() - m_whiskerAnagle + 90) * Util::Deg2Rad);
	SetLeftLOSEndPoint(GetTransform()->position+ glm::vec2(x,-y)*(GetLOSDistance()*0.75f));

	x = sin((GetCurrentHeading() + m_whiskerAnagle + 90) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() + m_whiskerAnagle + 90) * Util::Deg2Rad);
	SetRightLOSEndPoint(GetTransform()->position+glm::vec2(x,-y)*(GetLOSDistance()*0.75f));

	x = sin((GetCurrentHeading() + m_whiskerAnagle + 75) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() + m_whiskerAnagle + 75) * Util::Deg2Rad);
	SetRightLOSEndPointX(GetTransform()->position + glm::vec2(x, -y) * (GetLOSDistance() * 0.75f));

	x = sin((GetCurrentHeading() - m_whiskerAnagle + 75) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() - m_whiskerAnagle + 75) * Util::Deg2Rad);
	SetLeftLOSEndPointX(GetTransform()->position + glm::vec2(x, -y) * (GetLOSDistance() * 0.75f));

}

void Agent::ChangeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);
}
