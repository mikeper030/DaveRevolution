#include "InfoBar.h"
#include <sstream>
#include "Player.h"
#include <exception>
InfoBar::InfoBar(const int& s_height, const int& s_width,const int& coins_no,const int& lives,
	const int& level_shots,const int& level_no, TimeUtils& t)
	:m_timer(t), screen_h(s_height), screen_w(s_width), is_show_message(false)
  {

 if(!
	font.loadFromFile("font.ttf")
	  )
    throw std::runtime_error("Font not found on FileSystem");
	
    message.setFont(font);
	levelNO.setFont(font);
	shots_left.setFont(font);
	life.setFont(font);
	timer_text.setFont(font);
	coins.setFont(font);
	
	message.setString("Game Over. Restarting...");
	message.setFillColor(sf::Color::Blue);
	life.setFillColor(sf::Color::Blue);
	coins.setFillColor(sf::Color::Blue);
	shots_left.setFillColor(sf::Color::Blue);
	levelNO.setFillColor(sf::Color::Blue);
	timer_text.setFillColor(sf::Color::Red);
	
	message.setCharacterSize(s_height /18);
	life.setCharacterSize(s_height / 25);
	coins.setCharacterSize(s_height / 25);
	shots_left.setCharacterSize(s_height / 25);
	levelNO.setCharacterSize(s_height / 25);
	timer_text.setCharacterSize(s_height / 25);

	message.setPosition(s_width/2 - message.getLocalBounds().width / 2, s_height / 2- message.getLocalBounds().height);
	timer_text.setPosition(s_width * 0.005 , s_height/50);
	life.setPosition(s_width * 0.2-screen_w * 0.1 - life.getLocalBounds().width / 2, s_height / 50);
	coins.setPosition(s_width * 0.4 - screen_w * 0.1 - coins.getLocalBounds().width / 2, s_height / 50);
	levelNO.setPosition(s_width * 0.6 - screen_w * 0.1 - levelNO.getLocalBounds().width / 2, s_height / 50);
	shots_left.setPosition(s_width * 0.8 - screen_w * 0.1 - shots_left.getLocalBounds().width / 2, s_height / 50);

	setCoins(coins_no);
	setLevelNO(level_no);
	setLife(lives);
	setShots(level_shots);
	
	
}

void InfoBar::draw(sf::RenderWindow& w)
{

	w.draw(timer_text);
	w.draw(life);
	w.draw(shots_left);
	w.draw(levelNO);
	w.draw(coins);
	if (is_show_message) {
		
		w.draw(message);
	}
}

void InfoBar::setCoins(const int& score)
{
	std::ostringstream o;
	o << "SCORE: " << score;
	std::string f(o.str());
	coins.setString(f);
}

void InfoBar::setLevelNO(const int& num)
{
	std::ostringstream o;
	o << "LEVEL: " << num;
	std::string f(o.str());
	levelNO.setString(f);
}
bool InfoBar::lowOnTime() const
{
	return m_timer.getElapsedTimeAsSeconds() < 20 && m_timer.getTimeFormatted() != "-:--";
}
void InfoBar::setLife(const int& lives)
{
	std::ostringstream o;
	o << "LIVES: " << lives;
	std::string f(o.str());
	life.setString(f);
}
void InfoBar::moveDisplay(const Vector2f&center)
{
	  timer_text.setPosition(center.x - screen_w * 0.41- life.getLocalBounds().width / 2, screen_h / 50);
	  message.setPosition(center.x- message.getLocalBounds().width / 2, center.y- message.getLocalBounds().height);
	  life.setPosition(center.x-screen_w*0.32 - life.getLocalBounds().width / 2, screen_h / 50);
	   coins.setPosition(center.x - screen_w * 0.13 - coins.getLocalBounds().width / 2, screen_h / 50);
	   levelNO.setPosition(center.x , screen_h / 50);
	   shots_left.setPosition(center.x+ screen_w * 0.31 -shots_left.getLocalBounds().width / 2, screen_h / 50);
}
void InfoBar::setTimer(TimeUtils& t)
{
	m_timer = t;
}
void InfoBar::setShots(const int& bombs)
{
	std::ostringstream o;
	o << "BULLETS: " << bombs;
	std::string f(o.str());
	shots_left.setString(f);
}



void InfoBar::updateTime()
{
	timer_text.setString(m_timer.getTimeFormatted());
}