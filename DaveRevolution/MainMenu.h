#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TimeUtils.h"
class MainMenu
{
public:
	MainMenu(const int&,const int&);
	void textInput(const char& s);
	void saveScore(const int& score,  TimeUtils& t);
	void textInput(const std::string& s);
	void loadScores();
	void setLoading(const bool& b);
	bool newGame(sf::Event& event, sf::RenderWindow& window, bool& help, bool& score);
	void drawTextInput(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window, bool help, bool score);
	~MainMenu();


private:
	bool m_loading;
	sf::RectangleShape newGame_button, exitGame_button, help_button,
		rectInter, helpIntro, back_to_menu_button, score_table_button, scoreIntro, text_input_back;
	sf::Sprite m_sprite, end, m_help, m_score,help_image;
	sf::Texture m_texture_menu, m_texture_help, m_texture_score;
	std::string table_str;
	sf::Font font;
	sf::Text menu_newGame;
	sf::Text menu_exitGame;
	sf::Text text_help;
	sf::Text text_back;
	sf::Text text_score_table;
	sf::Text loading;
	sf::Text table;
	sf::Text table_title;
	sf::Text enter_name;
	sf::Text input;
	std::string input_str;
	int m_screen_width, m_screen_height;
};
