#ifndef Enemy_h
#define Enemy_h

#include <string>
#include <random>
#include <ctime>

class Enemy {
public:
	Enemy(std::string name, char tile, int health, int attack, int defence, int level, int experience);

	int attack();
	int takeDamage(int attack);

	//Setters
	void setPosition(int x, int y);

	//Getters
	void getPosition(int& x, int&y);
	std::string getName();

private:
	std::string m_name;
	char m_tile;

	int m_x;
	int m_y;


	int m_health;
	int m_attack;
	int m_defence;
	int m_level;
	int m_experience;
};
#endif // Enemy_h


