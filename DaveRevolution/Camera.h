#pragma once

#include "Animation.h"
class Camera
{
private:
	sf::View view;
public:
	Camera(const int&,const int&);
	int w; int h;
	void MoveView(sf::Vector2f& coords);
	void setPosition(const sf::Vector2f& coords);
	void SetView(sf::RenderWindow& window);
	const sf::Vector2f& GetCenter() const;
};

