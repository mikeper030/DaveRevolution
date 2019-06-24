#pragma once
#include "Consumable.h"
#include "Animation.h"
#include "SoundManager.h"
class Coin : public Consumable

{
public:

	Coin(sf::Sprite& sprite, sf::FloatRect& rectt);
	void animate(const float& t,RenderWindow&w) override;
private:
	SoundManager& manager;
};

