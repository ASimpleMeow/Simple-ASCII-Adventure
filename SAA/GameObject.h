//
//  GameObject.h
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 22/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Utils.h"

class GameObject {
public:

	GameObject();
	virtual ~GameObject() = 0;	//To make this class abstract

	virtual void init(char tile, FontColour colour = FontColour::LIGHTGRAY);

	//Getters
	virtual void getPosition(int& x, int&y);
	virtual FontColour& getColour();
	virtual char getTile();

	//Setters
	virtual void setPosition(int x, int y);

protected:
	//Position coordinates
	int m_x;
	int m_y;

	//For object rendering
	FontColour m_colour;
	char m_tile;

};

#endif // !GAMEOBJECT_H

