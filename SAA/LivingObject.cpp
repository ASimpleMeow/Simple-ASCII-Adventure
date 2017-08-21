#include "LivingObject.h"

#include <random>
#include <ctime>

LivingObject::LivingObject(){
}

LivingObject::LivingObject(int level, int health, int attack, int defence, int experience) {
	init("", ' ', level, health, attack, defence, experience);
}

LivingObject::LivingObject(std::string name, char tile, int level, int health, int attack, int defence, int experience) {
	init(name, tile, level, health, attack, defence, experience);
}

void LivingObject::init(std::string name, char tile, int level, int health, int attack, int defence, int experience) {
	m_name = name;
	m_tile = tile;
	m_health = health;
	m_attack = attack;
	m_defence = defence;
	m_level = level;
	m_experience = experience;
}

int LivingObject::attack() {
	static std::default_random_engine randomEngine(time(NULL));
	std::uniform_int_distribution<int> attackRoll(0, m_attack);

	return attackRoll(randomEngine);
}

int LivingObject::takeDamage(int attack) {
	attack -= m_defence;
	if (attack <= 0) return 0;	//Check if attack does damage
	m_health -= attack;
	if (m_health <= 0) return m_experience;	//Check if object died

	return 0;
}

//Setters
void LivingObject::setName(std::string name) {
	m_name = name;
}

void LivingObject::setTile(char tile) {
	m_tile = tile;
}

//Sets LivingObjects stats to the references passed 
void LivingObject::getStats(int& level, int& experience, int& health, int& attack, int& defence) {
	level = m_level;
	experience = m_experience;
	health = m_health;
	attack = m_attack;
	defence = m_defence;
}

std::string LivingObject::getName() {
	return m_name;
}

char LivingObject::getTile() {
	return m_tile;
}
