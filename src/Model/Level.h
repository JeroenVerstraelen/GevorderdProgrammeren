//============================================================================
// Name        : Level.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : Represents a level in a space invaders game.
//============================================================================

#ifndef LEVEL_H_
#define LEVEL_H_

#include <list>
#include <utility>
#include "Entity.h"
#include "Player.h"

class Level{
	private:
		/*
		 * Level properties
		 */
		std::pair<int, int> _bounds;
		int _y_offset = 0;

		/*
		 * Entities
		 */
		Player* _player = nullptr;
		std::list<Entity*> _entities;


	public:

		/**
		 * Constructor.
		 * @param bounds The bounds of the level.
		 * @param y_offset Decides when the monsters reach the end.
		 */
		Level(std::pair<double, double> bounds, double y_offset);

		/**
		 * Destructor.
		 */
		~Level();
		
		/**
		 * Performs all the game mechanics.
		 * @param elapsed_time The amount of time (milliseconds) used for the previous game tick.
		 */
		bool tick(double elapsed_time);

		/**
		 * Sets the current player of the level.
		 * @param player The player entity.
		 */
		void setPlayer(Player* player);

		/**
		 * Sets the offset of the level.
		 * @param offset Decides when the monsters reach the end.
		 */
		void setYOffset(double offset);

		/**
		 * Sets the bounds of the level.
		 * @param bounds The bounds to set.
		 */
		void setBounds(std::pair<double, double> bounds);

		/**
		 * Adds an entity to the level.
		 * @param entity The entity to add.
		 */
		void addEntity(Entity* entity);

		/**
		 * Returns the player entity of the level.
		 * @return The player entity.
		 */
		Player* getPlayer() const;

		/**
		 * Returns the bounds of the level.
		 * @return The bounds of the level.
		 */
		std::pair<double, double> const& getBounds() const;
};

#endif /* LEVEL_H_ */
