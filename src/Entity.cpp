#include "Entity.h"
#include "ofMain.h"

Entity::Entity()
{
	health = 100;
	entityColor.set(255, 255, 255);
	std::string e = "Entity";
	//nums aleatorios
	std::random_device randomizer;
	std::mt19937 gen(randomizer());
	std::uniform_int_distribution<int> dist(10000, 99999);
	name = e.append(std::to_string(dist(gen)));
}

const char* Entity::toString()
{
	return name.c_str();
}

void Entity::draw()
{
	ofSetColor(entityColor);
	ofCircle(posX, posY, 25);
}
