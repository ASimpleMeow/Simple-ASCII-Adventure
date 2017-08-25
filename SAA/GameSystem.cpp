//
//  GameSystem.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#include "GameSystem.h"
#include "Utils.h"

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
	input();
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

//Controller for input
void GameSystem::input() {
	
	/*
	if (keyPressed('W')) {
		m_player.move(LivingObject::Movement::UP);
	}else if (keyPressed('A')) {
		m_player.move(LivingObject::Movement::LEFT);
	} else if (keyPressed('S')) {
		m_player.move(LivingObject::Movement::DOWN);
	} else if (keyPressed('D')) {
		m_player.move(LivingObject::Movement::RIGHT);
	} else if (keyPressed(VK_SPACE))
		printf("OK");
	*/

	if (!_kbhit()) return;

	char input = _getch();

	m_level.movePlayer(input);
}

bool GameSystem::keyPressed(int key) const {
	return (GetAsyncKeyState(key) & 0x8000 != 0);
}

