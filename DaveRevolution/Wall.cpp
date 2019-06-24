#include "Wall.h"

//////////////////////////////////
//         Create Wall			//
//////////////////////////////////
Wall::Wall(const sf::Sprite& sprite,const sf::FloatRect&rect)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
}





