#include "GameSystem.h"

#include <conio.h>


//Constructor sets up the game
GameSystem::GameSystem(std::string levelFileName) {

	m_player.init(1, 20, 10, 10);

	m_level.load(levelFileName, &m_player);
}

void GameSystem::update() {
	playerMove();
	m_level.update();
}

void GameSystem::render() {
	m_level.render();
}

void GameSystem::playGame() {

	bool isDone = false;

	while (!isDone) {
		update();
		render();
	}
}

void GameSystem::playerMove() {

	if (!_kbhit()) return;

	char input = _getch();

	m_level.movePlayer(input);
}
