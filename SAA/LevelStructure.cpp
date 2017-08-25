#include "LevelStructure.h"

LevelStructure::LevelStructure() {}

//Initialise GameObject with parameters given
void LevelStructure::init(char tile, bool isWalkable, FontColour colour) {
	GameObject::init(tile, colour);
	m_isWalkable = isWalkable;
}

bool LevelStructure::isWalkable() const{
	return m_isWalkable;
}

