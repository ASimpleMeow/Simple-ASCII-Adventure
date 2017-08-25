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
#include "LevelStructure.h"

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

	void battleEnemy(LivingObject* enemy);			//NEEDS ABSTRACTION


	//Getters
	//char getTile(int x, int y);

	//Setters
	//void setTile(int x, int y, char tile);

private:
	void processLevel(std::vector<std::string> levelData);
	void addEnemy(int posX, int posY, char tile, int health, int attack, int defence, int level, FontColour colour, std::string name, int experience);
	void addLevelStructure(int posX, int posY, char tile, bool isWalkable, FontColour colour = FontColour::LIGHTGRAY);
	int findEnemyIndex(Enemy& enemy);

private:
	std::vector<LevelStructure> m_structures;
	std::vector<Enemy> m_enemies;
	Player* p_Player;

};

#endif // LEVEL_H

