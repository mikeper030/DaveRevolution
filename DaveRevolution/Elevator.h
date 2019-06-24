#pragma once
#include "DynamicObject.h"
class Elevator :
	public DynamicObject
{
public:
	Elevator(sf::Sprite& sprite, sf::FloatRect& rect);

	void changeDirection();

	virtual void updateCharacter(const sf::Vector2f& vector, const float& f,const int& direction, bool&) override;

	virtual void animateCharacter(sf::RenderWindow& window,const float& time)override;

	virtual void animate(const float& t, RenderWindow& w);

};
