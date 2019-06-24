#include "MainMenu.h"
#include "TimeUtils.h"
#include <sstream>
#include <fstream>
#include "Exceptions.h"
MainMenu::MainMenu(const int& width,const int& height)
	:m_screen_height(height), m_screen_width(width), m_loading(false)
{
	if(!font.loadFromFile("font.ttf"))
		throw(FileNotFoundException("FONT TTF"));

	loading.setFont(font);
	loading.setFillColor(sf::Color::Blue);
	loading.setCharacterSize(m_screen_width / 20);
	loading.setString("Loading... Please wait");
	loading.setPosition(m_screen_width / 2 - loading.getGlobalBounds().width / 2, m_screen_height / 2 - loading.getGlobalBounds().height / 2);
	if(!m_texture_menu.loadFromFile("Dangerous-Dave.png"))
		throw(FileNotFoundException("game wav"));
	m_texture_menu.setSmooth(true);
	rectInter.setSize(sf::Vector2f(m_screen_width, m_screen_height));
	m_sprite.setTexture(m_texture_menu);

	m_sprite.setPosition(0, 0);
	m_sprite.scale(sf::Vector2f(1.9, 2.5));


	helpIntro.setSize(sf::Vector2f(m_screen_width, m_screen_height));
	helpIntro.setPosition(0, 0);
	helpIntro.setFillColor(sf::Color::Green);


	scoreIntro.setSize(sf::Vector2f(m_screen_width, m_screen_height));
	scoreIntro.setPosition(0, 0);
	scoreIntro.setFillColor(sf::Color::Yellow);
	
	//the text input field
	text_input_back.setFillColor(sf::Color::Black);
	text_input_back.setSize(sf::Vector2f( m_screen_height / 3,m_screen_height / 3 ));
	text_input_back.setPosition(m_screen_width / 2 - text_input_back.getGlobalBounds().width / 2, m_screen_height / 2 - text_input_back.getGlobalBounds().height / 2);
	enter_name.setFont(font);
	enter_name.setCharacterSize(m_screen_height / 40);
	enter_name.setFillColor(sf::Color::White);
	enter_name.setString("Enter your name: ");
	enter_name.setPosition(m_screen_width * 0.5 - enter_name.getGlobalBounds().width / 2, m_screen_height * 0.45 - enter_name.getGlobalBounds().height);

	input.setFont(font);
	input.setCharacterSize(m_screen_height / 30);
	input.setPosition(m_screen_width * 0.5 - input.getGlobalBounds().width / 2, m_screen_height * 0.5  +input.getGlobalBounds().height);
	input.setFillColor(sf::Color::White);
	
	
	//score button
	score_table_button.setSize(sf::Vector2f(m_screen_width / 6, m_screen_height / 12));
	score_table_button.setFillColor(sf::Color::Color(244, 67, 54));
	score_table_button.setPosition(m_screen_width / 10, m_screen_height * 0.19);

	//help button
	help_button.setSize(sf::Vector2f(m_screen_width / 6, m_screen_height / 12));
	help_button.setFillColor(sf::Color::Color(244, 67, 54));
	help_button.setPosition(m_screen_width / 10, m_screen_height * 0.29);




	//back button
	back_to_menu_button.setSize(sf::Vector2f(m_screen_width / 6, m_screen_height / 12));
	back_to_menu_button.setFillColor(sf::Color::Color(244, 67, 54));
	back_to_menu_button.setPosition(0, 0);


	//new game button and exit game button
	newGame_button.setSize(sf::Vector2f(m_screen_width / 6, m_screen_height / 12));
	exitGame_button.setSize(sf::Vector2f(m_screen_width / 6, m_screen_height / 12));
	newGame_button.setFillColor(sf::Color::Color(244, 67, 54));
	newGame_button.setPosition(m_screen_width / 10, m_screen_height * 0.09);
	exitGame_button.setFillColor(sf::Color::Color(244, 67, 54));
	exitGame_button.setPosition(m_screen_width / 10, m_screen_height * 0.39);

	//text of new game
	menu_newGame.setFont(font);
	menu_newGame.setCharacterSize(m_screen_height / 30);
	menu_newGame.setPosition(m_screen_width * 0.11-8, m_screen_height * 0.11);
	menu_newGame.setFillColor(sf::Color::Black);
	menu_newGame.setString("New Game");


	//text for score table
	text_score_table.setFont(font);
	text_score_table.setCharacterSize(m_screen_height / 30);
	text_score_table.setPosition(m_screen_width * 0.11+25, m_screen_height * 0.21);
	text_score_table.setFillColor(sf::Color::Black);
	text_score_table.setString("Scores");

	table.setFont(font);
	table.setCharacterSize(m_screen_height / 30);
	table.setPosition(m_screen_width*0.5- table.getGlobalBounds().width/2-200,200);
	table.setFillColor(sf::Color::White);


	table_title .setFont(font);
	table_title.setCharacterSize(m_screen_height / 30);
	table_title.setString("Dave's hall of fame: \n \n Score  Time  Name\n");
	table_title.setPosition(m_screen_width * 0.5 - table_title.getGlobalBounds().width / 2,15);
	table_title.setFillColor(sf::Color::White);
	


	//text of help 
	text_help.setFont(font);
	text_help.setCharacterSize(m_screen_height / 30);
	text_help.setPosition(m_screen_width * 0.11+70, m_screen_height * 0.31);
	text_help.setFillColor(sf::Color::Black);
	text_help.setString("Help");

	//text of exit game
	menu_exitGame.setFont(font);
	menu_exitGame.setCharacterSize(m_screen_height / 30);
	menu_exitGame.setPosition(m_screen_width * 0.11-15, m_screen_height * 0.41);
	menu_exitGame.setFillColor(sf::Color::Black);
	menu_exitGame.setString("Exit Game");
	m_texture_help.loadFromFile("help.png");
	help_image.setPosition({ 0,0 });
	help_image.setTexture(m_texture_help);
	//text for back button
	text_back.setFont(font);
	text_back.setCharacterSize(m_screen_height / 30);
	text_back.setPosition(100, 40);
	text_back.setFillColor(sf::Color::Black);
	text_back.setString("Back");



}

