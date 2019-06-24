#include "FakeWall.h"
#include <iostream>
#include "Exceptions.h"

FakeWall::FakeWall(Sprite& sprite, sf::FloatRect& rect)

{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });

	if (!animeTexture.loadFromFile("PlatformGameTiles.png"))
		throw(FileNotFoundException("Platfor game tiles png"));



	sf::Vector2f s(2, 2);
	if (!m_Anime.loadFromXML("FakeTile.xml", animeTexture, s))
		throw(FileNotFoundException("FAKETILE .xml"));


	m_Anime.set("FakeTile");
}

void FakeWall::animate(const float& time, RenderWindow& window)
{
	m_Anime.tick(time);
	m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y + m_BoundingRectangle.getGlobalBounds().height);

}


