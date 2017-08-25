//
//  LivingObject.h
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 22/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#ifndef LIVINGOBJECT_H
#define LIVINGOBJECT_H

#include "GameObject.h"
#include "Utils.h"

#include <string>

class LivingObject : public GameObject{

public:

	enum class Movement {
		UP, DOWN, LEFT, RIGHT
	};

	LivingObject();
	virtual ~LivingObject() = 0;	//To make this class abstract

	virtual void init(char tile, int level, int health, int attack, int defence, FontColour colour = FontColour::LIGHTGRAY, std::string name = "", int experience = 0);

	virtual void move(Movement move);
	virtual bool attack(LivingObject& other, std::string* message = NULL);
	virtual int takeDamage(int attack);
	virtual std::string addExperience(int experience);

	//Setters
	virtual void setName(std::string name);

	//Getters
	virtual void getStats(int& level, int& experience, int& health, int& attack, int& defence) const;
	virtual std::string getName() const;

protected:
	std::string m_name;

	int m_health;
	int m_attack;
	int m_defence;
	int m_level;
	int m_experience;

};

#endif // !LIVINGOBJECT_H


