#include "CollisionHandling.h"
#include "MovementBlocker.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Wall.h"
#include "Player.h"
#include "Coin.h"
#include "Elevator.h"
#include "DynamicObject.h"
#include "Water.h"
#include "Spike.h"
#include "Checkpoint.h"
#include "Constants.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Consumable.h"
#include "Ammo.h"
#include "Life.h"
#include "SoundManager.h"
#include "Controller.h"
#include "FakeWall.h"
#include "DoorKey.h"
#include "Crow.h"
#include "Door.h"
#include "Exceptions.h"
namespace { // anonymous namespace — the standard way to make function "static"
	
	SoundManager& manager = SoundManager::getInstance();
// primary collision-processing functions
	void collide(Player& p, Elevator& w) {
		
		sf::FloatRect rectOne;
		w.getBoundingRectangle().getGlobalBounds().intersects(p.getBoundingRectangle().getGlobalBounds(), rectOne);

		if (!p.isOnGround())
		{
			//push from under the player             //pixel dependent
			if (p.getBoundingRectangle().getPosition().y< w.getBoundingRectangle().getGlobalBounds().top)//wiz.m_BoundingRectangle.getGlobalBounds().top > wall.m_BoundingRectangle.getGlobalBounds().top)
			{
				
				if (rectOne.width > rectOne.height) {
					while (p.getBoundingRectangle().getGlobalBounds().intersects(w.getBoundingRectangle().getGlobalBounds()))
					{
						//fix the enum
						if (w.getDirection() == 2) {
							p.getBoundingRectangle().move(-3.f, -0.4f * 40);
						}
						else {
							p.getBoundingRectangle().move(3.f, -0.4f * 40);
						}
					
					}
					p.jumpCounter = 1;
					p.onGround(true);
			
				}
			}
			//push from top of player
			else if (p.getBoundingRectangle().getGlobalBounds().intersects(w.getBoundingRectangle().getGlobalBounds()))//wiz.m_BoundingRectangle.getGlobalBounds().top > wall.m_BoundingRectangle.getGlobalBounds().top)
			{

				if (rectOne.width > rectOne.height) {
					while (p.getBoundingRectangle().getGlobalBounds().intersects(w.getBoundingRectangle().getGlobalBounds()))
					{

						p.getBoundingRectangle().move(0.0f, 0.4f * 40);

					}
				}
			}
		}
 
		if (rectOne.width < rectOne.height)
		{

			if (p.getBoundingRectangle().getPosition().x < w.getBoundingRectangle().getPosition().x)
			{
				while (p.getBoundingRectangle().getGlobalBounds().intersects(w.getBoundingRectangle().getGlobalBounds()))
				{

					p.getBoundingRectangle().move(-0.01f, 0.0f);

				}
			}
			else if (p.getBoundingRectangle().getPosition().x > w.getBoundingRectangle().getPosition().x)
			{
				while (p.getBoundingRectangle().getGlobalBounds().intersects(w.getBoundingRectangle().getGlobalBounds()))
				{

					p.getBoundingRectangle().move(0.01f, 0.0f);

				}
			}

		}
	}
	void collide(Player& p, GameObject& w) {
		
		sf::FloatRect rectOne;
		w.getBoundingRectangle().getGlobalBounds().intersects(p.getBoundingRectangle().getGlobalBounds(), rectOne);

		if (!p.isOnGround())
		{
			//push from under the player
			if (p.getBoundingRectangle().getPosition().y < w.getBoundingRectangle().getGlobalBounds().top)//wiz.m_BoundingRectangle.getGlobalBounds().top > wall.m_BoundingRectangle.getGlobalBounds().top)
			{
				if (rectOne.width > rectOne.height) {
					while (p.getBoundingRectangle().getGlobalBounds().intersects(w.getBoundingRectangle().getGlobalBounds()))
					{
						p.getBoundingRectangle().move(0.0f, -0.4f * 40);
					}
					p.jumpCounter = 1;
					p.onGround(true);
				

				}
			}
			//push from top of player
			else if (p.getBoundingRectangle().getGlobalBounds().intersects(w.getBoundingRectangle().getGlobalBounds()))//wiz.m_BoundingRectangle.getGlobalBounds().top > wall.m_BoundingRectangle.getGlobalBounds().top)
			{

			
				if (rectOne.width > rectOne.height) {
					while (p.getBoundingRectangle().getGlobalBounds().intersects(w.getBoundingRectangle().getGlobalBounds()))
					{

						p.getBoundingRectangle().move(0.0f, 0.4f * 40);

					}
				}
			}
		}

		if (rectOne.width < rectOne.height)
		{

			if (p.getBoundingRectangle().getPosition().x < w.getBoundingRectangle().getPosition().x)
			{
				while (p.getBoundingRectangle().getGlobalBounds().intersects(w.getBoundingRectangle().getGlobalBounds()))
				{
					//push left
					p.getBoundingRectangle().move(-0.01f, 0.0f);

				}
			}
			else if (p.getBoundingRectangle().getPosition().x > w.getBoundingRectangle().getPosition().x)
			{
				while (p.getBoundingRectangle().getGlobalBounds().intersects(w.getBoundingRectangle().getGlobalBounds()) )
				{
					//push right
					p.getBoundingRectangle().move(0.01f, 0.0f);

				}
			}

		}
	}
	void playerWall(GameObject& player,
		GameObject& wall)
	{
		
		// To get the actual types and use them:
		Player& p = dynamic_cast<Player&>(player);
		Wall& w = dynamic_cast<Wall&>(wall);
		if (manager.isJumpPlaying()) {
			manager.stopJump();
		}
		// Get intersecting rectangle and base collision on it.
		

		collide(p, w);


		
	}
	void bulletFakeTile(GameObject& bulletObj, GameObject& fakeTileObj)
	{
		FakeWall& fakeTile = dynamic_cast<FakeWall&>(fakeTileObj);
		Bullet& bullet = dynamic_cast<Bullet&>(bulletObj);

	

		if (fakeTile.getBoundingRectangle().getPosition().x < bullet.getBoundingRectangle().getPosition().x)
		{
			//	system("pause");
			fakeTile.remove();
			bullet.remove();
		}

	}

