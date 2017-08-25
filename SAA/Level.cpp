//
//  Level.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#include "Level.h"
#include "Utils.h"

#include <string>
#include <fstream>

Level::Level() {}

//Loads level from file given
void Level::load(std::string fileName, Player* pPlayer) {

	//Loads the level
	std::ifstream file;

	file.open(fileName);

	if (file.fail()) {
		perror("MISSING LEVEL\n");
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	std::string line;
	std::vector<std::string> levelData;

	while (std::getline(file, line)) {
		levelData.push_back(line);
	}

	file.close();

	p_Player = pPlayer;

	//Process the level
	processLevel(levelData);
}

//Process the level data to initialise necessary GameObjects and set their position
void Level::processLevel(std::vector<std::string> levelData) {
	char tile;
	LevelStructure* levelStructure;


	for (int i = 0; i < levelData.size(); ++i) {
		for (int j = 0; j < levelData[i].size(); ++j) {
			tile = levelData[i][j];

			switch (tile) {
			case '.':
				addLevelStructure(j, i, tile, true);
				break;
			case '#':
				addLevelStructure(j, i, tile, false);
				break;
			case 'S':	//Snake
				addEnemy(j, i, tile, 10, 3, 1, 1, FontColour::LIGHTGREEN, "Snake", 25);
				break;
			case 'g':	//Goblin
				addEnemy(j, i, tile, 35, 10, 5, 2, FontColour::GREEN, "Goblin", 50);
				break;
			case 'O':	//Ogre
				addEnemy(j, i, tile, 200, 20, 20, 4, FontColour::BROWN, "Ogre", 100);
				break;
			case 'B':	//Bandit
				addEnemy(j, i, tile, 100, 15, 10, 3, FontColour::DARKGRAY, "Bandit", 100);
				break;
			case 'D':	//Dragon
				addEnemy(j, i, tile, 2000, 2000, 2000, 100, FontColour::RED, "Dragon", 10000);
				break;
			case '@':	//Player
				p_Player->setPosition(j, i);
				break;
			}
			
		}
	}
}

void Level::addLevelStructure(int posX, int posY, char tile, bool isWalkable, FontColour colour) {
	LevelStructure ls;
	ls.init(tile, isWalkable, colour);
	ls.setPosition(posX, posY);
	m_structures.push_back(ls);
}

//Initialise an Enemy with set position
void Level::addEnemy(int posX, int posY, char tile, int health, int attack, int defence, int level, FontColour colour, std::string name, int experience) {
	addLevelStructure(posX, posY, '.', true);
	Enemy e;
	e.init(tile, health, attack, defence, level, colour, name, experience);
	e.setPosition(posX, posY);
	m_enemies.push_back(e);
}

void Level::update() {

}

/* RENDERING SCREEN*/

//Main render function
void Level::render() {
	LockWindowUpdate(GetConsoleWindow());

	Utils::getInstance()->clearScreen();
	Utils::getInstance()->setFontColour(FontColour::WHITE);
	Utils::getInstance()->setCursorToPosition(26, 0);

	printf("THE SIMPLE ASCII ADVENTURE\n");
	
	renderMap();

	renderPlayerStatus();

	Utils::getInstance()->setCursorToPosition(0, 20);

	LockWindowUpdate(NULL);
}

//Render map
void Level::renderMap() {

	Utils::getInstance()->setFontColour(FontColour::LIGHTGRAY);

	int gameObjectX = 0;	//GameObject X coordinate
	int gameObjectY = 0;	//GameObject Y coordinate
	int yOffset = 1;		//Amount down the map is rendered from the top
	int xOffset = 1;		//Amount right the map is rendered from the left

	//RENDER WALLS AND GROUND
	for (std::vector<LevelStructure>::iterator it = m_structures.begin(); it != m_structures.end(); ++it) {
		it->getPosition(gameObjectX, gameObjectY);
		Utils::getInstance()->setCursorToPosition(gameObjectX + xOffset, gameObjectY + yOffset);
		Utils::getInstance()->setFontColour(it->getColour());
		printf("%c", it->getTile());
	}

	//RENDER PLAYER
	p_Player->getPosition(gameObjectX, gameObjectY);
	Utils::getInstance()->setCursorToPosition(gameObjectX + xOffset, gameObjectY+ yOffset);
	Utils::getInstance()->setFontColour(p_Player->getColour());
	printf("%c", p_Player->getTile());

	//RENDER ENEMIES
	for (std::vector<Enemy>::iterator it = m_enemies.begin(); it != m_enemies.end(); ++it) {
		it->getPosition(gameObjectX, gameObjectY);
		Utils::getInstance()->setCursorToPosition(gameObjectX + xOffset, gameObjectY + yOffset);
		Utils::getInstance()->setFontColour(it->getColour());
		printf("%c", it->getTile());
	}
}

//Render player status to the right of map
void Level::renderPlayerStatus() {

	Utils::getInstance()->setFontColour(FontColour::WHITE);

	int playerLevel = 0, playerExp = 0, playerHealth = 0, playerAttack = 0, playerDefence = 0;
	p_Player->getStats(playerLevel, playerExp, playerHealth, playerAttack, playerDefence);

	Utils::getInstance()->setCursorToPosition(64, 2);
	printf("STATUS");
	Utils::getInstance()->setCursorToPosition(57, 3);
	printf("----------------------");
	Utils::getInstance()->setCursorToPosition(60, 5);
	printf("Level    : %d",playerLevel);
	Utils::getInstance()->setCursorToPosition(60, 7);
	printf("EXP      : %d", playerExp);
	Utils::getInstance()->setCursorToPosition(60, 9);
	printf("Health   : %d", playerHealth);
	Utils::getInstance()->setCursorToPosition(60, 11);
	printf("Attack   : %d", playerAttack);
	Utils::getInstance()->setCursorToPosition(60, 13);
	printf("Defence  : %d", playerDefence);
}

//Determine the input from User to move Player
void Level::movePlayer(char input) {
	int playerX = 0;
	int playerY = 0;
	p_Player->getPosition(playerX, playerY);

	switch (input) {
	case 'w':		//up
	case 'W':
		processPlayerMove(playerX, playerY - 1);
		break;
	case 's':		//down
	case 'S':
		processPlayerMove(playerX, playerY + 1);
		break;
	case 'a':		//left
	case 'A':
		processPlayerMove(playerX - 1, playerY);
		break;
	case 'd':		//right
	case 'D':
		processPlayerMove(playerX + 1, playerY);
		break;
	default:
		break;
	}
}

/*
//Gets the tile at positon x, y
char Level::getTile(int x, int y) {
	return m_levelData[y][x];
}

//Sets a tile at position x, y
void Level::setTile(int x, int y, char tile) {
	m_levelData[y][x] = tile;
}
*/

//Process players move to position given
void Level::processPlayerMove(int targetX, int targetY) {

	int playerX = 0;
	int playerY = 0;
	int gameObjectX = 0;
	int gameObjectY = 0;

	p_Player->getPosition(playerX, playerY);

	Enemy* enemy = NULL;

	for (std::vector<Enemy>::iterator it = m_enemies.begin(); it != m_enemies.end(); ++it) {
		it->getPosition(gameObjectX, gameObjectY);
		if (gameObjectX == targetX && gameObjectY == targetY) {
			enemy = &(*it);
			battleEnemy(enemy);
			return;
		}
	}

	for (std::vector<LevelStructure>::iterator it = m_structures.begin(); it != m_structures.end(); ++it) {
		it->getPosition(gameObjectX, gameObjectY);
		if (gameObjectX == targetX && gameObjectY == targetY) {
			if (!it->isWalkable()) return;
			p_Player->setPosition(gameObjectX, gameObjectY);
			it->setPosition(playerX, playerY);
			return;
		}
	}

	//char moveTile = getTile(targetX, targetY);

	/*
	switch (moveTile) {
	case '.':										//Floor - Allow movement there
		p_Player->setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':										//Wall
		break;
	default:										//Enemy encounter
		battleEnemy(targetX, targetY);
		break;
	}*/
}


//Start a battle with enemy at position given
void Level::battleEnemy(LivingObject* enemy) {

	int enemyX = 0;
	int enemyY = 0;
	enemy->getPosition(enemyX, enemyY);

	int playerX = 0;
	int playerY = 0;
	p_Player->getPosition(playerX, playerY);


	//BATTLE START
	std::string battleMessage = "";
	bool someoneDead = false;

	//Players Turn
	someoneDead = p_Player->attack(*enemy, &battleMessage);
	printf("%s\n", battleMessage.c_str());

	if (someoneDead) {
		Enemy* thisEnemy = dynamic_cast<Enemy*>(enemy);
		if (thisEnemy != NULL) {
			m_enemies.erase(m_enemies.begin() + findEnemyIndex(*thisEnemy));
			system("PAUSE");
			render();
			return;
		}
		perror("KILLED NOT AN ENEMY!?\n");
		system("PAUSE");
		exit(1);
	}

	//Enemy Turn
	someoneDead = enemy->attack(*p_Player, &battleMessage);
	printf("%s\n", battleMessage.c_str());

	if (someoneDead) {
		p_Player->setTile('x');
		p_Player->setColour(FontColour::LIGHTRED);
		render();
		printf("\nYOU DIED!\n");
		system("PAUSE");
		exit(1);
		return;
	}

	system("PAUSE");
}

int Level::findEnemyIndex(Enemy& enemy) {

	for (int i = 0; i < m_enemies.size(); ++i) {
		if (&m_enemies[i] == &enemy) return i;
	}
}