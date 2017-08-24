//
//  GameSystem.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#include "GameSystem.h"

#include <conio.h>


//Constructor sets up the game with starting value for the game
//Starting level and starting cutscene
GameSystem::GameSystem(std::string levelFileName, std::string cutsceneFileName) {

	m_player.init(1, 20, 10, 10);

	if(!cutsceneFileName.empty()) m_cutscene.load(cutsceneFileName);		//If there is a cutscene, load it
	m_level.load(levelFileName, &m_player);
}

//Updates the logic of the game
void GameSystem::update() {
	playerMove();
	m_level.update();
}

//Renders the game
void GameSystem::render() {
	m_level.render();
}

void GameSystem::playGame() {

	bool isDone = false;

	while (!isDone) {
		if (m_cutscene.isRunning()) m_cutscene.render();	//Cutscene takes priority over level render
		update();
		render();
	}
}

//Controller for the player
void GameSystem::playerMove() {

	if (!_kbhit()) return;

	char input = _getch();

	m_level.movePlayer(input);
}
