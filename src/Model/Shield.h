//==============================================================================================================================
// Name        : Shield.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : Represents a Shield in the game.
//==============================================================================================================================

#ifndef SHIELD_H_
#define SHIELD_H_

#include "Entity.h"

namespace si {

	class Shield : public Entity{
		private:
			unsigned int lives = 5;

		public:
			/** 
			 * Default Constructor.
			 */
			Shield();

			/** 
			 * Constructor.
			 * @param obs The vector of observers to use for this entity.
			 * @param x_location The location on the x_axis.
			 * @param y_location The location on the y_axis.
			 * @param collision_radius The radius that other entities can collide with.
			 * @param x_speed The speed the entity will move sideways.
			 * @param y_speed The speed the entity will move vertically.
			 */
			Shield(std::vector<Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed = 0);

			/** 
			 * Checks if the entity should be removed after a collission.
			 * @param entity The entity to check for.
		   	 * @param delete_other Whether to delete entity.
			 * @return Whether the entity should be deleted.
			 */
			virtual bool checkCollisionDeath(Entity* entity, bool& delete_other);
	};

}

#endif /* SHIELD_H_ */
