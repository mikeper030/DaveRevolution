#pragma once
#include "DynamicObject.h"
#include <SFML/Audio.hpp>

class Player :
	public DynamicObject
{


private:
	sf::Texture t;
	sf::Sprite s;
	sf::FloatRect m_rect;
	int m_level_no;
	int coins_collected;
	int m_life;
	bool m_checkpoint;
	bool restart_level;
	bool flag=false;
	int m_ammo;
	bool jumping = false;
	bool has_k = false;
	bool level_finished;
	bool m_game_finished;


public:
	void setGameFinished(const bool&b)
	{
		m_game_finished = b;
	}
	const bool& isGameFinished()
	{
		return m_game_finished;
	}
	const int& getLevelNo()
	{
		return m_level_no;
	}
	void setLevelNo(const int& i)
	{
		m_level_no = i;
	}
	const bool& isLevelFinsihed()
	{
		return level_finished;
	}
	void setLevelFinished(const bool& b)
	{
		level_finished = b;
	}
	const bool& has_key()
	{
		return has_k;
	}
	void setHasKey(const bool& b)
	{
		has_k = b;
	}
	void setFlag(const bool& b) {
		flag = b;
	}
	const bool& getFlag() {
		return flag;
	}
	void addLife()
	{
		m_life++;
	}
	void addAmmo()
	{
		m_ammo += 5;
	}
	const int& getAmmo()
	{
		return m_ammo;
	}
	const bool& isGoTocheckPoint() {
		return m_checkpoint;
	}
	void setGotoCheckpoint(const bool& b) {
		m_checkpoint = b;
	}
	void goalReach(bool flag);
	int jumpCounter = 0;
	virtual void animateCharacter(sf::RenderWindow& window,const float& time);
	void lowerLife();
	void lowerAmmo();
	void Shoot(bool& f);

	const bool shootAnimReady();
	
	void updateCharacter(const sf::Vector2f& vector, const float&,const int& direction,bool&shoot) override;
	const bool& is_jump();
	const sf::Vector2f& getCheckpointPosition();
	void setCheckpointPosition(const sf::Vector2f& coords);
	void addCoin() {
		coins_collected++;
	};
	const int& getLife() {
		return m_life;
	}
	void goToCheckPoint();
	void init(const sf::Sprite& sprite, const FloatRect& rect);
	
	Player(sf::Sprite& sprite, sf::FloatRect& rect);
	Player(sf::Sprite& sprite, sf::FloatRect& rect, const int& life, const int& ammo, const int& score, const int& level);
	void deathAnim();
	//void setCheckpoint(int i); 
	bool jumpFlag = true;
	const int& getCoins();
	void animate(const float& t, RenderWindow& w)override;
	
	
	

	
};

