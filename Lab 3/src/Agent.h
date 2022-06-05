#pragma once
#ifndef __AGENT__
#define __AGENT__

#include <glm/vec4.hpp>
#include "NavigationObject.h"

class Agent : public NavigationObject
{
public:
	Agent();
	~Agent();

	// Inherited via GameObject
	void Draw() override = 0;
	void Update() override = 0;
	void Clean() override = 0;

	// getters
	[[nodiscard]] glm::vec2 GetTargetPosition() const;
	[[nodiscard]] glm::vec2 GetCurrentDirection() const;
	[[nodiscard]] float GetLOSDistance() const;
	[[nodiscard]] bool HasLOS() const;
	[[nodiscard]] float GetCurrentHeading() const;
	[[nodiscard]] glm::vec4 GetLOSColour() const;

	// setters
	void SetTargetPosition(glm::vec2 new_position);
	void SetCurrentDirection(glm::vec2 new_direction);
	void SetLOSDistance(float distance);
	void SetHasLOS(bool state);
	void SetCurrentHeading(float heading);
	void SetLOSColour(glm::vec4 colour);

private:
	void ChangeDirection(); // From scalar to vec2.

	float m_currentHeading; // Scalar angle in degrees.
	glm::vec2 m_currentDirection; // Vec2 direction/angle.
	glm::vec2 m_targetPosition; // Where the agent wants to be.

	// LOS (line of sight)
	float m_LOSDistance; // (Position + direction) * distance
	bool m_hasLOS; // Used for collision.
	glm::vec4 m_LOSColour;
};



#endif /* defined ( __AGENT__) */