#ifndef LIVINGOBJECT_H
#define LIVINGOBJECT_H

#include "GameObject.h"
#include "Utils.h"

#include <string>

class LivingObject : public GameObject{

public:
	LivingObject();

	virtual void init(char tile, int level, int health, int attack, int defence, FontColour colour = FontColour::LIGHTGRAY, std::string name = "", int experience = 0);

	virtual int attack();
	virtual int takeDamage(int attack);

	//Setters
	virtual void setName(std::string name);

	//Getters
	virtual void getStats(int& level, int& experience, int& health, int& attack, int& defence);
	virtual std::string getName();

protected:
	std::string m_name;

	int m_health;
	int m_attack;
	int m_defence;
	int m_level;
	int m_experience;

};

#endif // !LIVINGOBJECT_H


