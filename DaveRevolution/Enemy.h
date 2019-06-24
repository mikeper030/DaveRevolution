#pragma once
#include "DynamicObject.h"
#include <iostream>
class Enemy :public DynamicObject
{
public:
	Enemy(sf::Sprite& sprite, sf::FloatRect& rect);

	void changeDirection();

	virtual void updateCharacter(const sf::Vector2f& velocity, const float& f,const int& direction, bool&shoot) override;

	virtual void animateCharacter(sf::RenderWindow& window,const  float& time)override;


	virtual void animate(const float& t, RenderWindow& w);

	
};




