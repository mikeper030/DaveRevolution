#pragma once
#include <iostream>
#include "SoundManager.h"
#include "DynamicObject.h"
class Bullet : public DynamicObject
{

private:
	AnimationManager m_explosion;
	RectangleShape player_rect;
	int m_direction;
	SoundManager& manager;
	bool m_consume_anim;
public:
	Bullet(const sf::RectangleShape& playerRect,const  int& direction);

	void updateCharacter(const sf::Vector2f& vector,const float&f,const int& direction, bool&) override;



	void animateCharacter(sf::RenderWindow& window,const float& time);


	void consumeAnim(const bool& f);

	const bool& consumed();


};

