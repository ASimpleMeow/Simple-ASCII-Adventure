#include "Utils.h"


bool Utils::instanceActive = false;
Utils* Utils::utils = NULL;

Utils::Utils() {
	m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}


Utils::~Utils() {
	instanceActive = false;
}

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
