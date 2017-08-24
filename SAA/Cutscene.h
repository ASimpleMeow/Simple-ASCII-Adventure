//
//  Cutscene.h
//  SAA - Simple ASCII Adventure
//
//	Creates a cutscene object which will render ASCII onto
//	screen, priority preceeds Level object
//
//  Created by Oleksandr Kononov on 24/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "Utils.h"

#include <string>
#include <vector>

class Cutscene {
public:
	Cutscene();

	//Load cutscene from file
	void load(std::string fileName);

	void render();

	//Getters
	bool isRunning();

private:
	bool m_isRunning;		//Is the cutscene running
	int m_deltaSleep;		//Time between scenes (thread sleep time)
	int m_linesPerScene;	//Lines displayed per scene

	std::vector<std::string> m_cutsceneData;

};

#endif // !CUTSCENE_H


