#pragma once
#include "Consumable.h"
class Life :
	public Consumable 
{
public:
	Life(sf::Sprite& sprite, sf::FloatRect& rect);
	void animate(const float& t, RenderWindow& window);
private:
	bool is_up;
};