void MainMenu::textInput(const char& s)
{
	input_str += s;
	input.setString(input_str);
	input.setPosition(m_screen_width * 0.5 - input.getGlobalBounds().width / 2, m_screen_height * 0.5 + input.getGlobalBounds().height);
}
void MainMenu::saveScore(const int&score,TimeUtils&t) 
{
	std::stringstream o;
	o <<  score<<" " << t.getTimeFormatted()<<" "<<input_str<<std::endl;
	std::ofstream outfile;
	outfile.open("scores.txt", std::ios_base::app);
	outfile << o.str();
	outfile.close();
}
void MainMenu::loadScores()
{
	std::ifstream inFile;

	inFile.open("scores.txt");
	if (!inFile) {
		throw std::runtime_error("Scores file was not found on system");
	}
	else {
		std::string line,name,time;
		int score;
		while (std::getline(inFile, line))
		{
			table_str += line+='\n';
			table_str += '\n';
			table.setString(table_str);
		}
	}

	
}
void MainMenu::setLoading(const bool& b)
{
	m_loading = b;
}
bool MainMenu::newGame(sf::Event & event, sf::RenderWindow & window, bool& help, bool& score)
{

	//get mouse position 
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	//compute global boundries
	sf::Vector2f mouse_world = window.mapPixelToCoords(mouse);
	sf::Vector2i mousePlace;
	if (sf::Event::MouseMoved)
	{
		mousePlace = sf::Vector2i{ event.mouseMove.x , event.mouseMove.y };


		if (exitGame_button.getGlobalBounds().contains(sf::Vector2f(mousePlace)))
		{
			exitGame_button.setOutlineColor(sf::Color::Yellow);
			exitGame_button.setOutlineThickness(5.0f);
		}
		else
		{
			exitGame_button.setOutlineColor(sf::Color::Transparent);
			exitGame_button.setOutlineThickness(5.0f);
		}

		if (newGame_button.getGlobalBounds().contains(sf::Vector2f(mousePlace)))
		{
			newGame_button.setOutlineColor(sf::Color::Yellow);
			newGame_button.setOutlineThickness(5.0f);
		}
		else
		{
			newGame_button.setOutlineColor(sf::Color::Transparent);
			newGame_button.setOutlineThickness(5.0f);
		}


		if (help_button.getGlobalBounds().contains(sf::Vector2f(mousePlace)))
		{
			help_button.setOutlineColor(sf::Color::Yellow);
			help_button.setOutlineThickness(5.0f);
		}
		else
		{
			help_button.setOutlineColor(sf::Color::Transparent);
			help_button.setOutlineThickness(5.0f);
		}
		if (score_table_button.getGlobalBounds().contains(sf::Vector2f(mousePlace)))
		{
			score_table_button.setOutlineColor(sf::Color::Yellow);
			score_table_button.setOutlineThickness(5.0f);
		}
		else
		{
			score_table_button.setOutlineColor(sf::Color::Transparent);
			score_table_button.setOutlineThickness(5.0f);
		}
		if (back_to_menu_button.getGlobalBounds().contains(sf::Vector2f(mousePlace)))
		{
			back_to_menu_button.setOutlineColor(sf::Color::Yellow);
			back_to_menu_button.setOutlineThickness(5.0f);
		}
		else
		{
			back_to_menu_button.setOutlineColor(sf::Color::Transparent);
			back_to_menu_button.setOutlineThickness(5.0f);
		}
	}
	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (exitGame_button.getGlobalBounds().contains(mouse_world))
		{
			window.close();
		}



		if (newGame_button.getGlobalBounds().contains(mouse_world))
		{
			return true;
		}


		if (help_button.getGlobalBounds().contains(mouse_world))
		{
			help = true;
		}

		if (score_table_button.getGlobalBounds().contains(mouse_world))
		{
			score = true;
		}

		if (back_to_menu_button.getGlobalBounds().contains(mouse_world))
		{
			help = false;
			score = false;
		}
	}
	return false;
}

