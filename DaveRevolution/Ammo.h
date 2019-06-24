#pragma once
#include "Consumable.h"
class Ammo :
	public Consumable
{
public:
	Ammo(sf::Sprite& sprite, sf::FloatRect& rect);
	void animate(const float& t, RenderWindow& w) override;
private:
	bool is_up;
};

