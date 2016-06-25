#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>

#include "LevelController.h"
#include "parsers/LevelParser.h"
#include "../View/LevelWindow.h"
#include "../View/EntityObserver.h"
#include "../Model/Level.h"
#include "../Model/Entity.h"
#include "../Model/Player.h"
#include "../Model/Bullet.h"
#include "../Model/Monster.h"
#include "../Utils/StopWatch.h"
#include "../Utils/RandomGenerator.h"

using namespace si;
using namespace si::controller;

LevelController::LevelController(view::LevelWindow* lw) : level_window(lw){
	// Create a level with a default offset of 10% the y_bound.
	level = new model::Level(std::make_pair(lw->getSize().x, lw->getSize().y));
}

LevelController::~LevelController(){
	delete level;
}

model::LevelStatus LevelController::startLevel(){
	// The StopWatch responsible for running the game at the same speed.
	StopWatch* stop_watch = StopWatch::getInstance();

	// run the program as long as the window is open
	while (level_window->isOpen())
	{
		// Reset the stop watch.
		stop_watch->reset();

		// clear the window with black color
		level_window->clear(sf::Color::Black);

		// Run the created level.
		model::LevelStatus current_status = this->tick(stop_watch);
		if(current_status != model::NORMAL) {
			level_window->close();
			return current_status;
		}

		// end the current frame
		level_window->display();
	}

	return model::NORMAL;
}

model::LevelStatus LevelController::tick(StopWatch* stop_watch){
	// The duration of the last tick.
	double elapsed_time = stop_watch->getPreviousTime();

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
					// Default 1 second between each shot.
					if(stop_watch->getPlayerBulletTime() >= 1000) {
						// Reset the bullet timer.
						stop_watch->resetPlayerBulletTime();
						// Shoot a bullet.
						view::Observer* bullet_observer = new view::EntityObserver(level_window);
						try {
							bullet_observer->addTexture(level_window->getTextures().at("bullet"));
						}catch(std::out_of_range) {
							std::cerr << "Bullet texture file not found." << std::endl;
						}
						std::vector<view::Observer*> bullet_observers = {bullet_observer};
						model::Bullet* bullet = new model::Bullet(bullet_observers, level->getPlayer()->getLocation().first, 
											  level->getPlayer()->getLocation().second + 32, 16, 0, -1);
						bullet->setSenderType("player");
						level->addEntity(bullet);
					}
				}
			    	break;

			// other events
			default:
		    		break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
   		level->getPlayer()->move(elapsed_time, level->getBounds().first, level->getBounds().second, model::LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    		level->getPlayer()->move(elapsed_time, level->getBounds().first, level->getBounds().second, model::RIGHT);
	}

	// Let the monsters shoot a bullet.
	RandomGenerator* rand_gen = RandomGenerator::getInstance();
	int rand_timer = rand_gen->getRandomInt(1000, 5000);
	if(stop_watch->getMonsterBulletTime() > rand_timer) {
		// Reset the timer for next time.
		stop_watch->resetMonsterBulletTime();

		// Create the bullet to shoot.
		view::Observer* bullet_observer = new view::EntityObserver(level_window);
		try {
			bullet_observer->addTexture(level_window->getTextures().at("bullet"));
		}catch(std::out_of_range) {
			std::cerr << "Bullet texture file not found." << std::endl;
		}
		std::vector<view::Observer*> bullet_observers = {bullet_observer};
		model::Bullet* bullet = new model::Bullet(bullet_observers, 0, 0, 16, 0, 1);
		bullet->setSenderType("monster");
	
		// Get the lists of monsters that are able to shoot.
		std::vector<model::Entity*> monsters_can_shoot = level->getMonstersCanShoot();

		// Generate a random index and shoot the bullet.
		int r_index = rand_gen->getRandomInt(0, monsters_can_shoot.size() - 1);	
		double monster_x = monsters_can_shoot[r_index]->getLocation().first;
		double monster_y = monsters_can_shoot[r_index]->getLocation().second; 
		bullet->setLocation(monster_x, monster_y);		
		level->addEntity(bullet);	
	}

	// Handle AI.
	return level->tick(stop_watch);
}

bool LevelController::loadLevel(std::string file) {
	// Create the window.
	level_window->create(sf::VideoMode(1200, 800), "Space Invaders");
	level_window->setPosition(sf::Vector2i(0, 0));

	LevelParser parser;
	try {
		if(!parser.parseLevel(file, level, level_window)) {
			std::cerr << "Could not load the next level." << std::endl;
		    	return false;
		}
	}catch(std::exception& e) {
		std::cerr << "Exception caught while loading level from XML file: " << e.what() << std::endl;
	    	std::terminate();
	}	
	next_level = file;

	return true;
}

std::string LevelController::getNextLevel() const {
	return next_level;
}
