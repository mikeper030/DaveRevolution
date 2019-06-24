#pragma once
#include "StaticObject.h"
//an abstract class to use as base
//for conumable objects such as coins ammo and life
class Consumable :
	public StaticObject
{
public:
	Consumable(sf::Sprite& sprite, sf::FloatRect& rect);
	Consumable(sf::Sprite& sprite, sf::FloatRect& rect, const int& counter);
	virtual void consumeAnim(const bool& f);
	const bool& consumed();
	virtual void animate(const float& t, RenderWindow& w)=0;
protected:
	bool m_consume_anim;
	int m_anim_counter, max;

	
};

