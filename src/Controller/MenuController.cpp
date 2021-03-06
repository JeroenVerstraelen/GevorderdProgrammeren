#include <iostream>

#include "MenuController.h"
#include "../Model/Bullet.h"
#include "../View/EntityObserver.h"

using namespace si;
using namespace si::controller;

MenuController::MenuController(view::LevelWindow* lw)  : _window(lw) {
	level = new model::Level(std::make_pair(lw->getSize().x, lw->getSize().y));
}

MenuController::~MenuController() {
	delete level;
	level = nullptr;

	for(auto entity : menu_entities) {
		delete entity;
		entity = nullptr;
	}
}

bool MenuController::loadSim() {
	// Load the entities for the simulation.
	LevelParser parser;
	std::string sim_file = "Resources/XMLDocuments/menu.xml";
	try {
		if(!parser.parseLevel(sim_file, level, _window)) {
			std::cerr << "Could not load the simulation." << std::endl;
		    	return false;
		}
	}catch(std::exception& e) {
		std::cerr << "Exception caught while loading level from XML file: " << e.what() << std::endl;
	    	std::terminate();
	}	
	return true;
}

bool MenuController::tick(StopWatch* stop_watch) {
	// The duration of the last tick.
	double elapsed_time = stop_watch->getPreviousTime();

	// The position of the mouse.
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*_window);

	// Handle user input.
	sf::Event event;
	while (_window->pollEvent(event))
	{
		switch (event.type)
		{
			// window closed
			case sf::Event::Closed:
		    		_window->close();
		    		break;

			// key pressed
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
		    			_window->close();
				}
				else if (event.key.code == sf::Keyboard::Space){
					// Default 1 second between each shot.
					if(stop_watch->getPlayerBulletTime() >= 250) {
						// Reset the bullet timer.
						stop_watch->resetPlayerBulletTime();
						// Shoot a bullet.
						view::Observer* bullet_observer = new view::EntityObserver(_window);
						try {
							bullet_observer->addTexture(_window->getTextures().at("bullet"));
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

			// Mouse pressed
			case sf::Event::MouseButtonPressed:
				if(event.mouseButton.button == sf::Mouse::Left) {
					for(auto entity : menu_entities) {
						if(entity->getType() == "Button") {
							model::Button* button = static_cast<model::Button*>(entity);
							double min_x = button->getLocation().first - (button->getCollisionBox().first/2);
							double max_x = button->getLocation().first + (button->getCollisionBox().first/2);
							double min_y = button->getLocation().second - (button->getCollisionBox().second/2);
							double max_y = button->getLocation().second + (button->getCollisionBox().second/2);

							if(mouse_pos.x > min_x && mouse_pos.x < max_x) {
								if(mouse_pos.y > min_y && mouse_pos.y < max_y) {
									return true;
								}
							}							
						}
					}
				}

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

	// Check if the button is being hovered over.
	for(auto entity : menu_entities) {
		if(entity->getType() == "Button") {
			model::Button* button = static_cast<model::Button*>(entity);
			double min_x = button->getLocation().first - (button->getCollisionBox().first/2);
			double max_x = button->getLocation().first + (button->getCollisionBox().first/2);
			double min_y = button->getLocation().second - (button->getCollisionBox().second/2);
			double max_y = button->getLocation().second + (button->getCollisionBox().second/2);

			if(mouse_pos.x > min_x && mouse_pos.x < max_x) {
				if(mouse_pos.y > min_y && mouse_pos.y < max_y) {
					button->switchHover(true);
					continue;
				}
			}
			button->switchHover(false);
		}
	}	

	// If the simulation has ended.
	model::LevelStatus end_status = level->tick(stop_watch);
	if(end_status == model::FAILURE) {
		// Restart the simulation.
		delete level;
		level = new model::Level(std::make_pair(_window->getSize().x, _window->getSize().y));
		loadSim();
	}
	else if(end_status == model::SUCCES) {
		// Reward the player.
		view::Observer* logo_observer = new view::EntityObserver(_window);
		try {
			logo_observer->addTexture(_window->getTextures().at("logo"));
		}catch(std::out_of_range) {
			std::cerr << "Logo texture file not found." << std::endl;
		}
		std::vector<view::Observer*> logo_observers = {logo_observer};
		model::Button* logo = new model::Button(logo_observers, 580, 110, 0, 0);
		menu_entities.push_back(logo);
	}

	// Draw the buttons.
	for(auto entity : menu_entities) 
		entity->notifyDraw();

	return false;
}

bool MenuController::start() {
	// Create the window.
	_window->create(sf::VideoMode(1200, 800), "Space Invaders");
	_window->setPosition(sf::Vector2i(0, 0));

	// Add the textures.
	_window->addTexture("Resources/Textures/playbutton.png", "playbutton");
	_window->addTexture("Resources/Textures/playbuttonhover.png", "playbuttonhover");
	_window->addTexture("Resources/Textures/logo.png", "logo");

	// Create the buttons that will be used.
	view::Observer* button_observer = new view::EntityObserver(_window);
	try {
		button_observer->addTexture(_window->getTextures().at("playbutton"));
		button_observer->addTexture(_window->getTextures().at("playbuttonhover"));
	}catch(std::out_of_range) {
		std::cerr << "Button texture file not found." << std::endl;
	}
	std::vector<view::Observer*> button_observers = {button_observer};
	model::Button* b1 = new model::Button(button_observers, 600, 400, 475, 50);

	// Create the logo.
	menu_entities.push_back(b1);

	// Load the simulation.
	if(!loadSim())
		return false;

	// The StopWatch responsible for running the game at the same speed.
	StopWatch* stop_watch = StopWatch::getInstance();

	// run the program as long as the window is open
	while (_window->isOpen())
	{
		// Reset the stop watch.
		stop_watch->reset();

		// clear the window with black color
		_window->clear(sf::Color::Black);

		// Run the menu.
		if(this->tick(stop_watch)) {
			stop_watch->fullReset();
			return true;
		}

		// end the current frame
		_window->display();
	}

	stop_watch->fullReset();
	return false;
}
