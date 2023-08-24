#pragma once
#include <string>
#include <random>
//#include "GenericArray.h"

class Entity
{
public:
	std::string name;
	int health;

	Entity();

	const char* toString();

	float posX, posY;

	float velX, velY;

	void draw();
};
/*
//template specialization
template<>
inline void GenericArray<Entity>::listContents()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "[" << i << "] = " << array[i].toString() << std::endl;
	}
}
*/