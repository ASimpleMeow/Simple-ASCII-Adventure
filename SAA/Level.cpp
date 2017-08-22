#include "Level.h"
#include "Utils.h"

#include <string>
#include <fstream>
#include <iostream>

Level::Level() {
}

void Level::load(std::string fileName, Player* pPlayer) {

	Utils::getInstance()->setCursorVisible(false);
	Utils::getInstance()->setFontSize(FontSize::NORMAL);

	//Loads the level
	std::ifstream file;

	file.open(fileName);

	if (file.fail()) {
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
	printf(std::string(10000, ' ').c_str());

	Utils::getInstance()->setCursorToPosition(25, 0);
	printf("THE SIMPLE ASCII ADVENTURE\n");
	
	renderMap();

	renderPlayerStatus();

	Utils::getInstance()->setCursorToPosition(0, 20);

	LockWindowUpdate(NULL);
}

//Render map
void Level::renderMap() {

	char tile = ' ';
	int eX = 0;
	int eY = 0;

	Utils::getInstance()->setCursorToPosition(0, 1);

	printf(" ");

	for (int i = 0; i < m_levelData.size(); ++i) {
		for (int j = 0; j < m_levelData[i].size(); ++j) {
			tile = m_levelData[i][j];
			if (tile == '.' || tile == '#' || tile == '@') {
				Utils::getInstance()->setFontColour(FontColour::LIGHTGRAY);
				printf("%c", m_levelData[i][j]);
			}
			else {
				for (int enemyIndex = 0; enemyIndex < m_enemies.size(); ++enemyIndex) {
					m_enemies[enemyIndex].getPosition(eX, eY);
					if (eX == j && eY == i) {
						Utils::getInstance()->setFontColour(m_enemies[enemyIndex].getColour());
						printf("%c", m_enemies[enemyIndex].getTile());
					}
				}
			}
		}
		printf("\n ");
	}
}

//Render player status to the right of map
void Level::renderPlayerStatus() {
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

char Level::getTile(int x, int y) {
	return m_levelData[y][x];
}

void Level::setTile(int x, int y, char tile) {
	m_levelData[y][x] = tile;
}

void Level::processPlayerMove(int targetX, int targetY) {

	int playerX = 0;
	int playerY = 0;
	p_Player->getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		p_Player->setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	default:
		//checkEnemy(player, moveTile, targetX, targetY);
		battleEnemy(targetX, targetY);
		break;
	}
}

void Level::battleEnemy(int targetX, int targetY) {
	int enemyX = 0;
	int enemyY = 0;
	std::string enemyName = "";

	int playerX = 0;
	int playerY = 0;
	p_Player->getPosition(playerX, playerY);

	int attackRoll = 0;
	int attackResult = 0;

	for (int i = 0; i < m_enemies.size(); ++i) {
		
		m_enemies[i].getPosition(enemyX, enemyY);
		enemyName = m_enemies[i].getName();

		if (targetX == enemyX && targetY == enemyY) {

			//Battle
			attackRoll = p_Player->attack();
			printf("Player attacked %s with attack of %d\n", enemyName.c_str(), attackRoll);
			system("PAUSE");
			attackResult = m_enemies[i].takeDamage(attackRoll);
			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				render();
				printf("Player has killed %s, %d experience gained\n", enemyName.c_str(), attackResult);
				printf("--------------------------------------------\n%s", p_Player->addExperience(attackResult).c_str());
				m_enemies.erase(m_enemies.begin() + i);
				system("PAUSE");
				render();
				return;
			}

			//Monster turn
			attackRoll = m_enemies[i].attack();
			printf("%s attacked with attack of %d\n", enemyName.c_str(), attackRoll);
			system("PAUSE");
			attackResult = p_Player->takeDamage(attackRoll);
			render();
			if (attackResult != 0) {
				setTile(playerX, playerY, 'x');
				render();
				printf("\nYOU DIED!\n");
				system("PAUSE");
				exit(1);
				return;
			}
			render();
			return;
		}
	}
}