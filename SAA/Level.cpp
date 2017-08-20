#include "Level.h"



Level::Level() {
}

void Level::load(std::string fileName, Player& player) {

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

	//Process the level
	char tile;

	for (int i = 0; i < m_levelData.size(); ++i) {
		for (int j = 0; j < m_levelData[i].size(); ++j) {
			tile = m_levelData[i][j];

			switch (tile) {
			case '@':	//Player
				player.setPosition(j, i);
				break;
			case 'S':	//Snake
				m_enemies.push_back(Enemy("Snake", tile, 10, 3, 1, 1, 50));
				m_enemies.back().setPosition(j, i);
				break;
			case 'O':	//Ogre
				m_enemies.push_back(Enemy("Ogre", tile, 200, 20, 20, 4, 500));
				m_enemies.back().setPosition(j, i);
				break;
			case 'B':	//Bandit
				m_enemies.push_back(Enemy("Bandit", tile, 100, 15, 10, 3, 250));
				m_enemies.back().setPosition(j, i);
				break;
			case 'D':	//Dragon
				m_enemies.push_back(Enemy("Dragon", tile, 2000, 2000, 2000, 100, 100000));
				m_enemies.back().setPosition(j, i);
				break;
			case 'g':	//Goblin
				m_enemies.push_back(Enemy("Goblin", tile, 35, 10, 5, 2, 50));
				m_enemies.back().setPosition(j, i);
				break;
			}
		}
	}
}

void Level::print(Player& player) {
	LockWindowUpdate(GetConsoleWindow());
	printf(std::string(10000, ' ').c_str());

	setCursorToPosition(25, 0);
	printf("THE SIMPLE ASCII ADVENTURE\n");
	
	printMap();

	printPlayerStatus(player);

	setCursorToPosition(0, 20);

	LockWindowUpdate(NULL);
}

void Level::printMap() {
	for (int i = 0; i < m_levelData.size(); ++i) {
		setCursorToPosition(1, i + 2);
		std::printf("%s\n", m_levelData[i].c_str());
	}
}

void Level::printPlayerStatus(Player& player) {
	int playerLevel = 0, playerExp = 0, playerHealth = 0, playerAttack = 0, playerDefence = 0;
	player.getStats(playerLevel, playerExp, playerHealth, playerAttack, playerDefence);

	setCursorToPosition(64, 2);
	printf("STATUS");
	setCursorToPosition(57, 3);
	printf("----------------------");
	setCursorToPosition(60, 5);
	printf("Level    : %d",playerLevel);
	setCursorToPosition(60, 7);
	printf("EXP      : %d", playerExp);
	setCursorToPosition(60, 9);
	printf("Health   : %d", playerHealth);
	setCursorToPosition(60, 11);
	printf("Attack   : %d", playerAttack);
	setCursorToPosition(60, 13);
	printf("Defence  : %d", playerDefence);
}

BOOL Level::setCursorToPosition(int x, int y) {
	m_coord.X = x;
	m_coord.Y = y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m_coord);
}

void Level::movePlayer(char input, Player& player) {

	int playerX = 0;
	int playerY = 0;
	player.getPosition(playerX, playerY);

	char moveTile;

	switch (input) {
	case 'w':		//up
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 's':		//down
	case 'S':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a':		//left
	case 'A':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'd':		//right
	case 'D':
		processPlayerMove(player, playerX + 1, playerY);
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

void Level::processPlayerMove(Player& player, int targetX, int targetY) {

	int playerX = 0;
	int playerY = 0;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	default:
		battleMonster(player, targetX, targetY);
		break;
	}
}

void Level::battleMonster(Player& player, int targetX, int targetY) {
	int enemyX = 0;
	int enemyY = 0;
	std::string enemyName = "";

	int playerX = 0;
	int playerY = 0;
	player.getPosition(playerX, playerY);

	int attackRoll = 0;
	int attackResult = 0;

	for (int i = 0; i < m_enemies.size(); ++i) {
		
		m_enemies[i].getPosition(enemyX, enemyY);
		enemyName = m_enemies[i].getName();

		if (targetX == enemyX && targetY == enemyY) {

			//Battle
			attackRoll = player.attack();
			printf("Player attacked %s with attack of %d\n", enemyName.c_str(), attackRoll);
			system("PAUSE");
			attackResult = m_enemies[i].takeDamage(attackRoll);
			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				print(player);
				printf("Player has killed %s, %d experience gained\n", enemyName.c_str(), attackResult);
				printf("--------------------------------------------\n%s",player.addExperience(attackResult).c_str());
				m_enemies.erase(m_enemies.begin() + i);
				system("PAUSE");
				print(player);
				return;
			}

			//Monster turn
			attackRoll = m_enemies[i].attack();
			printf("%s attacked with attack of %d\n", enemyName.c_str(), attackRoll);
			system("PAUSE");
			attackResult = player.takeDamage(attackRoll);
			print(player);
			if (attackResult != 0) {
				setTile(playerX, playerY, 'x');
				print(player);
				printf("\nYOU DIED!\n");
				system("PAUSE");
				exit(1);
				return;
			}
			print(player);
			return;
		}
	}
}