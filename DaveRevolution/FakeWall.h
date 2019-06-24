#pragma once
#include "StaticObject.h"
#include "SoundManager.h"
class FakeWall :
	public StaticObject
{
public:
	FakeWall(Sprite& sprite, sf::FloatRect& rect);
	void animate(const float& t, RenderWindow& w) override;

};

