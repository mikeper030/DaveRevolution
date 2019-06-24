#include "Camera.h"
#include <iostream>
///////////////////////////////////////////
// Constructor - sets the x and y of view//
///////////////////////////////////////////
Camera::Camera(const int&w,const int&h) : 
	view(FloatRect(0, 0, w, h)),w(w),h(h)
{
}

void Camera::MoveView(sf::Vector2f& coords)
{
	view.move(coords);
}
/////////////////////////////////////////////////////////
// Set position - currently, player.x and view center.y//
/////////////////////////////////////////////////////////
void Camera::setPosition(const sf::Vector2f& coords)
{
	//left edge of level
		if (coords.x < w * 0.75 / 2)
		{
			view.setCenter(w / 2, view.getCenter().y);
		}
		//right edge of level

		else if (coords.x > 5970)
		{
			view.setCenter(6230, view.getCenter().y);
		}
		//progress the view normally
		else
		{
			view.setCenter(coords.x + w * 0.13, view.getCenter().y);

		}
	
}


// Getters & Setters
void Camera::SetView(sf::RenderWindow& window)
{
	window.setView(view);
}
const sf::Vector2f& Camera::GetCenter() const
{
	return view.getCenter();
}
