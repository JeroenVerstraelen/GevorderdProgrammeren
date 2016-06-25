#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>

#include "LevelParser.h"
#include "../../Model/Level.h"
#include "../../Model/Player.h"
#include "../../Model/Shield.h"
#include "../../Model/Monster.h"
#include "../../View/LevelWindow.h"
#include "../../View/EntityObserver.h"

using namespace si;
using namespace si::controller;

bool LevelParser::loadFile(std::string filename) {
	if(!doc.LoadFile(filename.c_str())){
		std::cerr << "Failed to load file: Bad XML" << std::endl;
		return false;
	}

	root = doc.FirstChildElement();
	if(root == NULL){
		std::cerr << "Failed to load file: No root element." << std::endl;
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

std::string LevelParser::readAttributeString(TiXmlElement* elem, const char* tag) {
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

std::string LevelParser::readElementString(TiXmlElement* elem, const char* tag) {
	TiXmlNode* node = elem->FirstChild();
	TiXmlText* text = node->ToText();
	if(text == NULL){
		throw std::runtime_error("Failed to read element with tag '" + (std::string)tag  + "'.");
		return "";
	}
	return text->Value();
}


bool LevelParser::parseLevel(std::string& file_name, model::Level* level, view::LevelWindow* level_window) {
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
				file_name = readAttributeString(current_element, "next_level");
				level_window->setSize(sf::Vector2u(x_size, y_size));
				level->setBounds(std::make_pair(x_size, y_size));

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
				view::Observer* player_observer = new view::EntityObserver(level_window);

				// Player Location
				double x = std::stod(readAttributeString(current_element, "x"));
				double y = std::stod(readAttributeString(current_element, "y"));
				double collision_radius = std::stod(readAttributeString(current_element, "collision_radius"));
				double x_speed = std::stod(readAttributeString(current_element, "x_speed"));
				double y_speed = std::stod(readAttributeString(current_element, "y_speed"));

				// Player Texture
				TiXmlElement* child_element = current_element->FirstChildElement();
				if(child_element == NULL) {
					throw std::runtime_error("Invalid player texture.");
					return false;
				}
				std::string child_element_name = child_element->Value();
				if(child_element_name == "TEXTURE1") {
					if(!level_window->addTexture(readElementString(child_element, "TEXTURE"), "player")){
						throw std::runtime_error("Invalid player texture.");
						return false;
					}
					try{
						player_observer->addTexture(level_window->getTextures().at("player"));
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
				std::vector<view::Observer*> player_observers = {player_observer};
				model::Player* player = new model::Player(player_observers, x, y, collision_radius, x_speed, y_speed);
				level->addEntity(player);
				level->setPlayer(player);
			}

			else if(element_name == "MONSTERAI") {
				double x_speed = std::stod(readAttributeString(current_element, "x_speed"));
				double y_speed = std::stod(readAttributeString(current_element, "y_speed"));
				double x_limit = std::stod(readAttributeString(current_element, "x_limit"));
				double y_limit = std::stod(readAttributeString(current_element, "y_limit"));
				std::string initial_direction_str = readAttributeString(current_element, "initial_direction");
				double moving_right = true;
				if(initial_direction_str == "LEFT") 
					moving_right = false;
				level->setMonsterAI(x_speed, y_speed, x_limit, y_limit, moving_right);
			}

			else if(element_name == "MONSTER") {
				// Create an observer for the monster.
				view::Observer* monster_observer = new view::EntityObserver(level_window);

				// Monster Location
				double x = std::stod(readAttributeString(current_element, "x"));
				double y = std::stod(readAttributeString(current_element, "y"));
				double collision_radius = std::stod(readAttributeString(current_element, "collision_radius"));

				// Monster Texture	
				TiXmlElement* current_monster_element = current_element->FirstChildElement();
				while(current_monster_element != NULL) {
					std::string monster_element_name = current_monster_element->Value();
					if(monster_element_name == "TEXTURE1"){
						level_window->addTexture(readElementString(current_monster_element, "TEXTURE1"));
						try{
							monster_observer->addTexture(level_window->getTextures().at(readElementString(current_monster_element, "TEXTURE1")));
						}catch(std::out_of_range){
							std::cerr << "Texture file not found. Terminating program." << std::endl;
							std::terminate();
						}
					}
					if(monster_element_name == "TEXTURE2"){
						level_window->addTexture(readElementString(current_monster_element, "TEXTURE2"));
						try{
							monster_observer->addTexture(level_window->getTextures().at(readElementString(current_monster_element, "TEXTURE2")));
						}catch(std::out_of_range){
							std::cerr << "Texture file not found. Terminating program." << std::endl;
							std::terminate();
						}
					}

					current_monster_element = current_monster_element->NextSiblingElement();
				}
			
				// Add the monster to the level.
				std::vector<view::Observer*> monster_observers = {monster_observer};
				model::Monster* monster = new model::Monster(monster_observers, x, y, collision_radius, 0, 0);
				level->addEntity(monster);
			}

			else if(element_name == "SHIELD") {
				view::Observer* shield_observer = new view::EntityObserver(level_window);

				// Shield Location
				double x = std::stod(readAttributeString(current_element, "x"));
				double y = std::stod(readAttributeString(current_element, "y"));
				double collision_radius = std::stod(readAttributeString(current_element, "collision_radius"));

				// Shield Texture.
				TiXmlElement* current_shield_element = current_element->FirstChildElement();
				while(current_shield_element != NULL) {
					std::string shield_element_name = current_shield_element->Value();
					if(shield_element_name == "TEXTURE1"){
						level_window->addTexture(readElementString(current_shield_element, "TEXTURE1"));
						try{
							shield_observer->addTexture(level_window->getTextures().at(readElementString(current_shield_element, "TEXTURE1")));
						}catch(std::out_of_range){
							std::cerr << "Texture file not found. Terminating program." << std::endl;
							std::terminate();
						}
					}
					if(shield_element_name == "TEXTURE2"){
						level_window->addTexture(readElementString(current_shield_element, "TEXTURE2"));
						try{
							shield_observer->addTexture(level_window->getTextures().at(readElementString(current_shield_element, "TEXTURE2")));
						}catch(std::out_of_range){
							std::cerr << "Texture file not found. Terminating program." << std::endl;
							std::terminate();
						}
					}
					if(shield_element_name == "TEXTURE3"){
						level_window->addTexture(readElementString(current_shield_element, "TEXTURE3"));
						try{
							shield_observer->addTexture(level_window->getTextures().at(readElementString(current_shield_element, "TEXTURE3")));
						}catch(std::out_of_range){
							std::cerr << "Texture file not found. Terminating program." << std::endl;
							std::terminate();
						}
					}
					if(shield_element_name == "TEXTURE4"){
						level_window->addTexture(readElementString(current_shield_element, "TEXTURE4"));
						try{
							shield_observer->addTexture(level_window->getTextures().at(readElementString(current_shield_element, "TEXTURE4")));
						}catch(std::out_of_range){
							std::cerr << "Texture file not found. Terminating program." << std::endl;
							std::terminate();
						}
					}
					if(shield_element_name == "TEXTURE5"){
						level_window->addTexture(readElementString(current_shield_element, "TEXTURE5"));
						try{
							shield_observer->addTexture(level_window->getTextures().at(readElementString(current_shield_element, "TEXTURE5")));
						}catch(std::out_of_range){
							std::cerr << "Texture file not found. Terminating program." << std::endl;
							std::terminate();
						}
					}

					current_shield_element = current_shield_element->NextSiblingElement();
				}
			
				// Add the shield to the level.
				std::vector<view::Observer*> shield_observers = {shield_observer};
				model::Shield* shield = new model::Shield(shield_observers, x, y, collision_radius, 0, 0);
				level->addEntity(shield);				
			}

			current_element = current_element->NextSiblingElement();
		}
	}
	return true;
}
