#include "Enemy.h"


Enemy::Enemy(){

}

void Enemy::init(char tile, int health, int attack, int defence, int level, FontColour colour, std::string name, int experience) {
	LivingObject::init(tile, level, health, attack, defence, colour, name, experience);
}