//void MainMenu::setEnd()
//{
//	//simply change the background image to end game
//	m_tex.loadFromFile("res/endgame.jpg");
//	m_tex.setSmooth(true);
//	end.setPosition(sf::Vector2f(0, 0));
//	end.setTexture(m_tex);
//	end.scale(sf::Vector2f(2.6, 3));
//	m_sprite = end;
//}
void MainMenu::drawTextInput(sf::RenderWindow& window)
{
	sf::View menuView(sf::FloatRect(0, 0, 2160.f, 1600.f));
	window.setView(menuView);
	window.draw(text_input_back);
	window.draw(enter_name);
	window.draw(input);
}
void MainMenu::draw(sf::RenderWindow & window, bool help, bool score)
{
	sf::View menuView(sf::FloatRect(0, 0, 2160.f, 1600.f));
	window.setView(menuView);
	if (!help && !score)
	{
		window.draw(m_sprite);
		window.draw(newGame_button);
		window.draw(score_table_button);
		window.draw(help_button);//new
		window.draw(exitGame_button);
		window.draw(menu_newGame);
		window.draw(text_score_table);
		window.draw(text_help);//new
		window.draw(menu_exitGame);
		if(m_loading)
		window.draw(loading);
	}
	//help section
	if (help && !score)
	{
		window.draw(help_image);
		window.draw(back_to_menu_button);
		window.draw(text_back);
		
	}
	//score section
	if (score && !help)
	{
		window.clear();
		window.draw(m_score);
		window.draw(back_to_menu_button);
		window.draw(text_back);
		window.draw(table);
		window.draw(table_title);
		//window.draw(maxScore); //text High Score
		//window.draw(m_max_score); //the High Score himself
	}

}


MainMenu::~MainMenu()
{
}
