#include "Bullet.h"
#include "Exceptions.h"


Bullet::Bullet(const sf::RectangleShape& playerRect,const int& direction)
	:player_rect(playerRect),m_direction(direction),m_consume_anim(false),manager(SoundManager::getInstance())
 {
	if (direction == 1)
		m_BoundingRectangle.setPosition({ playerRect.getPosition().x + playerRect.getSize().x + 2, playerRect.getPosition().y+100 });
	if (direction == 2)
		m_BoundingRectangle.setPosition({ playerRect.getPosition().x - playerRect.getSize().x - 20, playerRect.getPosition().y+100 });

	m_BoundingRectangle.setSize(sf::Vector2f{ (float)playerRect.getSize().x / 4,(float)playerRect.getSize().y / 7});
	if (!animeTexture.loadFromFile("projectile.png"))
		throw(FileNotFoundException("projectile pn"));
	sf::Vector2f s(2, 2);
	
	if (!m_Anime.loadFromXML("bullet.xml", animeTexture, s)) 
		throw(FileNotFoundException("bullet.xml"));
	if (!m_explosion.loadFromXML("bullet_explosion.xml", animeTexture, s))
		throw(FileNotFoundException("bullet_explosion.xml"));

	m_Anime.set("bullet");
	m_explosion.set("explosion");

	if (direction == 1)
		m_Velocity.x = 13.0f;
	if (direction == 2)
		m_Velocity.x = -13.0f;
	

}

void Bullet::updateCharacter(const sf::Vector2f& vector, const float&f,const int& direction, bool&)
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

void Bullet::animateCharacter(sf::RenderWindow& window,const float& time)
{
	
	m_Anime.tick(time);
	m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y+30);
	if (m_explosion.animList["explosion"].currentFrame <= m_explosion.animList["explosion"].frames.size() - 1) {
		
		m_explosion.tick(time);
		if (m_direction == 1)
			m_explosion.draw(window, player_rect.getPosition().x + 90, player_rect.getPosition().y + 145);
		else
			m_explosion.draw(window, player_rect.getPosition().x - 90, player_rect.getPosition().y + 145);
	}


}

void Bullet::consumeAnim(const bool& f)
{
	m_consume_anim = f;
}

const bool& Bullet::consumed()
{
	return m_consume_anim;
}

