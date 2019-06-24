#include "MovementBlocker.h"

MovementBlocker::MovementBlocker(const sf::Sprite& sprite,const sf::FloatRect& rect)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
}


bool MovementBlocker::intersects(GameObject& otherObject)
{
	if (m_sprite.getGlobalBounds().intersects(otherObject.getSprite().getGlobalBounds()))
	{
		return true;
	}
	return false;
}

MovementBlocker::MovementBlocker()
{
}


MovementBlocker::~MovementBlocker()
{
}
