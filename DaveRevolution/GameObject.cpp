#include "GameObject.h"


bool GameObject::intersects(GameObject& otherObject)
	
{

	if (m_BoundingRectangle.getGlobalBounds().intersects(otherObject.m_BoundingRectangle.getGlobalBounds()))
	{
		return true;
	}
	return false;
}

void GameObject::animate(const float& t, RenderWindow& w)
{
}

RectangleShape& GameObject::getBoundingRectangle()
{
	return m_BoundingRectangle;
}

const Sprite& GameObject::getSprite()
{
	return m_sprite;
}


void GameObject::remove()
{
	m_remove = true;
}

const bool& GameObject::should_remove()
{
	return m_remove;
}

GameObject::~GameObject()
{
}
