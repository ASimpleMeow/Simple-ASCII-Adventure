#ifndef GameSystem_h
#define GameSystem_h

#include <string>
#include <conio.h>

#include "Player.h"
#include "Level.h"

class GameSystem {
public:
	GameSystem(std::string levelFileName);

	void playGame();
	void playerMove();

private:
	Player m_player;
	Level m_level;
};

#endif	// GameSystem_h 

