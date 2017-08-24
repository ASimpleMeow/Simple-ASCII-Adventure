//
//  Enemy.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#include "Enemy.h"


Enemy::Enemy(){}

//Initialise the Enemy
void Enemy::init(char tile, int health, int attack, int defence, int level, FontColour colour, std::string name, int experience) {
	LivingObject::init(tile, level, health, attack, defence, colour, name, experience);
}