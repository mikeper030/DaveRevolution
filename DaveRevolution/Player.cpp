#include "Player.h"
#include <iostream>
#include "Exceptions.h"

void Player::goToCheckPoint()
{
	if (!m_checkpoint) {
		m_checkpoint = true;
		deathAnim();
		lowerLife();
		m_ammo += 3;
		
	}
	
}
void Player::init(const sf::Sprite&sprite,const FloatRect&rect)
{
	m_BoundingRectangle.setPosition(sprite.getPosition());
	m_BoundingRectangle.setSize(sf::Vector2f{ (float)rect.width, (float)rect.height * 2 });
	

	// Set acceleration and velocity to zero vector
	m_Acceleration = sf::Vector2f{ 0,0 };
	m_Velocity = sf::Vector2f{ 0,0 };

	// Initialize animatino
	if (!animeTexture.loadFromFile("policeman.png"))
		throw(FileNotFoundException("POLICEMAN PNG"));

	sf::Vector2f s(2, 2);
	if (!m_Anime.loadFromXML("policeman.xml", animeTexture, s))
		throw(FileNotFoundException("bullet explosion png"));
	//m_Anime.animList["jump"].loop = 0;

	m_Anime.set("idle");
}
// Constructor - construct character based on object rectangle from level and sprite coords
Player::Player(sf::Sprite& sprite, sf::FloatRect& rect)
	:coins_collected(0), m_life(3), m_ammo(0),restart_level(false),m_checkpoint(false)
	,m_rect(rect),s(sprite),level_finished(false),m_game_finished(false),m_level_no(1)
{
	
	init(sprite,rect);
}
Player::Player(sf::Sprite& sprite, sf::FloatRect& rect, const int& life, const int& ammo, const int& score,const int&level)
	:coins_collected(score), m_life(life), m_ammo(ammo), restart_level(false), m_checkpoint(false), m_rect(rect), s(sprite)
	,m_level_no(level),level_finished(false),m_game_finished(false)
{
	init(sprite,rect);
}
void Player::deathAnim() {
	m_Anime.set("dead");
}
void Player::goalReach(bool flag)
{
	levelComplete = flag;
}

void Player::animateCharacter(sf::RenderWindow& window,const float& time)
{
	/*m_BoundingRectangle.setFillColor(sf::Color::White);
	window.draw(m_BoundingRectangle);*/
	if (m_Anime.currentAnim == "dead") {
		m_Anime.tick(time*0.65);
	}else
	m_Anime.tick(time);
	m_Anime.draw(window,m_BoundingRectangle.getPosition().x,m_BoundingRectangle.getPosition().y+m_BoundingRectangle.getSize().y);
	
}
void Player::lowerLife() {
	m_life--;
	if (m_life <= 0) {
		m_dead = true;
	}
}
void Player::lowerAmmo()
{
	m_ammo--;
}
void Player::Shoot(bool&f) {
	
		if (m_Anime.currentAnim != "shoot") {
			m_Anime.set("shoot");
		}
		//shoot animation already active now check when finished
		else {
			int i = m_Anime.animList["shoot"].currentFrame;
			if (i >= m_Anime.animList["shoot"].frames.size() - 1) {
				m_Anime.animList["shoot"].currentFrame = 0;
				f = false;
			}
		}
	}
