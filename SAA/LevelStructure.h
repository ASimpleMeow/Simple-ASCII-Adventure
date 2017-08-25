#ifndef LEVELSTRUCTURE_H
#define LEVELSTRUCTURE_H

#include "GameObject.h"
#include "Utils.h"

class LevelStructure : public GameObject {
public:
	LevelStructure();

	void init(char tile, bool isWalkable, FontColour colour = FontColour::LIGHTGRAY);

	//Getters
	bool isWalkable() const;

private:
	bool m_isWalkable;

};

#endif // !LEVELSTRUCTURE_H


