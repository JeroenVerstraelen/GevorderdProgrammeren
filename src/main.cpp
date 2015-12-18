#include <SFML/Graphics.hpp>
#include <iostream>
#include "Controller/LevelController.h"
#include "Controller/MenuController.h"
#include "View/LevelWindow.h"


int main(int argc, char *argv[]){
	// Create the main window for the game.
	si::LevelWindow level_window;
	level_window.setPosition(sf::Vector2i(0, 0));

	// Default first level.
	std::string previous_level = "level1";
	std::string next_level = "level1";

	while(true) {
		// Create the controller for the menu.
		si::MenuController menu_controller(&level_window);

		// Start the menu and wait for it to finish.
		if(!menu_controller.start())
			break;

		// Create the controller for the level.
		si::LevelController level_controller(&level_window);	

		// Load the next level.
		if(!level_controller.loadLevel("Resources/XMLDocuments/" + next_level + ".xml"))
			continue;

		// Update the previous & next level.
		previous_level = next_level;
		next_level = level_controller.getNextLevel();

		// Start the level.
		si::LevelStatus end_status = level_controller.startLevel();

		// Handle the end of the level.
		switch(end_status){
			case si::SUCCES: 
				break;
			case si::FAILURE: 
				next_level = previous_level;
				break;
			default:
				return 0;
		}
	}
	return 0;
}
