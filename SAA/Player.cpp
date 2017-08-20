#include "Player.h"



//Constructor, initialise position to zero
Player::Player() {
	m_x = 0;
	m_y = 0;
}

//Initialises Player with properties
void Player::init(int level, int health, int attack, int defence, int experience) {
	m_level = level;
	m_health = health;
	m_attack = attack;
	m_defence = defence;
	m_experience = experience;
}

//Sets position of player
void Player::setPosition(int x, int y) {
	m_x = x;
	m_y = y;
}

std::string Player::addExperience(int experience) {
	m_experience += experience;
	std::string levelUpMessage = "";

	//Level up
	if (m_level < (0.2 * sqrt(m_experience))) {
		levelUpMessage += "Leveled UP!\n";
		int levelDiff = ((0.2 * sqrt(m_experience)) - m_level) + 1;

		levelUpMessage += "Attack +"+ std::to_string(10*levelDiff) +"\n";
		m_attack += (10 * levelDiff);
		levelUpMessage += "Defence +" + std::to_string(5 * levelDiff) + "\n";
		m_defence += (5 * levelDiff);
		levelUpMessage += "Health +" + std::to_string(10 * levelDiff) + "\n\n";
		m_health += (10 * levelDiff);
		m_level = (0.2 * sqrt(m_experience)) + 1;
	}

	return levelUpMessage;
}

//Gets position of player using reference varaibles
void Player::getPosition(int& x, int&y) {
	x = m_x;
	y = m_y;
}

//Get player stats
void Player::getStats(int& level, int& experience, int& health, int& attack, int& defence) {
	level = m_level;
	experience = m_experience;
	health = m_health;
	attack = m_attack;
	defence = m_defence;
}

int Player::attack() {
	static std::default_random_engine randomEngine(time(NULL));
	std::uniform_int_distribution<int> attackRoll(0, m_attack);

	return attackRoll(randomEngine);
}

int Player::takeDamage(int attack) {
	attack -= m_defence;
	if (attack <= 0) return 0;	//Check if attack does damage
	m_health -= attack;
	if (m_health <= 0) return 1;	//Check if player died

	return 0;
}