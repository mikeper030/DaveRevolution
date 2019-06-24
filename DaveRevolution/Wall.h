#pragma once
#include "StaticObject.h"
class Wall :
	public StaticObject
{
public:
	Wall(const sf::Sprite& sprite,const  sf::FloatRect& rect);
	
};

