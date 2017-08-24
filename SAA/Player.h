//
//  Player.h
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "LivingObject.h"

#include <string>

class Player : public LivingObject{
public:
	Player();

	void init(int level, int health, int attack, int defence, FontColour colour = FontColour::WHITE, std::string name = "Player", int experience = 0);

};

#endif // PLAYER_H

