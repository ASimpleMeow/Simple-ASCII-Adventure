#ifndef ENEMY_H
#define ENEMY_H

#include "LivingObject.h"

#include <string>

class Enemy : public LivingObject{
public:
	Enemy(std::string name, char tile, int health, int attack, int defence, int level, int experience);
};
#endif // ENEMY_H


