//============================================================================
// Name        : LevelParser.cpp
// Author      : Jeroen Verstraelen
// Version     :
// Description : Parser for Space Invaders XML documents.
//============================================================================

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <stdexcept>
#include <list>
#include <iostream>
#include "LevelParser.h"
#include "../../Model/Level.h"
#include "../../Model/Player.h"
#include "../../Model/Monster.h"
#include "../../Model/MonsterLine.h"
#include "../../View/LevelWindow.h"

using namespace std;

bool LevelParser::loadFile(string filename) {
	if(!doc.LoadFile(filename.c_str())){
		cerr << "Failed to load file: Bad XML" << endl;
		return false;
	}

	root = doc.FirstChildElement();
	if(root == NULL){
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
		return false;
	}
	return true;
}

const char* LevelParser::readAttributeCString(TiXmlElement* elem, const char* tag) {
	const char* Attribute = elem->Attribute(tag);
	if(Attribute == NULL){
		throw std::runtime_error("Failed to read attribute with tag '" + (std::string)tag  + "'.");
		return "";
	}
	return Attribute;
}

string LevelParser::readAttributeString(TiXmlElement* elem, const char* tag) {
	const char* Attribute = elem->Attribute(tag);
	if(Attribute == NULL){
		throw std::runtime_error("Failed to read attribute with tag '" + (std::string)tag  + "'.");
		return "";
	}
	return Attribute;
}

const char* LevelParser::readElementCString(TiXmlElement* elem, const char* tag) {
	TiXmlNode* node = elem->FirstChild();
	TiXmlText* text = node->ToText();
	if(text == NULL){
		throw std::runtime_error("Failed to read element with tag '" + (std::string)tag  + "'.");
		return "";
	}
	return text->Value();
}

string LevelParser::readElementString(TiXmlElement* elem, const char* tag) {
	TiXmlNode* node = elem->FirstChild();
	TiXmlText* text = node->ToText();
	if(text == NULL){
		throw std::runtime_error("Failed to read element with tag '" + (std::string)tag  + "'.");
		return "";
	}
	return text->Value();
}


bool LevelParser::parseLevel(std::string file_name, Level* level, LevelWindow* level_window) {
	// Load the XML file.
	if(!loadFile(file_name))
		return false;
	
	// Parse starting with the root.
	if(root != NULL){
		TiXmlElement* current_element = root->FirstChildElement();
		while(current_element != NULL) {
			std::string element_name = current_element->Value();
	
			if(element_name == "WINDOW") {
				// Change the window and level properties.
				int x_size = atoi(readAttributeCString(current_element, "x_size"));
				int y_size = atoi(readAttributeCString(current_element, "y_size"));
				int y_offset = atoi(readAttributeCString(current_element, "y_offset"));
				level_window->setSize(sf::Vector2u(x_size, y_size));
				level->setBounds(std::make_pair(x_size, y_size));
				level->setYOffset(y_offset);

				TiXmlElement* current_window_element = current_element->FirstChildElement();
				while(current_window_element != NULL) {
					std::string window_element_name = current_window_element->Value();
					if(window_element_name == "NAME"){
						level_window->setTitle(readElementString(current_window_element, "NAME"));
					}
					else if(window_element_name == "TEXTURE1"){
						// Set the window background.
						std::string file_name = readElementString(current_window_element, "TEXTURE1");
						level_window->addTexture(file_name);
						level_window->setBackground(level_window->getTextures().at(file_name));
					}

					current_window_element = current_window_element->NextSiblingElement();
				}
			}

			else if(element_name == "BULLET") {
				std::string file_path = readAttributeString(current_element, "texture");

				if(!level_window->addTexture(file_path, "bullet")){
					throw std::runtime_error("Invalid bullet texture.");
					return false;
				}
			}

			else if(element_name == "PLAYER") {
				// Create an observer for the player.
				Observer* player_observer = new Observer(level_window);

				// Player Location
				double x = atoi(readAttributeCString(current_element, "x"));
				double y = atoi(readAttributeCString(current_element, "y"));
				double collision_radius = atoi(readAttributeCString(current_element, "collision_radius"));
				double x_speed = atoi(readAttributeCString(current_element, "x_speed"));
				double y_speed = atoi(readAttributeCString(current_element, "y_speed"));

				// Player Texture
				TiXmlElement* child_element = current_element->FirstChildElement();
				if(child_element == NULL) {
					throw std::runtime_error("Invalid player texture.");
					return false;
				}
				std::string child_element_name = child_element->Value();
				if(child_element_name == "TEXTURE1") {
					if(!level_window->addTexture(readElementString(child_element, "TEXTURE"))){
						throw std::runtime_error("Invalid player texture.");
						return false;
					}
					try{
						player_observer->setTexture(level_window->getTextures().at(readElementString(child_element, "TEXTURE")));
					}catch(std::out_of_range){
						std::cerr << "Texture file not found. Terminating program." << std::endl;
						std::terminate();
					}
					
				}		
				else {
					throw std::runtime_error("Player texture not found.");
					return false;
				}
		
				// Add the player to the level.
				std::vector<Observer*> player_observers = {player_observer};
				Player* player = new Player(player_observers, x, y, collision_radius, x_speed, y_speed);
				level->addEntity(player);
				level->setPlayer(player);
			}

			else if(element_name == "MONSTERLINE") {
				std::list<Entity*> monsters;
				double x_speed = atoi(readAttributeCString(current_element, "x_speed"));
				double y_speed = atoi(readAttributeCString(current_element, "y_speed"));
				std::string initial_direction_str = readAttributeString(current_element, "initial_direction");
				Direction initial_direction = RIGHT;
				if(initial_direction_str == "LEFT")
					initial_direction = LEFT;

				TiXmlElement* current_monsterline_element = current_element->FirstChildElement();
				while(current_monsterline_element != NULL) {
					std::string cme_name = current_monsterline_element->Value();
					if(cme_name == "MONSTER") {
						// Create an observer for the monster.
						Observer* monster_observer = new Observer(level_window);

						// Monster Location
						double x = atoi(readAttributeCString(current_monsterline_element, "x"));
						double y = atoi(readAttributeCString(current_monsterline_element, "y"));
						double collision_radius = atoi(readAttributeCString(current_monsterline_element, "collision_radius"));

						// Monster Texture	
						TiXmlElement* cme_child_element = current_monsterline_element->FirstChildElement();
						if(cme_child_element == NULL) {
							throw std::runtime_error("Invalid monster texture.");
							return false;
						}
						std::string cme_child_element_name = cme_child_element->Value();
						if(cme_child_element_name == "TEXTURE1") {
							level_window->addTexture(readElementString(cme_child_element, "TEXTURE"));
							try{
								monster_observer->setTexture(level_window->getTextures().at(readElementString(cme_child_element, "TEXTURE")));
							}catch(std::out_of_range){
								std::cerr << "Texture file not found. Terminating program." << std::endl;
								std::terminate();
							}
						}		
						else {
							throw std::runtime_error("Monster texture was not found.");
							return false;
						}
						
						// Add the monster to list.
						std::vector<Observer*> monster_observers = {monster_observer};
						Monster* monster = new Monster(monster_observers, x, y, collision_radius, 0, 0);
						monsters.push_back(monster);
					}
					current_monsterline_element = current_monsterline_element->NextSiblingElement();
				}
				// Add the monster line to the level.
				MonsterLine* monster_line = new MonsterLine(initial_direction, x_speed, y_speed, level->getBounds().first, monsters);
				level->addEntity(monster_line);
			}

			current_element = current_element->NextSiblingElement();
		}
	}
	return true;
}
