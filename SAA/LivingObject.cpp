#include "LivingObject.h"

#include <random>
#include <ctime>

LivingObject::LivingObject(){
	m_level = 0;
	m_health = 0;
	m_attack = 0;
	m_defence = 0;
	m_name = "";
	m_experience = 0;
}

void LivingObject::init(char tile, int level, int health, int attack, int defence, FontColour colour, std::string name, int experience) {
	GameObject::init(tile, colour);
	m_level = level;
	m_health = health;
	m_attack = attack;
	m_defence = defence;
	m_experience = experience;
	m_name = name;
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

//Set name
void LivingObject::setName(std::string name) {
	m_name = name;
}

//Sets LivingObjects stats to the references passed 
void LivingObject::getStats(int& level, int& experience, int& health, int& attack, int& defence) {
	level = m_level;
	experience = m_experience;
	health = m_health;
	attack = m_attack;
	defence = m_defence;
}

//Get name
std::string LivingObject::getName() {

	return m_name;
}