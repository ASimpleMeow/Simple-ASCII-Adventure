//
//  Main.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 20/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

/*
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

BOOL setCursorToPosition(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main() {

	setCursorToPosition(40, 10);

	

	system("PAUSE");
	return 0;
}*/



#include "GameSystem.h"
#include <windows.h>


int main() {

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	
	MoveWindow(console, r.left, r.top, 800, 500, TRUE); // 800 width, 500 height

	GameSystem gameSystem("levels/level1.txt");

	gameSystem.playGame();

	return 0;
}
