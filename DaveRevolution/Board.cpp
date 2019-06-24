#include "Board.h"
#include <iostream>
#include "Player.h"
#include <algorithm>
#include "CollisionHandling.h"
#include "Exceptions.h"
#include "Bullet.h"
#include "MainMenu.h"


// Randomly select if they collide or not
// In actual implementation it will check for intersection
bool collide(GameObject& objectA, GameObject& objectB)
{

	return (objectA.intersects(objectB));
	
}
/////////////////////////////////////////////////////////
//					Constructor
/////////////////////////////////////////////////////////
Board::Board(const int&w,const int&h)
	:my_Camera(w,h), manager(SoundManager::getInstance())
{
}



void Board::reset()
{
	m_DynamicObject.clear();
	m_StaticObject.clear();

}


void Board::moveDynamics()
{
	for (size_t i = 0; i < m_DynamicObject.size(); i++)
	{
		m_DynamicObject[i]->m_moveCharacter();
	}
}

void Board::updateAnimations(const float& t,RenderWindow&w)
{
	for (auto& a : m_StaticObject)
	{
		if(a!=nullptr)a->animate(t,w);
	}
}

void Board::flag() {
	m_flag = false;
}

const int& Board::getPlayerLife()
{
	Player* p = dynamic_cast<Player*>(m_DynamicObject[0].get());
	if(!p)
		throw(BadCastException("at getPlayerLife()"));
	return p->getLife();
}

/////////////////////////////////////////////////////////
// Update the heroes velocity, direction, and animation
/////////////////////////////////////////////////////////

const int& Board::getPlayerAmmo()
{
	Player* p = dynamic_cast<Player*>(m_DynamicObject[0].get());
	if(!p)throw(BadCastException("getPlayerAmmo()"));
	return p->getAmmo();
}

const int& Board::getPlayerScore()
{
	Player* p = dynamic_cast<Player*>(m_DynamicObject[0].get());
	if (!p)	throw(BadCastException("at getPlayerScore()"));
	return p->getCoins();
}

void Board::updatePlayer(const sf::Vector2f& velocity,const int& direction, const float&f,bool&b,const int&level)
{
	//handle the player shooting
	Player* p = dynamic_cast<Player*>(m_DynamicObject[0].get());
	if (p) {
		if (p->shootAnimReady() && !m_flag&&p->getAmmo()>0) {
			p->lowerAmmo();
			p->setLevelNo(level);
			manager.stopExplosion();
			manager.playExplosion();
			playerShoot();
			m_flag = true;
		}
		
	}else 	
		throw(BadCastException("at updatePlayer()"));
	for (size_t i = 0; i < m_DynamicObject.size(); i++)
	{
		m_DynamicObject[i]->updateCharacter(velocity, f, direction,b);
	}

}
/////////////////////////////////////////////////////////
//					Check for collision
/////////////////////////////////////////////////////////
void Board::checkForCollision()
{
	// player is not on ground by default unless a collision tells us otherwise.
	m_DynamicObject[0]->onGround(false);
	
	std::for_each(m_DynamicObject.begin(), m_DynamicObject.end(), [&](auto & a) {
		std::for_each(m_StaticObject.begin(), m_StaticObject.end(), [&a](auto & b) {

			if (collide(*a, *b))
			{
				processCollision(*a, *b);
			}
			});
		});
	std::for_each(m_DynamicObject.begin(), m_DynamicObject.end(), [&](auto & a) {
		std::for_each(m_DynamicObject.begin(), m_DynamicObject.end(), [&](auto & b) {

			if (a == b)
				return;
			if (collide(*a, *b))
			{
				processCollision(*a, *b);
			}
			});
		});

}

void Board::playerShoot()
{
	m_DynamicObject.push_back(std::make_unique<Bullet>(m_DynamicObject[0]->getBoundingRectangle(), m_DynamicObject[0]->getDirection()));
}




void Board::checkDynamics()
{

	for (size_t i = 0; i < m_DynamicObject.size(); i++)
	{
		if (m_DynamicObject[i]->isDead())
		{
			m_DynamicObject.erase(m_DynamicObject.begin() + i);
		}
	}
	//m_deadCharacters.push_back(std::move(m_DynamicObject[0]));
}

/////////////////////////////////////////////////////////
//					Update the camera
/////////////////////////////////////////////////////////
void Board::updateView(sf::RenderWindow & window,const sf::Vector2f & velocity,InfoBar& infb)
{
	// Check if hes not deadif (!m_DynamicObject[0]->amIdead())


	if (velocity.x == -5 && velocity.y == -5)
	{
		my_Camera.setPosition({ -5,-5 });
	}
	else {
		my_Camera.setPosition(m_DynamicObject[0]->getBoundingRectangle().getPosition());
		infb.moveDisplay(my_Camera.GetCenter());
		
		Player* p = dynamic_cast<Player*>(m_DynamicObject[0].get());
		if (p)
		{
			infb.setCoins(p->getCoins());
			infb.setLife(p->getLife());
			infb.setShots(p->getAmmo());
			infb.setLevelNO(p->getLevelNo());
		}
		else
		{
			throw(BadCastException("at updateView()"));
		}
	}


}
float Board::getCamera() {
	return my_Camera.GetCenter().x;
}
const bool& Board::isGameFinished()
{
	Player* p = dynamic_cast<Player*>(m_DynamicObject[0].get());
	if(!p)	throw(BadCastException("at isGameFinihed()"));
	
	return p->isGameFinished();
}
void Board::setGameFinished(const bool& b)
{
	Player* p = dynamic_cast<Player*>(m_DynamicObject[0].get());
	if (!p) throw(BadCastException("at setGameFinihed()"));
	p->setGameFinished(b);
}
const bool& Board::isLevelFinished()
{
	Player* p = dynamic_cast<Player*>(m_DynamicObject[0].get());
	if (!p)	throw(BadCastException("at isLevelFinihed()"));
	return p->isLevelFinsihed();
}
const bool Board::playerDead() {
	return m_DynamicObject[0]->isDead();
}
/////////////////////////////////////////////////////////
//					Set camera, draw animation
/////////////////////////////////////////////////////////
void Board::updateCamera(const float& time, sf::RenderWindow & window)
{

	my_Camera.SetView(window);

	for (size_t i = 0; i < m_DynamicObject.size(); i++)
	{
		
		m_DynamicObject[i]->animateCharacter(window, time);
	}
	for (size_t i = 0; i < m_StaticObject.size(); i++)
	{
		if (m_StaticObject[i]->should_remove()) {
			m_StaticObject.erase(m_StaticObject.begin()+i);
		}
	}
	for (size_t i = 0; i < m_DynamicObject.size(); i++)
	{
		if (m_DynamicObject[i]->should_remove()) {
			m_DynamicObject.erase(m_DynamicObject.begin() + i);
		}
	}

}
///////////////////////////////////////////////////////////
//					Initialize objects
/////////////////////////////////////////////////////////
void Board::initiateBoard(vector<std::unique_ptr<DynamicObject>> & Dynamicobjects, 
	vector<std::unique_ptr<StaticObject>> & Staticobjects)
{

	//move using move semantics
	m_DynamicObject = std::move(Dynamicobjects);
	m_StaticObject = std::move(Staticobjects);
}

