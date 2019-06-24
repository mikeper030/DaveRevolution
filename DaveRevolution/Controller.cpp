#pragma once
#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include<memory>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Coin.h"
#include "InfoBar.h"
#include "Elevator.h"
#include "MovementBlocker.h"
#include "Water.h"
#include "Spike.h"
#include "Checkpoint.h"
#include "Enemy.h"
#include "Ammo.h"
#include "Life.h"
#include "Constants.h"
#include "FakeWall.h"
#include "Crow.h"
#include "DoorKey.h"
#include "Door.h"
#include "MainMenu.h"
#include <algorithm>
#include "Constants.h"
#include "Exceptions.h"
#include "StaticObject.h"
#include "ObjectFactory.h"

bool Controller::is_player_sound_on = false;
Controller::Controller()
	:m_screen_height(S_HEIGHT)
	, m_screen_width(S_WIDTH)
	, m_Board(S_WIDTH,S_HEIGHT)
	, shoot(false),is_playing(false)
	,manager(SoundManager::getInstance())
	,text_input(false)
{

}



/////////////////////////////////////////////////////////
//					Object factory
/////////////////////////////////////////////////////////
void Controller::initiateObjects(LevelLoader& level)
{

	sf::Vector2f firstCoords;
	bool firstCheck = false;

	std::string m_objectName;
	std::vector<Object> m_LevelObjects;
	m_LevelObjects = level.GetAllObjects();

	m_DynamicObject1.clear();
	m_StaticObject1.clear();
	// Construct bricks
	for (auto& i : m_LevelObjects)
	{
		// Get Name
		m_objectName = i.name;
		if (m_objectName != "Player" && m_objectName != "Checkpoint"&&m_objectName!="Crow"&&m_objectName!="Enemy"&&m_objectName!="Elevator") {
			//create the objects using factory
			auto a = ObjectFactory::create_static(m_objectName, i.sprite, i.rect);
			//static object
			m_StaticObject1.push_back(std::move(a));
		}
		//dynamic object
		else
		{
			if (m_objectName == "Player" && curentLevel == 1)
			{
				m_player = std::make_unique<Player>(i.sprite, i.rect);
				m_DynamicObject1.push_back(std::move(m_player));
			}
			else {
				if (m_objectName == "Player" && curentLevel > 1)
				{
					m_player = std::make_unique<Player>(i.sprite, i.rect, m_Board.getPlayerLife(), m_Board.getPlayerAmmo(), m_Board.getPlayerScore() + 10, curentLevel);
					m_DynamicObject1.push_back(std::move(m_player));
				}
				else if (m_objectName == "Checkpoint")
				{
					m_StaticObject1.push_back(std::make_unique<Checkpoint>(i.sprite, i.rect, stoi(i.type)));
				}
				else
				{
					std::unique_ptr<DynamicObject> a = ObjectFactory::create_dynamic(m_objectName, i.sprite, i.rect);
					m_DynamicObject1.push_back(std::move(a));
				}

			}



		}
	}
	m_DynamicObject1[0]->setResetPosition(firstCoords);
	// Construct the board;
	m_Board.initiateBoard(m_DynamicObject1, m_StaticObject1);

}

