#pragma once
#include "Board.h"
#include "Wall.h"
#include "Player.h"
#include "LevelLoader.h"
#include "SoundManager.h"
#include "MainMenu.h"
using namespace sf;
//class LevelLoader;
class Controller

{
	
private:
	vector<unique_ptr<DynamicObject>> m_DynamicObject1;
	vector<unique_ptr<StaticObject>> m_StaticObject1;
	unique_ptr<Player> m_player;
public:
	Controller();
	void loadLevel(const std::string& l_name);
	void initLevels();
	void startGame();
	void processEvent(Event& event, MainMenu& m);
	static bool is_player_sound_on;
	
	void initiateObjects(LevelLoader& level);
	
	bool playingGame = true;

private:
	bool text_input;
	SoundManager& manager;
	std::map<int, std::string> m_levels;
	int curentLevel = 1;
	int direction = Idle;
	Vector2f Velocity;
	Vector2f coords4movement{ 0,0 };
	LevelLoader lvl;
	sf::Sprite m_cursor;
	// Death, Game Over, Winner Winner
	sf::Texture gameTextures[4];
	Texture spaceBackground;
	sf::RenderWindow window;
	bool shoot;
	Board m_Board;
	bool is_playing = false;
	bool clicked = false;
	int m_screen_height, m_screen_width;

};

