//
//  Level.h
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Enemy.h"

#include <vector>

class Level {
public:
	Level();

	void load(std::string fileName, Player* pPlayer);

	void update();

	void render();
	void renderMap();
	void renderPlayerStatus();

	void movePlayer(char input);						//NEEDS ABSTRACTION
	void processPlayerMove(int targetX, int targetY);

	void battleEnemy(int targetX, int targetY);			//NEEDS ABSTRACTION


	//Getters
	char getTile(int x, int y);

	//Setters
	void setTile(int x, int y, char tile);

private:
	void processLevel();
	void addEnemy(int posX, int posY, char tile, int health, int attack, int defence, int level, FontColour colour, std::string name, int experience);

private:
	std::vector<std::string> m_levelData;
	std::vector<Enemy> m_enemies;
	Player* p_Player;

};

#endif // LEVEL_H

