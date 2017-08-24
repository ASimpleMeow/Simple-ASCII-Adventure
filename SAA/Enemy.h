//
//  Enemy.h
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#ifndef ENEMY_H
#define ENEMY_H

#include "LivingObject.h"
#include "Utils.h"

#include <string>

class Enemy : public LivingObject{
public:
	Enemy();

	void init(char tile, int health, int attack, int defence, int level, FontColour colour = FontColour::LIGHTGRAY, std::string name = "", int experience = 0);

};
#endif // ENEMY_H


