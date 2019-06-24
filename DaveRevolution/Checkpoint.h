#pragma once
#include "StaticObject.h"
class Checkpoint :
	public StaticObject
{
private:
	int m_placement;
	bool m_activeCheckpoint;
public:
	void animate(const float& t, RenderWindow& w) override;
	void setActiveCheckpoint(const bool& flag);
	const bool &checkPointActive();
	Checkpoint(sf::Sprite& sprite, sf::FloatRect& rect, const int&placement);
	
};
