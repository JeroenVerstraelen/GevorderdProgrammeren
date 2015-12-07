#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>

#include "LevelController.h"
#include "parsers/LevelParser.h"
#include "../View/LevelWindow.h"
#include "../Model/Level.h"
#include "../Model/Entity.h"
#include "../Model/Player.h"
#include "../Model/Bullet.h"
#include "../Model/Monster.h"
#include "../Utils/StopWatch.h"


LevelController::LevelController(LevelWindow* lw) : level_window(lw){
	// Create a level with a default offset of 10% the y_bound.
	level = new Level(std::make_pair(lw->getSize().x, lw->getSize().y), 0.1 * lw->getSize().y);
}

LevelController::~LevelController(){
	delete level;
}

bool LevelController::startLevel(){
	// run the program as long as the window is open
	while (level_window->isOpen())
	{
		// Get the elapsed time between two iterations.
		double elapsed_time = StopWatch::getInstance().getElapsedTime();

		// Reset the stop watch to time the next iteration.
		StopWatch::getInstance().reset();

		// clear the window with black color
		level_window->clear(sf::Color::Black);

		// Run the created level.
		if(!this->tick(elapsed_time))
			level_window->close();

		// end the current frame
		level_window->display();
	}
	return true;
}

bool LevelController::tick(double elapsed_time){
	// Draw the background of the level.
	level_window->drawBackground();

	// Handle user input.
	sf::Event event;
	while (level_window->pollEvent(event))
	{
		switch (event.type)
		{
			// window closed
			case sf::Event::Closed:
		    		level_window->close();
		    		break;

			// key pressed
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape){
		    			level_window->close();
				}
				else if (event.key.code == sf::Keyboard::Space){
					// Shoot a bullet.
					Observer* bullet_observer = new Observer(level_window);
					bullet_observer->setTexture(level_window->getTextures().at("bullet"));
					std::vector<Observer*> bullet_observers = {bullet_observer};
					Bullet* bullet = new Bullet(bullet_observers, level->getPlayer()->getLocation().first, level->getPlayer()->getLocation().second, 10, 0.1, 0.1);
					level->addEntity(bullet);
				}
			    	break;

			// other events
			default:
		    		break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
   		level->getPlayer()->move(-3, 0, level->getBounds().first, level->getBounds().second);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    		level->getPlayer()->move(3, 0, level->getBounds().first, level->getBounds().second);
	}

	// Handle AI.
	return level->tick(elapsed_time);
}

bool LevelController::loadLevel(std::string file){
	LevelParser parser;
	try {
		parser.parseLevel(file, level, level_window);
	}catch(std::exception& e) {
		std::cerr << "Exception caught while loading level from XML file: " << e.what() << std::endl;
	}		

	return true;
}
