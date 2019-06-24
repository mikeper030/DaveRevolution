#include "DynamicObject.h"

bool DynamicObject::isDead()
{
	return m_dead;
}

void DynamicObject::dead(const bool& flag)
{
	m_dead = flag;
}

void DynamicObject::setResetPosition(const sf::Vector2f& position)
{
	resetPosition = position;
}

sf::Vector2f& DynamicObject::getResetPosition() 
{
	return resetPosition;
}
DynamicObject::DynamicObject()
	:m_Direction(0),m_Speed(0)
{
}


DynamicObject::~DynamicObject()
{
}

void DynamicObject::updateCharacter(const sf::Vector2f& vector, const float&f,const int& direction, bool&)
{
	
}
// Set the Y acceleration ( for jumps )
void DynamicObject::setAccelerationY(const float& accel)
{
	m_Acceleration.y = accel;
}
// Get the current (X Y) velocity
sf::Vector2f& DynamicObject::getVelocity()
{
	return m_Velocity;
}
// Get the current acceleration
sf::Vector2f& DynamicObject::getAcceleration()
{
	return m_Acceleration;
}
// Set velocity of x
void DynamicObject::setVelocityX(const float&  v_X)
{
	m_Velocity.x = v_X;
}
// Set velocity of y
void DynamicObject::setVelocityY(const float&  v_Y)
{
	m_Velocity.y = v_Y;
}

// Set the velocity
void DynamicObject::setVelocity(const sf::Vector2f&  velocity)
{
	m_Velocity = velocity;
}
// Get the current direction ( state )
int DynamicObject::getDirection()
{
	return m_Direction;
}
// Check wether we are on ground
bool DynamicObject::isOnGround()
{
	return m_onGround;
}
// Set the on ground falg to true
void DynamicObject::onGround(const bool& flag)
{
	m_onGround = flag;
}
// Move the character according to the velocity
bool DynamicObject::m_moveCharacter()
{
	m_BoundingRectangle.move(m_Velocity.x, m_Velocity.y);
	return false;
}


// Set the direction ( state )
void DynamicObject::setDirection(const int& direction)
{
	m_Direction = direction;
}

