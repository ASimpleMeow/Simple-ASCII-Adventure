#ifndef LIVINGOBJECT_H
#define LIVINGOBJECT_H

#include "GameObject.h"

#include <string>

class LivingObject : public GameObject{
public:
	LivingObject();
	LivingObject(int level, int health, int attack, int defence, int experience);
	LivingObject(std::string name, int level, int health, int attack, int defence, int experience);

	virtual void init(std::string name, int level, int health, int attack, int defence, int experience);

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


