#pragma once
#include "Consumable.h"
class Door :public Consumable
{
public:
	Door(sf::Sprite& sprite, sf::FloatRect& rect);

	void animate(const float& t, RenderWindow& w)override;
	
	
};

