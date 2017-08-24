//
//  Utils.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 22/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#include "Utils.h"

#include <string>

bool Utils::instanceActive = false;		//Initially the instance is not active
Utils* Utils::utils = NULL;				

//Constructor gets the console handle
Utils::Utils() {
	m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

Utils::~Utils() {
	instanceActive = false;
}

//Get instance of the Utils singleton
Utils* Utils::getInstance() {

	if (!instanceActive) {
		utils = new Utils();
		instanceActive = true;
		return utils;
	}

	return utils;
}

//Set the cursor position on console window
void Utils::setCursorToPosition(int x, int y) {
	m_cursorPos.X = x;
	m_cursorPos.Y = y;
	SetConsoleCursorPosition(m_handle, m_cursorPos);
}

//Sets the cursors visibilty
void Utils::setCursorVisible(bool showCursor) {
	GetConsoleCursorInfo(m_handle, &m_cursorInfo);
	m_cursorInfo.bVisible = showCursor; // set the cursor visibility
	SetConsoleCursorInfo(m_handle, &m_cursorInfo);
}

//Sets fonts size
void Utils::setFontSize(const FontSize size) {
	m_font = { sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(m_handle, false, &m_font)) return;

	switch (size) {
	case FontSize::VERY_SMALL:
		m_fontSize = { 6, 9 };
		break;
	case FontSize::SMALL:
		m_fontSize = { 7, 12 };
		break;
	case FontSize::NORMAL:
		m_fontSize = { 8, 12 };
		break;
	case FontSize::BIG:
		m_fontSize = { 10, 18 };
		break;
	case FontSize::VERY_BIG:
		m_fontSize = { 12, 16 };
		break;
	default:
		return;
	}

	m_font.dwFontSize = m_fontSize;
	SetCurrentConsoleFontEx(m_handle, false, &m_font);
}

//Sets font colour
void Utils::setFontColour(const FontColour colour) {
	SetConsoleTextAttribute(m_handle, static_cast<int>(colour));
}

//Screens screen
void Utils::clearScreen() {
	setCursorToPosition(0, 0);
	printf(std::string(3040,' ').c_str());
}
