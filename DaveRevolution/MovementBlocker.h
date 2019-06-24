#pragma once
#include "StaticObject.h"
class MovementBlocker :
	public StaticObject
{
public:
	MovementBlocker(const sf::Sprite& sprite,const  sf::FloatRect& rect);
	virtual bool intersects(GameObject& otherObject);
	MovementBlocker();
	~MovementBlocker();
};