	void fakeTileBullet(GameObject& fakeTileObj, GameObject& bulletObj)
	{
	
		bulletFakeTile(bulletObj, fakeTileObj);

	}
	void bulletWall(GameObject& bullet, GameObject& wall)
	{
		bullet.remove();
	}
	void wallBullet(GameObject& wall, GameObject& bullet)
	{
		bulletWall(bullet, wall);
	}
	void playerElevator(GameObject& player,
		GameObject& elevator)
	{
		
		Player& p = dynamic_cast<Player&>(player);
		Elevator& w = dynamic_cast<Elevator&>(elevator);
		collide(p, w);
	}
	void checkPointPlayer(GameObject& checkpoint, GameObject& player)
	{
		Checkpoint& c = dynamic_cast<Checkpoint&>(checkpoint);
		c.setActiveCheckpoint(true);
		Player& p = dynamic_cast<Player&>(player);
		if (p.getCheckpointPosition()!=checkpoint.getBoundingRectangle().getPosition())
		{	
			p.setCheckpointPosition(checkpoint.getBoundingRectangle().getPosition());
			manager.stopSuccess();
			manager.playSuccess();
		}
		
		

			
	

	}
	void playerCheckPoint(GameObject& player, GameObject& checkpoint) 
	{
		checkPointPlayer(checkpoint, player);
	}
	void elevatorPlayer(GameObject& elevator,
		GameObject& player)
	{
		playerElevator(player, elevator);
	}

	void blockerElevator(GameObject& blocker,
		GameObject& elevator)
	{
		//elevatorBlocker(elevator,blocker);
	}
	void elevatorBlocker(GameObject& elevator,
		GameObject& blocker)
	{
		
		MovementBlocker& b= dynamic_cast<MovementBlocker&>(blocker);
		Elevator& w = dynamic_cast<Elevator&>(elevator);
		w.changeDirection();

	}
	//main function to handle player strikes
	void playerWater(GameObject& player, GameObject& water) {
		
		Player& p = dynamic_cast<Player&>(player);
		collide(p, water);
		
		if (!p.getFlag() ) {
			p.goToCheckPoint();
			manager.stopFail();
			manager.playFail();
			
		}
		p.setFlag(true);
	}
	void enemyBlocker(GameObject& enemy, GameObject& blocker)
	{
		Enemy& e = dynamic_cast<Enemy&>(enemy);
		e.changeDirection();
	}
	void blockerEnemy(GameObject& blocker, GameObject& enemy) {
		enemyBlocker(enemy, blocker);
	}
	void waterplayer(GameObject& water, GameObject& player) {
		playerWater(player, water);
	}
	void spikePlayer(GameObject& spike, GameObject& player)
	{
		playerWater(player, spike);
	}
	void playerSpike(GameObject& player, GameObject& spike) {
		playerWater(player, spike);
	}
	// secondary collision-processing functions that just
	// implement symmetry: swap the parameters and call a
	// primary function
	void wallPlayer(GameObject& wall,
		GameObject& player)
	{
		playerWall(player, wall);
	}
	
	
	void playerCoin(GameObject& player,
		GameObject& coin)
	{
		
			Player& p = dynamic_cast<Player&>(player);
			
			Coin& c = dynamic_cast<Coin&>(coin);
			if (!c.consumed()) {
				p.addCoin();
			}
			c.consumeAnim(true);
			
		
	}
	void coinPlayer(GameObject& coin,
		GameObject& player)
	{
		playerCoin(player, coin);
	}
	void playerEnemy(GameObject& player,
		GameObject& enemy)
	{
		Player& p = dynamic_cast<Player&>(player);
		Enemy &e = dynamic_cast<Enemy&>(enemy);

		if (!p.isOnGround())
		{
			if (p.getBoundingRectangle().getPosition().y < e.getBoundingRectangle().getGlobalBounds().top)
			{
				e.remove();

			}
		}

		if (!p.getFlag()) {
			//


			p.goToCheckPoint();
			manager.stopFail();
			manager.playFail();

		}
		p.setFlag(true);
	}
	void enemyPlayer(GameObject& enemy,
		GameObject& player)
	{
		playerEnemy(player, enemy);
	}
	void playerBullet(GameObject& player,
		GameObject& bullet)
	{
		bullet.remove();
		Player& p = dynamic_cast<Player&>(player);
		p.goToCheckPoint();
		manager.stopFail();
		manager.playFail();
	}
	void bulletPlayer(GameObject& bullet,
		GameObject& player)
	{
		playerBullet(player,bullet);
	}
	void bulletEnemy(GameObject& bullet,
		GameObject& enemy)
	{
		Bullet& c = dynamic_cast<Bullet&>(bullet);
		if (!c.consumed()) {
			bullet.remove();
			enemy.remove();
			manager.stopEnemyKiller();
			manager.playEnemyKilled();
		}
		c.consumeAnim(true);
		
	}

