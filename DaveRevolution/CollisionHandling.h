#pragma once

#include "GameObject.h"

#include <iostream>
#include <typeinfo>
// Sample struct for exception throwing
struct UnknownCollision
{
	UnknownCollision(GameObject& a, GameObject& b) : first(a), second(b)
	{
		std::cout << "Unknown collision of " << typeid(a).name() << " and "
			<< typeid(b).name() << std::endl;
	}
	GameObject& first;
	GameObject& second;
};

void processCollision(GameObject& object1, GameObject& object2);

