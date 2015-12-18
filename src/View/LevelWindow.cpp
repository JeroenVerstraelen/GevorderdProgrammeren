#include <SFML/Graphics.hpp>
#include <map>
#include <utility>
#include <stdint.h>
#include <iostream>

#include "LevelWindow.h"

namespace si {

	LevelWindow::LevelWindow() : sf::RenderWindow() {}

	LevelWindow::LevelWindow(sf::VideoMode mode, const std::string& title, sf::Uint32 style, const sf::ContextSettings& settings) : sf::RenderWindow(mode, title, style, settings) {}

	LevelWindow::~LevelWindow() {
		/*
		std::map<std::string, sf::Texture*>::iterator map_iterator;	
		for(map_iterator = textures.begin(); map_iterator != textures.end(); ++map_iterator) {
			delete map_iterator->second;
			//background.setTexture(*map_iterator->second);
			map_iterator->second = nullptr;
		}
		*/
	}

	bool LevelWindow::addTexture(std::string file_path, std::string key) {
		//sf::Texture* texture = new sf::Texture();
		sf::Texture texture;
		if (!texture.loadFromFile(file_path))
			return false;
		if(key != "")
			file_path = key;
		textures.insert(std::pair<std::string, sf::Texture>(file_path, texture));
		return true;
	}

	void LevelWindow::setBackground(sf::Texture& background_texture) {
		background.setPosition(sf::Vector2f(0, -10000 + 1200));
		background.setTextureRect(sf::IntRect(0, 0, 1200, 10000));
		background_texture.setRepeated(true);
		background.setTexture(background_texture);
	}

	void LevelWindow::drawBackground() {
		double x = background.getPosition().x;
		double y = background.getPosition().y + 0.5;
		background.setPosition(sf::Vector2f(x, y));
		this->draw(background);
	
	}


	std::map<std::string, sf::Texture>& LevelWindow::getTextures() {
		return textures;
	}

}
