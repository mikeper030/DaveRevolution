#pragma once
#include "Consumable.h"
#include <iostream>
class DoorKey : public Consumable
{
public:
	DoorKey(Sprite& sprite, sf::FloatRect& rect);
	void animate(const float& t, RenderWindow& w) override;
	private:
		bool is_up;
};

