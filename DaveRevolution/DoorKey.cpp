#include "DoorKey.h"
#include "Exceptions.h"

DoorKey::DoorKey(Sprite& sprite, sf::FloatRect& rect)
	:Consumable(sprite, rect), is_up(true)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });

	if (!animeTexture.loadFromFile("key.png"))
		throw(FileNotFoundException("key png"));
	sf::Vector2f s(1, 1);
	if (!m_Anime.loadFromXML("key_anim.xml", animeTexture, s))
		throw(FileNotFoundException("key anim.xml"));


	m_Anime.set("key");
}

void DoorKey::animate(const float& time, RenderWindow& window)
{
	m_Anime.tick(time * 2);
	if (m_anim_counter >= 0 && m_anim_counter < 20 && is_up)
	{
		m_anim_counter++;
		m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y - m_anim_counter);

	}
	else if (m_anim_counter >= 20 || !is_up) {
		is_up = false;

		m_anim_counter--;
		if (m_anim_counter == 0)
		{
			is_up = true;
		}
		m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y - m_anim_counter);

	}
}