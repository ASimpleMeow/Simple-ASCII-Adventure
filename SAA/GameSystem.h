//
//  GameSystem.h
//  SAA - Simple ASCII Adventure
//
//	Contains the game elements together
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "Player.h"
#include "Level.h"
#include "Cutscene.h"

class GameSystem {
public:
	GameSystem(std::string levelFileName, std::string cutsceneFileName = "");

	void playGame();

private:
	void update();
	void render();
	void input();
	bool keyPressed(int key) const;

private:
	Player m_player;
	Level m_level;
	Cutscene m_cutscene;
};

#endif	// GAMESYSTEM_H 

