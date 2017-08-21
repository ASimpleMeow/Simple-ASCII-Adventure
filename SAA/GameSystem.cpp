#include "GameSystem.h"

#include <conio.h>


//Constructor sets up the game
GameSystem::GameSystem(std::string levelFileName) {

	m_player.init(1, 20, 50, 10, 0);

	m_level.load(levelFileName, m_player);
}


void GameSystem::playGame() {

	bool isDone = false;

	while (!isDone) {
		playerMove();
		m_level.update();
		m_level.render(m_player);
	}
}

void GameSystem::playerMove() {
	char input = _getch();

	m_level.movePlayer(input, m_player);
}