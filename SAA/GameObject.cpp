//
//  GameObject.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 22/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#include "GameObject.h"


//Initialise all parameters
GameObject::GameObject(){
	m_x = 0;
	m_y = 0;
	m_tile = ' ';
	m_colour = FontColour::LIGHTGRAY;
}

GameObject::~GameObject() {}

//Initialise GameObject with parameters given
void GameObject::init(char tile, FontColour colour) {
	m_tile = tile;
	m_colour = colour;
}

//Sets position of GameObject
void GameObject::setPosition(int x, int y){
	m_x = x;
	m_y = y;
}

//Sets tile
void GameObject::setTile(char tile) {
	m_tile = tile;
}

//Sets colour
void GameObject::setColour(FontColour colour) {
	m_colour = colour;
}

//Gets GameObjects position to the references passed
void GameObject::getPosition(int& x, int& y) const {
	x = m_x;
	y = m_y;
}

//Gets colour of tile (font)
FontColour GameObject::getColour() const{
	return m_colour;
}

//Gets tile
char GameObject::getTile() const{
	return m_tile;
}

