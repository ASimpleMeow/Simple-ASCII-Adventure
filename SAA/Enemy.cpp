#include "Enemy.h"




Enemy::Enemy(std::string name, char tile, int health, int attack, int defence, int level, int experience) : LivingObject(){
	init(name, tile, health, attack, defence, level, experience);
}



