//============================================================================
// Name        : Level.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : Represents a level in a space invaders game.
//============================================================================

#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <utility>
#include "Entity.h"
#include "Player.h"
#include "ParticleGenerator.h"
#include "../Utils/StopWatch.h"

namespace si {
namespace model {

/*
 * Represents the current status of the level.
 */
enum LevelStatus { NORMAL, SUCCES, FAILURE};

class Level{
	private:
		/*
		 * Level properties
		 */
		std::pair<int, int> _bounds;

		/*
		 * Entities
		 */
		Player* _player = nullptr;
		std::vector<Entity*> _entities;

		/**
		 * Particle generators used in the level.
		 */
		std::vector<ParticleGenerator*> _particle_generators;

		/**
		 * The direction the monsters are currently moving in.
		 */
		bool _monster_moving_right = true;

		/**
		 * The speed of the monsters on the x-axis.
		 */
		double _x_monster_speed = 0;

		/**
		 * The speed of the monsters on the y-axis.
		 */
		double _y_monster_speed = 0;

		/**
		 * X-bound for the monsters.
		 */
		double _x_monster_limit = 0;

		/**
		 * Y-bound for the monsters.
		 */
		double _y_monster_limit = 0;

	public:

		/**
		 * Constructor.
		 * @param bounds The bounds of the level.
		 */
		Level(std::pair<double, double> bounds);

		/**
		 * Destructor.
		 */
		~Level();

		/**
		 * Performs all the game mechanics.
		 * @param stop_watch The stop_watch keeping track of the time between game ticks.
		 * @return The status of the level after the tick. 
		 */
		LevelStatus tick(StopWatch* stop_watch);

		/**
		 * Sets the current player of the level.
		 * @param player The player entity.
		 */
		void setPlayer(Player* player);

		/**
		 * Sets the bounds of the level.
		 * @param bounds The bounds to set.
		 */
		void setBounds(std::pair<double, double> bounds);

		/**
		 * Sets the AI for the monsters.
		 * @param x_speed The speed the monsters will move on the x-axis.
		 * @param y_speed The speed the monsters will move on the y-axis.
		 * @param x_limit The maximum x-value the monsters can have.
		 * @param y_limit The maximum y-value the monsters can have.
		 * @param moving_right Whether to start with the monsters moving right or left.
		 */
		void setMonsterAI(double x_speed, double y_speed, double x_limit, double y_limit, bool moving_right = true);

		/**
		 * Adds an entity to the level.
		 * @param entity The entity to add.
		 */
		void addEntity(Entity* entity);

		/**
		 * Returns all the monsters that are able to shoot.
		 * @return The monsters that are able to shoot.
		 */
		std::vector<Entity*> getMonstersCanShoot() const;

		/**
		 * Returns the player entity of the level.
		 * @return The player entity.
		 */
		Player* getPlayer() const;

		/**
		 * Returns the bounds of the level.
		 * @return The bounds of the level.
		 */
		std::pair<double, double> const getBounds() const;


		/**
		 * Returns entities used in the level.
		 * @return The entities used in the level.
		 */
		std::vector<Entity*> const& getEntities() const;
};

} // Namespace model
} // Namespace si
#endif /* LEVEL_H_ */
