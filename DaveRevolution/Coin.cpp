#include "Coin.h"
#include <iostream>
#include "Exceptions.h"

Coin::Coin(sf::Sprite& sprite, sf::FloatRect& rect)
	:Consumable(sprite,rect), manager(SoundManager::getInstance())
{
	if (!animeTexture.loadFromFile("coins_sheet.png"))
		throw(FileNotFoundException("coins sheet png"));
	sf::Vector2f s(0.5, 0.5);
	if (!m_Anime.loadFromXML("money.xml", animeTexture, s))
		throw(FileNotFoundException("money xml"));
	m_Anime.set("money");
}


//override
void Coin::animate(const float& t,RenderWindow&window)
{
	
	//routine animation
	m_Anime.tick(t*2);
	if (!m_consume_anim)
	m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y+60);
	else
	{
	
		//strat the consume animation
		if (m_anim_counter < max) {
			if (m_anim_counter == 0)
			{
				manager.stopGift();
				manager.playGift();
			}
			//move the coin upper based on counter progress                                       //pixel density dependent
			m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y-m_anim_counter*7);
			m_anim_counter++;
		}
		else 
			remove();
	}
}

