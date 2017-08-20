#ifndef Player_h
#define Player_h

#include <random>
#include <ctime>
#include <string>

class Player {
public:
	Player();
	void init(int level, int health, int attack, int defence, int experience);

	int attack();
	int takeDamage(int attack);

	//Setters
	void setPosition(int x, int y);
	std::string addExperience(int experience);

	//Getters
	void getPosition(int& x, int&y);
	void getStats(int& level, int& experience, int& health, int& attack, int& defence);

private:
	//Properties
	int m_level;
	int m_health;
	int m_attack;
	int m_defence;
	int m_experience;
	int m_x;
	int m_y;

};

#endif // Player_h

