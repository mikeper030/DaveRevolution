#include "Door.h"
#include "Exceptions.h"
Door::Door(sf::Sprite& sprite, sf::FloatRect& rect)
	:Consumable(sprite, rect)
{
		m_BoundingRectangle.setPosition({sprite.getPosition().x, sprite.getPosition().y-30});
		m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height });
		m_sprite.setPosition({ sprite.getPosition().x, sprite.getPosition().y - 30 });
		if(!m_texture.loadFromFile("door.png"))
			throw(FileNotFoundException("door png"));
		m_sprite.setTexture(m_texture);
		m_sprite.scale(0.09, 0.09);
		
	}


void Door::animate(const float& t, RenderWindow& w)
{
	w.draw(m_sprite);
}