//
//  Utils.h
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 22/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#ifndef UTILS_H
#define UTILS_H

#include <Windows.h>

enum class FontSize {
	VERY_SMALL, SMALL, NORMAL, BIG, VERY_BIG
};

enum class FontColour {
	BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3,
	RED = 4, MAGENTA = 5, BROWN = 6, LIGHTGRAY = 7,
	DARKGRAY = 8, LIGHTBLUE = 9, LIGHTGREEN = 10, LIGHTCYAN = 11,
	LIGHTRED = 12, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15
};

class Utils {
public:

	static Utils* getInstance();
	~Utils();

	void setCursorToPosition(int x, int y);
	void setCursorVisible(bool showCursor);
	void setFontSize(const FontSize size);
	void setFontColour(const FontColour colour);
	void clearScreen();

private:
	static bool instanceActive;
	static Utils* utils;
	Utils();


	HANDLE m_handle;							//Handle to access input and screen buffers
	COORD m_cursorPos;							//Coordinate, used here for setting cursor position
	COORD m_fontSize;							//Coordinate, holding X and Y of font size
	CONSOLE_CURSOR_INFO m_cursorInfo;			//Cursor info, used here for setting cursor visibility
	CONSOLE_FONT_INFOEX m_font;					//Font info, used here for setting font size
};


#endif // !UTILS_H

