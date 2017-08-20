#include "Enemy.h"



Enemy::Enemy(std::string name, char tile, int health, int attack, int defence, int level, int experience) {

	m_name = name;
	m_tile = tile;
	m_health = health;
	m_attack = attack;
	m_defence = defence;
	m_level = level;
	m_experience = experience;
}

//Sets position of enemy
void Enemy::setPosition(int x, int y) {
	m_x = x;
	m_y = y;
}

//Gets position of enmey using reference varaibles
void Enemy::getPosition(int& x, int&y) {
	x = m_x;
	y = m_y;
}

std::string Enemy::getName() {
	return m_name;
}

int Enemy::attack() {
	static std::default_random_engine randomEngine(time(NULL));
	std::uniform_int_distribution<int> attackRoll(0, m_attack);

	return attackRoll(randomEngine);
}

int Enemy::takeDamage(int attack) {
	attack -= m_defence;
	if (attack <= 0) return 0;	//Check if attack does damage
	m_health -= attack;
	if (m_health <= 0) return m_experience;	//Check if enemy died

	return 0;
}


