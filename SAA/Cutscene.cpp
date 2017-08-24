//
//  Cutscene.cpp
//  SAA - Simple ASCII Adventure
//
//  Created by Oleksandr Kononov on 24/08/2017.
//  Copyright © 2017 Oleksandr Kononov. All rights reserved.
//

#include "Cutscene.h"

#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

Cutscene::Cutscene() {}

//Load cutscene from file
//File will contain parameters for cutscene like deltaTime
//and linesPerScene as first line in the file seperated by comma
void Cutscene::load(std::string fileName) {

	//Clear previous data
	m_deltaSleep = 0;
	m_linesPerScene = 0;
	m_cutsceneData.clear();

	//Loads the cutscene file
	std::ifstream file;

	file.open(fileName);

	if (file.fail()) {
		perror("CUTSCENE MISSING!\n");
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	std::string line;

	//CUTSCENE PARAMETERS
	std::getline(file, line);		//Getting parameters for cutscene
	std::stringstream ss(line);		//Creating a string stream for parsing parameters

	while (ss.good()) {
		std::string substr;
		getline(ss, substr, ',');
		(m_deltaSleep == 0) ? m_deltaSleep = std::stoi(substr) : m_linesPerScene = std::stoi(substr);
	}


	//CUTSCENE DATA
	while (std::getline(file, line)) {
		m_cutsceneData.push_back(line);
	}

	file.close();
	m_isRunning = true;
}

//Renders cutscene data to screen
//Uses cutscene parameters to display data correctly
void Cutscene::render() {

	Utils::getInstance()->setCursorVisible(false);
	Utils::getInstance()->setFontSize(FontSize::VERY_BIG);

	int line = 0;	//Index for current lines on screen

	for (std::vector<std::string>::iterator it = m_cutsceneData.begin(); it != m_cutsceneData.end(); ++it) {

		Utils::getInstance()->setCursorToPosition(19, ((37 - m_linesPerScene)/2) + line);	//Set position to be centered
		printf("%s", it->c_str());
		++line;
		
		if (line % m_linesPerScene == 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(m_deltaSleep));
			line = 0;
			Utils::getInstance()->clearScreen();
		}
	}

	Utils::getInstance()->clearScreen();
	m_isRunning = false;
}

//Checks if the cutscene is running
bool Cutscene::isRunning() {
	return m_isRunning;
}
