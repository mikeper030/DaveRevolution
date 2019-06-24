#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class SoundManager
{
public:
	~SoundManager();
	SoundManager();
	void stopFail();
	void playFail();
	bool isJumpPlaying();
	bool isSuccessPlaying();
	void stopSuccess();
	void playSuccess();
	void stopGift();
	void playGift();
	void playIntro();
	void stopIntro();
	void playExplosion();
	void stopExplosion();
	void playSteps();
	void stopSteps();
	void playGameOver();
	void stopGameOver();
	void playJump();
	void stopJump();
	void playEnemyKilled();
	void stopEnemyKiller();
	void playAmmo();
	void stopAmmo();
	void playPlayerKilled();
	void stopPlayerKilled();
	void playMenu();
	void stopMenu();
	void playGameBackgroud();
	void stopGameBackgroud();
	static SoundManager& getInstance();
private:
	bool destroyed = false;
	SoundManager(const SoundManager&);
	 sf::Music intro, explosion, steps, gameover,
		 gift,ammo, success, fail,jump,enemy_killed,
		 player_killed,menu,game_background;
};

