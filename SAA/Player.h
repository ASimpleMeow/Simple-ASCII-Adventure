#ifndef PLAYER_H
#define PLAYER_H

#include "LivingObject.h"

#include <string>

class Player : public LivingObject{
public:
	Player();

	void init(int level, int health, int attack, int defence, FontColour colour = FontColour::WHITE, std::string name = "Player", int experience = 0);

	std::string addExperience(int experience);

private:

};

#endif // PLAYER_H

