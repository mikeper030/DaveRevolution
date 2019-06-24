#pragma once

#include <memory>
#include <functional>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Camera.h"
#include <exception>
#include "InfoBar.h"
#include "SoundManager.h"
//float m_Gravity = 0.1;
using std::vector;
using std::unique_ptr;
class Board
{
private:
	bool m_flag = false;
	SoundManager& manager;
	vector<unique_ptr<DynamicObject>> m_DynamicObject;
	vector < unique_ptr<StaticObject>> m_StaticObject;
	Camera my_Camera;
	sf::Sprite spaceBackground;


public:
	Board(const int&w, const int&h);
	void reset();
	void moveDynamics();
	void updateAnimations(const float& t,RenderWindow&w);
	void flag();
	const int& getPlayerLife();
	const bool& isGameFinished();
	const int& getPlayerAmmo();
	const int& getPlayerScore();
	void updatePlayer(const sf::Vector2f& velocity,const int& direction, const float& f, bool& b, const int& level);

	void checkForCollision();
	void playerShoot();
	bool flipped = false;
	void checkDynamics();
	
	void updateView(sf::RenderWindow& window,const sf::Vector2f& velocity, InfoBar& infb);
	float getCamera();
	void setGameFinished(const bool& b);
	const bool& isLevelFinished();
	const bool playerDead();
	void updateCamera(const float& time, sf::RenderWindow& window);
	//load the board from the levelloader manager
	void initiateBoard(vector<std::unique_ptr<DynamicObject>>& Dynamicobjects,
		vector<std::unique_ptr<StaticObject>>& Staticobjects);



	

};

