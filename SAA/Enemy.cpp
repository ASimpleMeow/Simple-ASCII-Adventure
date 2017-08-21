#include "Enemy.h"




Enemy::Enemy(std::string name, EnemyType type, int health, int attack, int defence, int level, int experience) : LivingObject(){
	init(name, health, attack, defence, level, experience);
	m_type = type;
}