void Controller::loadLevel(const std::string& l_name) {

	if (!lvl.LoadFromFile(l_name))
		throw FileNotFoundException(l_name.c_str());
	initiateObjects(lvl);
}
void Controller::initLevels() {
	m_levels.insert({ 1, "level01.tmx" });
	m_levels.insert({ 2, "level02.tmx" });
	m_levels.insert({ 3, "level03.tmx" });

}
void Controller::startGame()
{

	/////////////////////////////////////////////
	///load the level with loader tmx to sfml////
	/////////////////////////////////////////////
	initLevels();
	Clock delta;
	Time deltaTime;
	TimeUtils t(0);
	
	bool help = false;
	bool score = false;
	/////clock////////////
	Clock clock;
	////////////////////
	
	RenderWindow window(VideoMode(m_screen_width, m_screen_height, sf::Style::Close||sf::Style::Resize), "Dangerous Dave");
	window.setFramerateLimit(60);
	
	InfoBar infoBar(m_screen_height,m_screen_width,0,3,0,1,t);
	MainMenu mainMenu(m_screen_width, m_screen_height);
	sf::View menuView;
	sf::Texture texture;
	texture.loadFromFile("cursor.png");
	
	m_cursor.setTexture(texture);
	m_cursor.scale({ 0.5,0.5 });
	menuView.setViewport(sf::FloatRect(0, 0, 2160.f, 1600.f));
	menuView.setCenter(0,0);
	mainMenu.loadScores();
	/////////////////////
	/////run window/////
	///////////////////
	while (window.isOpen())
	{
        if(direction!=Shoot&&direction!=Crouch)direction = Idle;
		 Velocity = { 0,0 };
		deltaTime = delta.getElapsedTime();
		
		delta.restart().asSeconds();
		float time = 40;
		
		window.setMouseCursorVisible(false);

		if (time > 40);
	
		Event event;
		
		while (window.pollEvent(event))
		{
		  if(is_playing||clicked)
			processEvent(event,mainMenu);
		  m_cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

		}
		if (!is_playing&&mainMenu.newGame(event, window, help, score))
		{   
			//new game button has been clicked
		    //first click
			if (!text_input) {
				clicked = true;
			}else
			   
			{ 
				clicked = false;
				window.clear();
				mainMenu.setLoading(true);

				mainMenu.draw(window, help, score);
				window.display();
				std::string first_level = m_levels[1];
				loadLevel(first_level);
				is_playing = true;
				mainMenu.setLoading(false);
			}
			
			
		}
		
		if (is_playing) {
			manager.playGameBackgroud();
			if (m_Board.isGameFinished())
			{
				window.clear();
				coords4movement = { -5,-5 };
				m_Board.updateView(window, coords4movement, infoBar);
				infoBar.setMessage("Game Completed!");
				infoBar.setShowMessage(true);
				manager.stopSteps();
				manager.stopJump();
				is_playing = false;
				clicked = false;
				mainMenu.saveScore(m_Board.getPlayerScore(), t);
				//m_Board.setGameFinished(false);

			}
			else {

				m_Board.updatePlayer(Velocity, direction, time, shoot, curentLevel);
				m_Board.checkForCollision();
				window.clear();
				if (m_Board.playerDead()) {
					
					infoBar.setMessage("Game over. Restarting...");
					m_Board.updateView(window, coords4movement, infoBar);
					manager.stopSteps();
					manager.stopJump();
					infoBar.setShowMessage(true);
					lvl.Draw(window);//ui changes from here
					infoBar.draw(window);
					infoBar.setShowMessage(false);
					window.display();
					curentLevel = 1;
					loadLevel(m_levels[1]);

				}
				//handle the level finished case

				if (m_Board.isLevelFinished())
				{
					infoBar.setMessage("Success! Loading ...");
					infoBar.setShowMessage(true);
					manager.stopSteps();
					manager.stopJump();
					m_Board.updateView(window, coords4movement, infoBar);
					lvl.Draw(window);//ui changes from here
					infoBar.draw(window);
					infoBar.setShowMessage(false);
					window.display();
					curentLevel += 1;
					loadLevel(m_levels[curentLevel]);
				}
				//update the level timer 
				if (clock.getElapsedTime().asSeconds() > 1)
				{
					t.secondPassed();
					clock.restart();
				}
			
				m_Board.moveDynamics();
				m_Board.checkDynamics();
				m_Board.updateView(window, coords4movement, infoBar);
				lvl.Draw(window);//ui changes from here

				m_Board.updateAnimations(time, window);
				m_Board.updateCamera(time, window);
				infoBar.updateTime();

				infoBar.draw(window);
			}
		}
		else {
			
			manager.stopGameBackgroud();
			mainMenu.draw(window, help, score);
			window.draw(m_cursor);
			manager.playMenu();
		}if (clicked)
			   mainMenu.drawTextInput(window);
		
		window.display();

	}

}
void Controller::processEvent(Event& event,MainMenu&m)
{
	if (event.type == sf::Event::TextEntered)
	{
		text_input = true;
		m.textInput(char(event.text.unicode)) ;
	    
	}
	if (event.type == Event::Closed)
		window.close();
	if (event.type == sf::Event::KeyReleased)
	{
		if (is_player_sound_on&& event.key.code != Keyboard::Up) {
			manager.stopSteps();
			
			is_player_sound_on = false;
		}
		if (event.key.code == Keyboard::Right)
		{
			
			Velocity = { 0,0 };
			coords4movement.x = 0;
			direction = IdleRight;
		}else
			if (event.key.code == Keyboard::Left) 
			{
				
				Velocity = { 0,0 };
				coords4movement.x = 0;
				direction = IdleLeft;
		}
		if (event.key.code == Keyboard::Down)
		{

			Velocity = { 0,0 };
			coords4movement.x = 0;
			direction = Stand;
		}
	}
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Right:
		{
				direction = Right;
				if (!is_player_sound_on)
				{
					manager.playSteps();
					is_player_sound_on = true;
				}
				
				Velocity = { 5,0 };
			coords4movement.x = 5;
		}
		break;
		case sf::Keyboard::Left:
		{
			if (!is_player_sound_on)
			{
				manager.playSteps();
				is_player_sound_on = true;
			}
				direction = 2;
				Velocity = { -5,0 };
			coords4movement.x = -5;
		}
		break;
		case sf::Keyboard::Escape:
			exit(0);
			break;
		case sf::Keyboard::Up:
			manager.playJump();
			direction = Jump;
			Velocity = { 0,0};
 			Velocity.y = -m_screen_height/3 ;
			break;
		case sf::Keyboard::Space:
			
			m_Board.flag();
			shoot = true;
			Velocity = { 0,0 };
			coords4movement.x = 0;
			direction = Shoot;
			break;
		case sf::Keyboard::Down:

			Velocity = { 0,0 };
			coords4movement.x = 0;
			direction = Crouch;
			break;

		}	
	}
}
