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

	while (std::getline(file, line)) {
		m_levelData.push_back(line);
	}

	file.close();

	p_Player = pPlayer;

	//Process the level
	processLevel();
}

//Process the level data to initialise necessary GameObjects and set their position
void Level::processLevel() {
	char tile;
	Enemy* pEnemy;

	for (int i = 0; i < m_levelData.size(); ++i) {
		for (int j = 0; j < m_levelData[i].size(); ++j) {
			tile = m_levelData[i][j];

			switch (tile) {
			case '@':	//Player
				p_Player->setPosition(j, i);
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
			}
		}
	}
}

//Initialise an Enemy with set position
void Level::addEnemy(int posX, int posY, char tile, int health, int attack, int defence, int level, FontColour colour, std::string name, int experience) {
	Enemy e;
	e.init(tile, health, attack, defence, level, colour, name, experience);
	m_enemies.push_back(e);
	m_enemies.back().setPosition(posX, posY);
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
	for (int row = 0; row < m_levelData.size(); ++row) {

		Utils::getInstance()->setCursorToPosition(xOffset, yOffset + row);

		for (int column = 0; column < m_levelData[row].size(); ++column) {
			printf("%c", m_levelData[row][column]);
		}
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

//Gets the tile at positon x, y
char Level::getTile(int x, int y) {
	return m_levelData[y][x];
}

//Sets a tile at position x, y
void Level::setTile(int x, int y, char tile) {
	m_levelData[y][x] = tile;
}

//Process players move to position given
void Level::processPlayerMove(int targetX, int targetY) {

	int playerX = 0;
	int playerY = 0;
	p_Player->getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

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
	}
}

//Start a battle with enemy at position given
void Level::battleEnemy(int targetX, int targetY) {
	int enemyX = 0;
	int enemyY = 0;
	std::string enemyName = "";

	int playerX = 0;
	int playerY = 0;
	p_Player->getPosition(playerX, playerY);

	int attackRoll = 0;
	int attackResult = 0;

	for (std::vector<Enemy>::iterator it = m_enemies.begin(); it != m_enemies.end(); ++it) {
		
		it->getPosition(enemyX, enemyY);
		enemyName = it->getName();

		if (targetX != enemyX && targetY != enemyY) continue;

		//BATTLE START
		std::string battleMessage = "";
		bool someoneDead = false;

		//Players Turn
		someoneDead = p_Player->attack(*it, &battleMessage);
		printf("%s\n", battleMessage.c_str());

		if (someoneDead) {
			m_enemies.erase(it);
			setTile(targetX, targetY, '.');
			break;
		}

		//Enemy Turn
		someoneDead = it->attack(*p_Player, &battleMessage);
		printf("%s\n", battleMessage.c_str());

		if (attackResult != 0) {
			setTile(playerX, playerY, 'x');
			render();
			printf("\nYOU DIED!\n");
			system("PAUSE");
			exit(1);
			return;
		}

		break;
	}

	system("PAUSE");
	render();
	return;
}