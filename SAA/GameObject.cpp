#include "GameObject.h"



GameObject::GameObject(){
	m_x = 0;
	m_y = 0;
	m_tile = ' ';
	m_colour = FontColour::LIGHTGRAY;
}

GameObject::~GameObject() {}

void GameObject::init(char tile, FontColour colour) {
	m_tile = tile;
	m_colour = colour;
}

//Sets GameObjects position to the references passed
void GameObject::getPosition(int& x, int& y){
	x = m_x;
	y = m_y;
}

//Sets position of GameObject
void GameObject::setPosition(int x, int y){
	m_x = x;
	m_y = y;
}

FontColour GameObject::getColour() {
	return m_colour;
}

char GameObject::getTile() {
	return m_tile;
}