const bool Player::shootAnimReady() {
	return m_Anime.currentAnim == "shoot" &&
		(m_Anime.animList["shoot"].currentFrame >= m_Anime.animList["shoot"].frames.size()- 2);
}
void Player::updateCharacter(const sf::Vector2f& velocity, const float&f,const int& direction,bool&is_s)
{

	int i = m_Anime.animList["dead"].currentFrame;
	
	
	//if the player is dying do the death animation
	if (m_Anime.currentAnim=="dead"&&i<m_Anime.animList["dead"].getFrames()-1){
		setVelocityX(0);
		return;
	//the death animation is finished
	}
	else if (m_Anime.currentAnim == "dead" && i >= m_Anime.animList["dead"].getFrames() -1)
	{
		//reset the death animation
		m_Anime.animList["dead"].currentFrame = 0;
		m_Anime.set("idle");
		return;
	}
	
	//animation finished now restart from checkpoint
	if (m_checkpoint) {
		if (isDead()) {
			restart_level = true;
			
			return;
		}
		flag = false;
		m_checkpoint = false;
		m_BoundingRectangle.setPosition(getCheckpointPosition());
		m_Anime.set("idle");
		return;
	} 
	
	if (direction == Crouch)
	{
		m_BoundingRectangle.setSize(sf::Vector2f{ (float)m_rect.width, (float)m_rect.height  });
		m_Anime.set("crouch");
		if (m_Velocity.x >= 0)
			m_Anime.flip(false);
		else
			m_Anime.flip(true);
	}
	if(direction==Stand)
	{
		
		m_BoundingRectangle.setSize(sf::Vector2f{ (float)m_rect.width, (float)m_rect.height * 2 });
		
	}
	// stop walking Right	
	if (direction == IdleRight)
	{
		setVelocityX(0);
		if (!is_s){
			m_Anime.set("idle");
		}
		else
		{
			Shoot(is_s);
		}
		
		m_Anime.flip(false);

	}
	//stop walking left
	if (direction ==IdleLeft)
	{
		setVelocityX(0);
		if (!is_s) {
			m_Anime.set("idle");
		
		}
		else
		{
			Shoot(is_s);
		}
		
		m_Anime.flip(true);
	}

	// This will update the movement when he is on ground
	if (isOnGround())
	{
		
		if (getVelocity().x == 0)
		{
			if (getDirection() == Left)
			{
				if (!is_s) {
					m_Anime.set("idle");
					
				}
				else
				{
					Shoot(is_s);
				}
				m_Anime.flip(true);
			
			}
			else
			{
				if (!is_s) {
					if (direction != Crouch) {
						m_Anime.set("idle");
						
					}
					}
				else
				{
					Shoot(is_s);
				}
			}
		}
		if (getVelocity().x > 0)
		{
			
		}
		if (getVelocity().x < 0)
		{
			
	
		}

	}
	// This is for when he is not on the ground
	/////////////////////////////////////////////////////
	// New direction is right and old direction is left? Flip is FALSE
	if (direction == Right)
	{
		if (!is_s) {
			m_Anime.set("walk");
		}
		else {
			Shoot(is_s);
		}
				
		setDirection(Right);
	
		setVelocityX(0.2f * f);
		
	}
	// New direction is left and old direction is right? Flip is true
	else if (direction == Left)
	{
		if (!is_s) {
			m_Anime.set("walk");
		}
		else  {
			//handle shoot animation
			Shoot(is_s);
		}
		m_Anime.flip(true);
		setDirection(Left);
		setVelocityX(-0.2f * f);
	
	}


	// Jump
	if (direction == Jump)
	{
		
		jumpCounter++;
		
		if (!is_s) {
			m_Anime.set("jump");
		}
		else {
			Shoot(is_s);
		}
		if (getDirection() == Left)
			m_Anime.flip(true);
		else(m_Anime.flip(false));
		
		if (jumpCounter <= 2)
		{
			
			if (jumpCounter == 1)
			{
				setAccelerationY(velocity.y);
				
			}
			else//jumpcounter==2
			{
			
				setAccelerationY(velocity.y +30);
				onGround(false);
				jumping = true;
			}
		}

	}
	//gravity normally pulls down
	if (!isOnGround() || jumping) {
     setVelocityY(0.4f *f);
	 jumping = false;
	}

	
		if(getAcceleration().y<0){
		

		onGround(false);
		setVelocityY(getAcceleration().y/25 );
		setAccelerationY(getAcceleration().y + 0.5f * f);
	}
	
	
}

const bool& Player::is_jump()
{
	return jumping;
}


const sf::Vector2f& Player::getCheckpointPosition()
{
	return resetPosition;
}

void Player::setCheckpointPosition(const sf::Vector2f& coords)
{
	resetPosition = coords;
}


const int& Player::getCoins() {
	return coins_collected;
}
void Player::animate(const float& t, RenderWindow& w)
{
	//leave empty -> the animation is already done
}

