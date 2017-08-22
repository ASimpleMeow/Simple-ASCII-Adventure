#ifndef ENEMY_H
#define ENEMY_H

#include "LivingObject.h"
#include "Utils.h"

#include <string>

class Enemy : public LivingObject{
public:
	Enemy();

	void init(char tile, int health, int attack, int defence, int level, FontColour colour = FontColour::LIGHTGRAY, std::string name = "", int experience = 0);

};
#endif // ENEMY_H


