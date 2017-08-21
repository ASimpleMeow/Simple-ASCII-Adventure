#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Enemy.h"

#include <windows.h>
#include <vector>

class Level {
public:
	Level();

	void load(std::string fileName, Player& player);
	void print(Player& player);
	void movePlayer(char input, Player& player);


	//Getters
	char getTile(int x, int y);

	//Setters
	void setTile(int x, int y, char tile);

private:
	void processPlayerMove(Player& player, int targetX, int targetY);
	void battleMonster(Player& player, int targetX, int targetY);
	void printMap();
	void printPlayerStatus(Player& player);
	BOOL setCursorToPosition(int x, int y);

private:
	std::vector<std::string> m_levelData;
	std::vector<Enemy> m_enemies;
	COORD m_coord;

};

#endif // LEVEL_H

