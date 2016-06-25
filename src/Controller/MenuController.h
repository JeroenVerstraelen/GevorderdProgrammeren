//==============================================================================================================================
// Name        : MenuController.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : Wraps the creation and user input for a menu.
//==============================================================================================================================

#ifndef MENUCONTROLLER_H_
#define MENUCONTROLLER_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "parsers/LevelParser.h"
#include "../View/LevelWindow.h"
#include "../Model/Button.h"
#include "../Model/Entity.h"
#include "../Model/Level.h"
#include "../Utils/StopWatch.h"

namespace si {
namespace controller {

class MenuController {
	private:
		/** 
		 * The window used for the menu.
		 */
		view::LevelWindow* _window = NULL;

		/**
		 * A list of the buttons used in the menu.
		 */
		std::vector<model::Entity*> menu_entities;

		/** 
		 * The level sim being handled.
		 */
		model::Level* level = NULL;

		/** 
		 * Loads the simulation.
		 */
		bool loadSim();

		/**
		 * Performs a single tick on the menu.
		 * @param stop_watch The stop watch used to time the ticks.
		 * @return Whether the next game should start. 
		 */
		bool tick(StopWatch* stop_watch);

	public:
		/**
		 * Constructor.
		 */
		MenuController(view::LevelWindow* lw);

		/**
		 * Default Destructor.
		 */
		~MenuController();

		/* 
		 * Starts the menu.
		 * @return Whether the next game should start. 
		 */
		bool start();
};

} // Namespace controller
} // Namespace si

#endif /* MENUCONTROLLER_H_ */
