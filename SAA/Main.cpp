//
//  Main.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#include "GameSystem.h"
#include "Utils.h"

#include <windows.h>

int main() {

	//SETTING UP THE WINDOW
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.top, 0, 800, 500, TRUE); // 800 width, 500 height

	Utils::getInstance()->setCursorVisible(false);
	Utils::getInstance()->setFontSize(FontSize::VERY_BIG);



	GameSystem gameSystem("levels/level1.txt", "cutscenes/cutscene1.txt");

	gameSystem.playGame();

	return 0;
}


