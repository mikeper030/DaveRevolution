#include "Consumable.h"
#include <iostream>
//default constructor
Consumable::Consumable(sf::Sprite& sprite, sf::FloatRect& rect)
	:m_consume_anim(false), m_anim_counter(0), max(20)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
}
//custom anim counter constructor
Consumable::Consumable(sf::Sprite& sprite, sf::FloatRect& rect,const int& counter)
	:m_consume_anim(false), m_anim_counter(counter), max(20)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
}

void Consumable::consumeAnim(const bool& f)
{
	m_consume_anim = f;
}

const bool& Consumable::consumed()
{
	return m_consume_anim;
}
