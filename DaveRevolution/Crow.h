#pragma once
#include "DynamicObject.h"
class Crow :
	public DynamicObject
{
public:
	Crow(sf::Sprite& sprite, sf::FloatRect& rect);
	void updateCharacter(const sf::Vector2f& vector, const float& f,const int& direction,bool& shoot)override;
	void animateCharacter(sf::RenderWindow& window,const float& time);
	void animate(const float& t, RenderWindow& w);
	void changeDirection();

};

