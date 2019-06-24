#pragma once
#include "GameObject.h"
#include "Constants.h"
class DynamicObject : public GameObject
{
protected:
	// For resetting the original position after board reset.
	sf::Vector2f m_checkPointPosition;
	sf::Vector2f m_Velocity{ 0,0 };
	sf::Vector2f m_Position{ 0,0 };
	// For now, we will only use Y - Acceleration will affect jump;
	sf::Vector2f m_Acceleration{ 0,0 };
	int m_Direction;
	int m_Speed;
	sf::Vector2f m_Center;
	sf::Clock m_Clock;
	sf::Time m_TimeElapsed;
	
	bool m_Jumping = false;
	bool m_onGround = false;
	bool m_dead = false;
	Time m_delta;


	sf::Vector2f resetPosition;


public:
	bool levelComplete = false;
	DynamicObject();
	virtual ~DynamicObject();

	virtual bool isDead();

	void dead(const bool& flag);
	
	const Time& getDeltaTime(){
		return m_delta;
	}
	void setDeltaTime(const Time& t) {
		m_delta = t;
	}
	virtual void setResetPosition(const sf::Vector2f& position);
	sf::Vector2f& getResetPosition() ;

	// Setters and getters for direction
	virtual void setDirection(const int& direction);
	virtual int getDirection();

	virtual bool isOnGround();
	virtual void onGround(const bool& flag);
	virtual void updateCharacter(const sf::Vector2f& vector, const float&f,const int& direction, bool&shoot) = 0;
	virtual void setAccelerationY(const float& accel);
	
	virtual void setVelocity(const sf::Vector2f& velocity);
	virtual void setVelocityX(const float& v_X);
	virtual void setVelocityY(const float& v_Y);
	


	virtual bool m_moveCharacter();
	//virtual bool increaseVelocity(sf::Vector2f &speed) = 0;
	virtual void animateCharacter(sf::RenderWindow& window,const float& time) = 0;
	virtual sf::Vector2f& getVelocity() ;
	virtual sf::Vector2f& getAcceleration();
	
};

