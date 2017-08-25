//
//  LivingObject.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 22/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#include "LivingObject.h"

#include <random>
#include <ctime>

//Initialise all parameters
LivingObject::LivingObject(){
	m_level = 0;
	m_health = 0;
	m_attack = 0;
	m_defence = 0;
	m_name = "";
	m_experience = 0;
}

LivingObject::~LivingObject() {}

//Initialise LivingObject with parameters given
void LivingObject::init(char tile, int level, int health, int attack, int defence, FontColour colour, std::string name, int experience) {
	GameObject::init(tile, colour);
	m_level = level;
	m_health = health;
	m_attack = attack;
	m_defence = defence;
	m_experience = experience;
	m_name = name;
}

//Move the LivingObject
void LivingObject::move(Movement move) {

	switch (move) {
	case Movement::UP:
		setPosition(m_x, m_y - 1);
		break;
	case Movement::DOWN:
		setPosition(m_x, m_y + 1);
		break;
	case Movement::LEFT:
		setPosition(m_x - 1, m_y);
		break;
	case Movement::RIGHT:
		setPosition(m_x + 1, m_y);
		break;
	}
}

//Attacks another LivingObject
//Using uniformly random attack in range of this objects attack stat
//deal damage to the other LivingObject
//If string pointer is passed, record the battle log
bool LivingObject::attack(LivingObject& other, std::string* message) {

	static std::default_random_engine randomEngine(time(NULL));	//Make one time random number generator
	std::uniform_int_distribution<int> attackRoll(0, m_attack);	//Return int in range of attack stat

	int attackValue = attackRoll(randomEngine);			//This objects attack value
	int attackResult = other.takeDamage(attackValue);	//The result of the attack
	bool isDead = false;								//Is the other object dead
	std::string logMessage = "";						//Battle log

	logMessage = m_name + " attacked " + other.getName() + " with attack of "+ std::to_string(attackValue) +"\n";

	//Other object died
	if (attackResult != 0) {
		logMessage += m_name + " has killed " + other.getName() + ", "+std::to_string(attackResult)+" experience gained\n";
		logMessage+="--------------------------------------------\n"+ addExperience(attackResult);
		isDead = true;
	}

	if (message != NULL) *message = logMessage;
	return isDead;
}

//Take damage from the attack
//Reduce the damage taken by using defence stat
int LivingObject::takeDamage(int attack) {
	attack -= m_defence;
	if (attack <= 0) return 0;	//Check if attack does damage
	m_health -= attack;
	if (m_health <= 0) return m_experience;	//Check if object died

	return 0;
}

//Add experience given to object
//Return level up string if a new level reached
std::string LivingObject::addExperience(int experience) {
	m_experience += experience;
	std::string levelUpMessage = "";

	//Level up using formula
	if (m_level < (0.2 * sqrt(m_experience))) {
		levelUpMessage += "Leveled UP!\n";
		int levelDiff = ((0.2 * sqrt(m_experience)) - m_level) + 1;

		levelUpMessage += "Attack +" + std::to_string(10 * levelDiff) + "\n";
		m_attack += (10 * levelDiff);
		levelUpMessage += "Defence +" + std::to_string(5 * levelDiff) + "\n";
		m_defence += (5 * levelDiff);
		levelUpMessage += "Health +" + std::to_string(10 * levelDiff) + "\n\n";
		m_health += (10 * levelDiff);
		m_level = (0.2 * sqrt(m_experience)) + 1;
	}

	return levelUpMessage;
}

//Set name
void LivingObject::setName(std::string name) {
	m_name = name;
}

//Sets LivingObjects stats to the references passed 
void LivingObject::getStats(int& level, int& experience, int& health, int& attack, int& defence) const {
	level = m_level;
	experience = m_experience;
	health = m_health;
	attack = m_attack;
	defence = m_defence;
}

//Get name
std::string LivingObject::getName() const {
	return m_name;
}