	void enemyBullet(GameObject& enemy,
		GameObject& bullet)
	{
		bulletEnemy(bullet, enemy);
	}
	
 
	void playerAmmo(GameObject& player,
		GameObject& ammo)
	{
		Player& p = dynamic_cast<Player&>(player);
		
		Ammo& a = dynamic_cast<Ammo&>(ammo);
		if (!a.consumed()) {
			p.addAmmo();
			manager.stopAmmo();
			manager.playAmmo();
		
		}
		a.consumeAnim(true);
		a.remove();
	
		
		
		
		
	}
	void ammoPlayer(GameObject& ammo,
		GameObject& player)
	{
		playerAmmo(player, ammo);
	}
	void playerLife(GameObject& player,
		GameObject& life)
	{
		Player& p = dynamic_cast<Player&>(player);
		Life& a = dynamic_cast<Life&>(life);
		if (!a.consumed())
		{
			p.addLife();
			manager.stopGift();
			manager.playGift();
		}
		a.consumeAnim(true);
		a.remove();
	}
	void lifePlayer(GameObject& life,
		GameObject& player)
	{
		playerLife(player, life);
	}
	void playerKey(GameObject& playerObj, GameObject& key_Obj)
	{
		// To get the actual types and use them:
		Player& player = dynamic_cast<Player&>(playerObj);
		DoorKey& doorKey = dynamic_cast<DoorKey&>(key_Obj);

		// Get intersecting rectangle and base collision on it.
		if (!doorKey.consumed()) {
			player.setHasKey(true);
			
			manager.stopSuccess();
			manager.playSuccess();
			doorKey.remove();
		}
		doorKey.consumeAnim(true);
	}

	void keyPlayer(GameObject& key_Obj, GameObject& playerObj)
	{
		playerKey(playerObj, key_Obj);
	}
	
	void crowWall(GameObject& crow, GameObject& wall)
	{
		Crow& e = dynamic_cast<Crow&>(crow);
		e.changeDirection();
	}
	void wallCrow(GameObject& wall, GameObject& crow)
	{ 
		crowWall(crow, wall);
	}
	void crowBlocker(GameObject& crow, GameObject& wall)
	{
		crowWall(crow, wall);
	}
	void blockerCrow(GameObject& blocker, GameObject& crow)
	{
		crowBlocker(crow, blocker);
	}
	void playerCrow(GameObject& player, GameObject& crow)
	{
		Player& p = dynamic_cast<Player&>(player);
		if (!p.getFlag()) {
			p.goToCheckPoint();
			manager.stopFail();
			manager.playFail();

		}
		p.setFlag(true);
	}
	void crowPlayer(GameObject& crow, GameObject& player)
	{
		playerCrow(player, crow);
	}
	void crowBullet(GameObject& crow, GameObject& bullet)
	{
		Bullet& c = dynamic_cast<Bullet&>(bullet);
		if (!c.consumed()) {
			bullet.remove();
			crow.remove();
			manager.stopEnemyKiller();
			manager.playEnemyKilled();
		}
		c.consumeAnim(true);
	}
	void bulletCrow(GameObject& bullet, GameObject& crow)
	{
		crowBullet(crow, bullet);
	}
	void playerDoor(GameObject& player, GameObject& door)
	{
		Door& d = dynamic_cast<Door&>(door);
		if (!d.consumed()) {
			Player& p = dynamic_cast<Player&>(player);
			if (p.getLevelNo() < MAX_LEVELS_NO) {
				if (p.has_key()) {
					p.setLevelFinished(true);
					if (!manager.isSuccessPlaying()) {

						manager.playSuccess();
					}
				}
			}
			else
			{
				p.setGameFinished(true);
			}
		}d.consumeAnim(true);
	}
	void crowCrow(GameObject& crow1, GameObject& crow2)
	{
		Crow& c1 = dynamic_cast<Crow&>(crow1);
		Crow& c2 = dynamic_cast<Crow&>(crow2);
		c1.changeDirection();
		c2.changeDirection();

	}
	void doorPlayer(GameObject& door, GameObject& player)
	{
		playerDoor(player, door);
	}
	

