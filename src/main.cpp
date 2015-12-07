#include "Controller/LevelController.h"
#include <SFML/Graphics.hpp>
#include "View/LevelWindow.h"
#include <iostream>


int main(int argc, char *argv[]){
	if(argc == 2){
		// Create the window.
		LevelWindow level_window(sf::VideoMode(1200, 800), "Space Invaders");
		level_window.setPosition(sf::Vector2i(0, 0));

		// Create the main Game.
		LevelController level_controller(&level_window);
		level_controller.loadLevel("Resources/XMLDocuments/" + (std::string)argv[1] + ".xml");

		// Start the main Game.
		level_controller.startLevel();
	}
	else{
		std::cout << "./[program name] [XMLfile]" << std::endl;
	}
	return 0;
}
