#include "GameSystem.h"



//Constructor sets up the game
GameSystem::GameSystem(std::string levelFileName) {

	m_player.init(1, 20, 50, 10, 0);

	m_level.load(levelFileName, m_player);
}


void GameSystem::playGame() {

	bool isDone = false;

	while (!isDone) {
		m_level.print(m_player);
		playerMove();
	}
}

void GameSystem::playerMove() {
	char input = _getch();

	m_level.movePlayer(input, m_player);
}