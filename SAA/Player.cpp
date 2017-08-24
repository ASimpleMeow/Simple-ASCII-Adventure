//
//  Player.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#include "Player.h"

#include <random>
#include <ctime>


Player::Player(){}

//Initialises Player with properties
void Player::init(int level, int health, int attack, int defence, FontColour colour, std::string name, int experience){
	LivingObject::init('@', level, health, attack, defence, colour, name, experience);
}
