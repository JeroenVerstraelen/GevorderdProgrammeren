//==============================================================================================================================
// Name        : LevelController.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : Wraps the creation and user input for levels. Allows creation with XML files and performs a tick of the level.
//==============================================================================================================================

#ifndef LEVELCONTROLLER_H_
#define LEVELCONTROLLER_H_

#include <SFML/Graphics.hpp>
#include "../Model/Level.h"
#include "../View/LevelWindow.h"

class LevelController{
	private:
		/** 
		 * The current level being handled.
		 */
		Level* level = NULL;

		/** 
		 * The window used for the current level.
		 */
		LevelWindow* level_window = NULL;

		/** 
		 * The XML file name of the following level.
		 */
		std::string next_level = "NONE";

		/**
		 * Runs the current level.
		 * @param elapsed_time The amount of time (milliseconds) used for the previous game tick.
		 */
		bool tick(double elapsed_time);
		
	public:
		/**
		 * Constructor.
		 */
		LevelController(LevelWindow* lw);

		/**
		 * Default Destructor.
		 */
		~LevelController();

		/* 
		 * Starts the level. 
		 * @return Whether the level has started correctly.
		 */
		bool startLevel();

		/**
		 * Creates a level from an XML file.
		 * @param file The XML file to use.
		 * @return Whether the level has been succesfully created.
		 */
		bool loadLevel(std::string file);
};

#endif /* LEVELCONTROLLER_H_ */
