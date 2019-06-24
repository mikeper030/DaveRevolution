#include "Checkpoint.h"
#include <iostream>




Checkpoint::Checkpoint(sf::Sprite& sprite, sf::FloatRect& rect ,const int& placement)
	:m_placement(placement),m_activeCheckpoint(false)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
	if (!m_texture.loadFromFile("police_station.png"))
		throw(std::runtime_error("Image not found"));
	m_sprite.setTexture(m_texture);
	m_sprite.scale(0.5f, 0.5f);
	m_sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 125);
	
}

void Checkpoint::animate(const float& t, RenderWindow& w)
{
	w.draw(m_sprite);
}

void Checkpoint::setActiveCheckpoint(const bool& flag)
{
	m_activeCheckpoint = flag;
}


const bool& Checkpoint::checkPointActive()
{
	return m_activeCheckpoint;
}