	using HitFunctionPtr = void (*)(GameObject&, GameObject&);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Player), typeid(Wall))] = &playerWall;
		phm[Key(typeid(Wall), typeid(Player))] = &wallPlayer;
		phm[Key(typeid(Coin), typeid(Player))] = &coinPlayer;
		phm[Key(typeid(Player), typeid(Coin))] = &playerCoin;
		phm[Key(typeid(Player), typeid(Elevator))] = &playerElevator;
		phm[Key(typeid(Elevator), typeid(Player))] = &elevatorPlayer;
		phm[Key(typeid(Elevator), typeid(MovementBlocker))] = &elevatorBlocker;
		phm[Key(typeid(MovementBlocker), typeid(Elevator))] = &blockerElevator;
		phm[Key(typeid(Player), typeid(Water))] = &playerWater;
		phm[Key(typeid(Water), typeid(Player))] = &waterplayer;
		phm[Key(typeid(Player), typeid(Spike))] = &playerSpike;
		phm[Key(typeid(Spike), typeid(Player))] = &spikePlayer;
		phm[Key(typeid(Checkpoint), typeid(Player))] = &checkPointPlayer;
		phm[Key(typeid(Player), typeid(Checkpoint))] = &playerCheckPoint;
		phm[Key(typeid(Enemy), typeid(MovementBlocker))] = &enemyBlocker;
		phm[Key(typeid(MovementBlocker), typeid(Enemy))] = &blockerEnemy;
		phm[Key(typeid(Enemy), typeid(Player))] = &enemyPlayer;
		phm[Key(typeid(Player), typeid(Enemy))] = &playerEnemy;
		phm[Key(typeid(Player), typeid(Bullet))] = &playerBullet;
		phm[Key(typeid(Bullet), typeid(Player))] = &bulletPlayer;
		phm[Key(typeid(Enemy), typeid(Bullet))] = &enemyBullet;
		phm[Key(typeid(Bullet), typeid(Enemy))] = &bulletEnemy;
		phm[Key(typeid(Player), typeid(Ammo))] = &playerAmmo;
		phm[Key(typeid(Ammo), typeid(Player))] = &ammoPlayer;
		phm[Key(typeid(Player), typeid(Life))] = &playerLife;
		phm[Key(typeid(Life), typeid(Player))] = &lifePlayer;
		phm[Key(typeid(Bullet), typeid(Wall))] = &bulletWall;
		phm[Key(typeid(Wall), typeid(Bullet))] = &wallBullet;
		phm[Key(typeid(Bullet), typeid(FakeWall))] = &bulletFakeTile;
		phm[Key(typeid(FakeWall), typeid(Bullet))] = &fakeTileBullet;
		phm[Key(typeid(Player), typeid(DoorKey))] = &playerKey;
		phm[Key(typeid(DoorKey), typeid(Player))] = &keyPlayer;
		
		phm[Key(typeid(Crow), typeid(Wall))] = &crowWall;
		phm[Key(typeid(Wall), typeid(Crow))] = &wallCrow;
		phm[Key(typeid(Crow), typeid(MovementBlocker))] = &crowBlocker;
		phm[Key(typeid(MovementBlocker), typeid(Crow))] = &blockerCrow;
		phm[Key(typeid(Crow), typeid(Player))] = &crowPlayer;
		phm[Key(typeid(Player), typeid(Crow))] = &playerCrow;
		phm[Key(typeid(Crow), typeid(Bullet))] = &crowBullet;
		phm[Key(typeid(Bullet), typeid(Player))] = &bulletCrow;
		phm[Key(typeid(Player), typeid(Door))] = &playerDoor;
		phm[Key(typeid(Door), typeid(Player))] = &doorPlayer;
		phm[Key(typeid(Crow), typeid(Crow))] = &crowCrow;
		


		return phm;
	}

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}
	
	
	
} // end namespace

void processCollision(GameObject& object1, GameObject& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		//throw UnknownCollision(object1, object2);
	}else
	phf(object1, object2);
}

