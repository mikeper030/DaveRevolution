#include "SoundManager.h"
#include <iostream>
#include "Exceptions.h"

SoundManager& SoundManager::getInstance()
{
	static SoundManager sm;
	return sm;
}

SoundManager::~SoundManager()
{
	
}

SoundManager::SoundManager()
{

	if(!intro.openFromFile("game.wav"))
		throw(FileNotFoundException("game wav"));
	intro.setVolume(70);
	intro.setLoop(true);


	if(!explosion.openFromFile("bullet.wav"))
		throw(FileNotFoundException("bullet wav"));
	explosion.setVolume(60);

	
	if(!ammo.openFromFile("ammo.wav"))
		throw(FileNotFoundException("game wav"));
	ammo.setVolume(90);

	if(!steps.openFromFile("steps.wav"))
		throw(FileNotFoundException("game wav"));
	steps.setVolume(50);
	steps.setLoop(true);

	if(!gameover.openFromFile("game_over.wav"))
		throw(FileNotFoundException("game over wav"));
	gameover.setVolume(60);

	if(!player_killed.openFromFile("game_over.wav"))
		throw(FileNotFoundException("game wav"));
	gameover.setVolume(60);

	if(!enemy_killed.openFromFile("enemy_killed.wav"))
		throw(FileNotFoundException("enemy killed wav"));
	enemy_killed.setVolume(70);

	if(!gift.openFromFile("consume.wav"))
		throw(FileNotFoundException("consume wav"));
	gift.setVolume(60);

	if(!fail.openFromFile("strike.wav"))
		throw(FileNotFoundException("game wav"));
	fail.setVolume(60);

	if (!game_background.openFromFile("Fantasy.ogg"))
		throw(FileNotFoundException("game wav"));
	game_background.setVolume(60);
	game_background.setLoop(true);
	if (!menu.openFromFile("Game-Menu.ogg"))
		throw(FileNotFoundException("game wav"));
	menu.setVolume(60);
	menu.setLoop(true);
	if(!success.openFromFile("success.wav"))
		throw(FileNotFoundException("success wav"));
	success.setVolume(60);
	if(!jump.openFromFile("jump.wav"))
		throw(FileNotFoundException("jump wav"));
	jump.setVolume(35);
	jump.setLoop(true);
}
void SoundManager::stopFail()
{
	fail.stop();
}
void SoundManager::playFail()
{

	fail.play();
}
bool SoundManager::isJumpPlaying()
{
	return jump.getStatus() == sf::SoundSource::Playing;
}
bool SoundManager::isSuccessPlaying()
{
	return success.getStatus()== sf::SoundSource::Playing;
}
void SoundManager::stopSuccess()
{
	success.stop();
	
}
void SoundManager::playSuccess()
{
	success.play();
}
void SoundManager::stopGift()
{
	gift.stop();
}
void SoundManager::playGift()
{
	gift.play();
}
void SoundManager::playIntro()
{
	intro.play();
}

void SoundManager::stopIntro()
{
	intro.stop();
}

void SoundManager::playExplosion()
{
	explosion.play();
}

void SoundManager::stopExplosion()
{
	explosion.stop();
}

void SoundManager::playSteps()
{
	steps.play();
}

void SoundManager::stopSteps()
{
	steps.stop();
}

void SoundManager::playGameOver()
{
	gameover.play();
}

void SoundManager::stopGameOver()
{
	gameover.stop();
}

void SoundManager::playJump()
{
	jump.play();
}

void SoundManager::stopJump()
{
	jump.stop();
}

void SoundManager::playEnemyKilled()
{
	enemy_killed.play();
}

void SoundManager::stopEnemyKiller()
{
	enemy_killed.stop();
}

void SoundManager::playAmmo()
{
	ammo.play();
}

void SoundManager::stopAmmo()
{
	ammo.stop();
}

void SoundManager::playPlayerKilled()
{
	player_killed.play();
}

void SoundManager::stopPlayerKilled()
{
	player_killed.stop();
}

void SoundManager::playMenu()
{
	if (menu.getStatus() != sf::SoundSource::Playing)
		menu.play();
}

void SoundManager::stopMenu()
{
	menu.stop();
}

void SoundManager::playGameBackgroud()
{
	if (game_background.getStatus() != sf::SoundSource::Playing)
		game_background.play();
}

void SoundManager::stopGameBackgroud()
{
	game_background.stop();
}



