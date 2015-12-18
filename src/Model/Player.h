//============================================================================
// Name        : Player.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : A player model.
//============================================================================

#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <utility>

#include "Entity.h"
#include "../View/Observer.h"

namespace si {

	class Player : public Entity{
		public:
			/** 
			 * Constructor.
			 * @param obs The vector of observers to use for this entity.
			 * @param x_location The location on the x_axis.
			 * @param y_location The location on the y_axis.
			 * @param collision_radius The radius that other entities can collide with.
			 * @param x_speed The speed the entity will move sideways.
			 * @param y_speed The speed the entity will move vertically.
			 */
			Player(std::vector<Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed = 0);

			/**
			 * Moves the entity using its own AI.
			 * @param elapsed_time The amount of time (milliseconds) used for the previous game tick.
			 * @param direction The direction the entity will go in.
			 * @param x_bound The maximum x_value.
			 * @param y_bound The maximum y_value.
			 * @return Whether the line has reached the maximum y-value.
			 */
			virtual bool move(double elapsed_time, double x_bound, double y_bound, Direction direction = RIGHT);

			/** 
			 * Checks if the entity should be removed after a collission.
			 * @param entity The entity to check for.
		   	 * @param delete_other Whether to delete entity.
			 * @return Whether the entity should be deleted.
			 */
			virtual bool checkCollisionDeath(Entity* entity, bool& delete_other);

			/** 
			 * Returns the type of the entity.
			 * @return The type of the entity.
			 */
			virtual std::string getType();
	};

}

#endif /* PLAYER_H_ */
