#include "Player.h"

#include <random>
#include <ctime>


Player::Player(){}

//Initialises Player with properties
void Player::init(int level, int health, int attack, int defence, FontColour colour, std::string name, int experience){
	LivingObject::init('@', level, health, attack, defence, colour, name, experience);
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
