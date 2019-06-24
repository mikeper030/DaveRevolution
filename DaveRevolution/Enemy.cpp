#include "Enemy.h"
#include "Exceptions.h"

Enemy::Enemy(sf::Sprite& sprite, sf::FloatRect& rect)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height*2 });

	if (!animeTexture.loadFromFile("player_large.png")) 
		throw(FileNotFoundException("player large png"));

	sf::Vector2f s(3, 3);
	if (!m_Anime.loadFromXML("player_anim.xml", animeTexture, s))
		throw(FileNotFoundException("player anim xml"));

	m_Anime.set("walk_left");
	m_Velocity.x = -3.f;
	setDirection(Left);
}
void Enemy::changeDirection()
{
	if (getDirection() == Left) {
		setDirection(Right);
		m_Velocity.x = 3.f;
		m_Anime.set("walk_right");
	}
	else {
		setDirection(Left);
		m_Velocity.x = -3.f;
		m_Anime.set("walk_left");
	}
}
void Enemy::updateCharacter(const sf::Vector2f& velocity, const float& f,const int& direction,bool& shoot)
{
}

void Enemy::animateCharacter(sf::RenderWindow& window,const  float& time)
{
	m_Anime.tick(time/2);
	m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y + m_BoundingRectangle.getGlobalBounds().height-20);
}


void Enemy::animate(const float& t, RenderWindow& w)
{
}
