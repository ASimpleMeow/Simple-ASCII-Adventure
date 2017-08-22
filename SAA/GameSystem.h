#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "Player.h"
#include "Level.h"

class GameSystem {
public:
	GameSystem(std::string levelFileName);

	void playGame();

private:
	void update();
	void render();
	void playerMove();

private:
	Player m_player;
	Level m_level;
};

#endif	// GAMESYSTEM_H 

