#include "Elevator.h"

#include "Exceptions.h"
Elevator::Elevator(sf::Sprite& sprite, sf::FloatRect& rect)
{
	m_BoundingRectangle.setPosition(sprite.getPosition().x,sprite.getPosition().y);
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });

	if (!animeTexture.loadFromFile("canvas-Recovered.png"))
		throw(FileNotFoundException("canvas recoverd png"));

	sf::Vector2f s(1, 1);
	if (!m_Anime.loadFromXML("elevator_anim.xml", animeTexture, s))
		throw(FileNotFoundException("elevator anim.xml"));
	m_Anime.set("elevator");
	m_Velocity.x = -3.f;
	setDirection(Left);

}
void Elevator::changeDirection()
{
	if (getDirection() == Right) {
		m_Velocity.x = -3.f;
		setDirection(Left);
	}
	else {
		m_Velocity.x = 3.f;
		setDirection(Right);
	}
}
void Elevator::updateCharacter(const sf::Vector2f& vector, const float& f,const int& direction,bool&)
{
	if (getVelocity().x > 0 || getVelocity().x > 0)
		m_Anime.set("elevator");
}

void Elevator::animateCharacter(sf::RenderWindow & window,const float& time)
{
	m_Anime.tick(time);
	                                                 //pixel dependent
	m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y+25);

}


void Elevator::animate(const float& t, RenderWindow & w)
{
}
