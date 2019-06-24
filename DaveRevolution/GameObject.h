#pragma once
#include "SFML\Graphics.hpp"
#include  "Animation.h"
using namespace sf;
class GameObject
{
private:
	bool m_remove = false;
protected:
	Texture animeTexture;
	AnimationManager m_Anime;
	Color m_color;
	Sprite m_sprite;
	Texture m_texture;
	// Very important - bounds the object and is used for collision
	RectangleShape m_BoundingRectangle;




	
public:
	virtual ~GameObject();
	void remove();
	const bool& should_remove();
	virtual bool intersects(GameObject& otherObject);
	virtual void animate(const float& t,RenderWindow&w);
	RectangleShape& getBoundingRectangle();
	const Sprite& getSprite();

};

