#include "ObjectFactory.h"
#include "Wall.h"
#include "Spike.h"
#include "Water.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "MovementBlocker.h"
#include "Ammo.h"
#include "Life.h"
#include "FakeWall.h"
#include "Crow.h"
#include "DoorKey.h"
#include "Door.h"
#include "Elevator.h"
std::map<std::string, std::unique_ptr<StaticObject>(*)(sf::Sprite&, sf::FloatRect&)> ObjectFactory::m_s_map;
std::map<std::string, std::unique_ptr<DynamicObject>(*)(sf::Sprite&, sf::FloatRect&)> ObjectFactory::m_d_map;


ObjectFactory::ObjectFactory()
{
}
std::unique_ptr<StaticObject> ObjectFactory::create_static(const std::string& name
	,  sf::Sprite& s, FloatRect& f)
{
	static bool initial = true;
	if (initial) {
		s_registerit("Wall",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<StaticObject>
			 {return std::make_unique<Wall>(s1, s2); });
		s_registerit("Spike",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<StaticObject>
			{return std::make_unique<Spike>(s1, s2); });
		s_registerit("Water",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<StaticObject>
			{return std::make_unique<Water>(s1, s2); });
		
		s_registerit("Money",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<StaticObject>
			{return std::make_unique<Coin>(s1, s2); });
		
		s_registerit("Blocker",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<StaticObject>
			{return std::make_unique<MovementBlocker>(s1, s2); });
		s_registerit("Ammo",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<StaticObject>
			{return std::make_unique<Ammo>(s1, s2); });
		s_registerit("Life",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<StaticObject>
			{return std::make_unique<Life>(s1, s2); });
		s_registerit("FakeWall",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<StaticObject>
			{return std::make_unique<FakeWall>(s1, s2); });
		
		s_registerit("Key",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<StaticObject>
			{return std::make_unique<DoorKey>(s1, s2); });
		s_registerit("Door",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<StaticObject>
			{return std::make_unique<Door>(s1, s2); });
		
		initial = false;
	}
	auto it = m_s_map.find(name);
	if (it == m_s_map.end())
		return std::make_unique<Wall>(s, f);
	return it->second(s,f);
}

std::unique_ptr<DynamicObject> ObjectFactory::create_dynamic(const std::string& name
	, sf::Sprite& s, FloatRect& f)
{
	static bool initial = true;
	if (initial) {
		d_registerit("Player",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<DynamicObject>
			{return std::make_unique<Player>(s1, s2); });
		d_registerit("Enemy",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<DynamicObject>
			{return std::make_unique<Enemy>(s1, s2); });
		d_registerit("Crow",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<DynamicObject>
			{return std::make_unique<Crow>(s1, s2); });
		d_registerit("Elevator",
			[](sf::Sprite & s1, FloatRect & s2) -> std::unique_ptr<DynamicObject>
			{return std::make_unique<Elevator>(s1, s2); });
		
		initial = false;
	}
	auto it = m_d_map.find(name);
	if (it == m_d_map.end())
		return nullptr;
	return it->second(s, f);
}


void ObjectFactory::d_registerit(const std::string& name, std::unique_ptr<DynamicObject>(*f)(sf::Sprite&, sf::FloatRect&))
{
	m_d_map.emplace(name, f);
}

void ObjectFactory::s_registerit(const std::string& name, std::unique_ptr<StaticObject>(*f)(sf::Sprite&,sf::FloatRect&))
{
	m_s_map.emplace(name, f);
}



