#include <SFML/Graphics.hpp>
#include <map>
#include <utility>
#include <stdint.h>

#include "LevelWindow.h"

//LevelWindow::LevelWindow(sf::VideoMode vm, std::string title) : sf::RenderWindow(vm, title){}

LevelWindow::LevelWindow(sf::VideoMode mode, const std::string& title, sf::Uint32 style, const sf::ContextSettings& settings) : sf::RenderWindow(mode, title, style, settings){}

LevelWindow::~LevelWindow(){
	std::map<std::string, sf::Texture*>::iterator map_iterator;	
	for(map_iterator = textures.begin(); map_iterator != textures.end(); ++map_iterator)
		delete map_iterator->second;
}

bool LevelWindow::addTexture(std::string file_path, std::string key){
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(file_path))
		return false;
	if(key != "")
		file_path = key;
	textures.insert(std::pair<std::string, sf::Texture*>(file_path, texture));
	return true;
}

void LevelWindow::setBackground(sf::Texture* background_texture){
	background.setTexture(*background_texture);
}

void LevelWindow::drawBackground(){
	this->draw(background);
}


std::map<std::string, sf::Texture*> const& LevelWindow::getTextures() const{
	return textures;
}
