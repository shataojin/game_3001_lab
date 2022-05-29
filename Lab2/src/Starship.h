#pragma once
#ifndef __Starship__
#define __Starship__

#include "DisplayObject.h"

class Starship final : public DisplayObject {
public:
	Starship();
	~Starship() override;

	// Inherited via GameObject
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	void Reset();
private:
	void Move();
	void CheckBounds();


	glm::vec2 m_startPos;
};


#endif /* defined (__Starship__) */