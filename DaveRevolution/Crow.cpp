#include "Crow.h"
#include <iostream>
#include "Exceptions.h"
Crow::Crow(sf::Sprite& sprite, sf::FloatRect& rect)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });

	if (!animeTexture.loadFromFile("crow.png"))
		throw(FileNotFoundException("crow png"));


	sf::Vector2f s(1, 1);
	if (!m_Anime.loadFromXML("crow.xml", animeTexture, s)) 
		throw(FileNotFoundException("crow.xml"));

	m_Anime.set("crow");
	m_Velocity.x = 11.f;
	setDirection(Right);
}

void Crow::updateCharacter(const sf::Vector2f& vector, const float& f,const int& direction, bool& shoot)
{
	if (getVelocity().x > 0) {
		
		m_Anime.flip(false);
		setDirection(Right);
	}
	if (getVelocity().x < 0)
	{
		m_Anime.flip(true);
		setDirection(Left);
	}
	
}

void Crow::animateCharacter(sf::RenderWindow& window,const float& time)
{
	
	m_Anime.tick(time*1.2);
	m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y + m_BoundingRectangle.getGlobalBounds().height-50);
}


void Crow::animate(const float& t, RenderWindow& w)
{
}

void Crow::changeDirection()
{
	if (getDirection() == Right) {
		m_Velocity.x = -11.f;
		setDirection(Left);
	}
	else {
		m_Velocity.x = 11.f;
		setDirection(Right);
	}
}
