#ifndef ENEMY_H
#define ENEMY_H

#include "LivingObject.h"

#include <string>

class Enemy : public LivingObject{
public:
	enum class EnemyType {
		SNAKE = 'S',
		GOBLIN = 'g',
		BANDIT = 'B',
		OGRE = 'O',
		DRAGON = 'D'
	};

	Enemy(std::string name, EnemyType type, int health, int attack, int defence, int level, int experience);

private:
	EnemyType m_type;

};
#endif // ENEMY_H


