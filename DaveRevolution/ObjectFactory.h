#pragma once
#include <memory>
#include "GameObject.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "DynamicObject.h"
class ObjectFactory
{
public:
	ObjectFactory();
	static std::unique_ptr<StaticObject> create_static(const std::string& name, sf::Sprite&, FloatRect&);
	static std::unique_ptr<DynamicObject> create_dynamic(const std::string& name, sf::Sprite&, FloatRect&);

	static void s_registerit(const std::string& name, std::unique_ptr<StaticObject>(*f)(sf::Sprite&,sf::FloatRect&));
	static void d_registerit(const std::string& name, std::unique_ptr<DynamicObject>(*f)(sf::Sprite&, sf::FloatRect&));

private:
	static std::map<std::string, std::unique_ptr<StaticObject>(*)(sf::Sprite&, sf::FloatRect&)> m_s_map;
	static std::map<std::string, std::unique_ptr<DynamicObject>(*)(sf::Sprite&, sf::FloatRect&)> m_d_map;

};

