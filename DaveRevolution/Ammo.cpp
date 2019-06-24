#include "Ammo.h"
#include <iostream>
#include "Exceptions.h"
Ammo::Ammo(sf::Sprite& sprite, sf::FloatRect& rect)
	:Consumable(sprite,rect),is_up(true)
{
	
	if (!animeTexture.loadFromFile("ammo_life.png")) 
		throw FileNotFoundException("ammo life png");

	sf::Vector2f s(0.5, 0.5);
	if (!m_Anime.loadFromXML("ammo_life.xml", animeTexture, s)) 
		throw(FileNotFoundException("ammo_life.xml"));
	//m_Anime.animList["jump"].loop = 0;

	m_Anime.set("ammo");
}


void Ammo::animate(const float& t, RenderWindow& window)
{
	
	m_Anime.tick(t * 2);
	if (m_anim_counter >=0&&m_anim_counter<20&&is_up)
	{
		m_anim_counter++;
		m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y-m_anim_counter);
		
	}
	else if(m_anim_counter>=20||!is_up){
		is_up = false;
	
		m_anim_counter--;
		if (m_anim_counter == 0)
		{
			is_up = true;
		}
		m_Anime.draw(window, m_BoundingRectangle.getPosition().x, m_BoundingRectangle.getPosition().y - m_anim_counter);
	
	}
	
}
