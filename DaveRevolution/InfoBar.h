#pragma once
#include <SFML/Graphics.hpp>
#include "TimeUtils.h"
using namespace sf;
class InfoBar
{
public:
	InfoBar(const int& s_height, const int& s_width,const int& coins_no,const int& lives,const int& level_shots,const int& level_no, TimeUtils& t);

	void draw(sf::RenderWindow& w);
	void setCoins(const int& score);
	void setLevelNO(const int& num);
	bool lowOnTime() const;
	void setLife(const int& lives);
	void moveDisplay(const Vector2f&);
	void setTimer(TimeUtils& t);
	void setMessage(const std::string &msg)
	{
		message.setString( msg);
	
	}
	void setShowMessage(const bool& f) {
		is_show_message = f;
	}
	void setShots(const int& bombs);
	void updateTime();
private:
	bool is_show_message;
	TimeUtils& m_timer;
	Text life, timer_text, levelNO,shots_left,coins,message;
	Font font;
	int screen_w, screen_h;
};

