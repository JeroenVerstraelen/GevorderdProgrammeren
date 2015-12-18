//============================================================================
// Name        : Monster.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : A monster model.
//============================================================================

#ifndef MONSTER_H_
#define MONSTER_H_

#include "Entity.h"
#include "Bullet.h"

namespace si {

	class Monster : public Entity{
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
			Monster(std::vector<Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed = 0);

			/** 
			 * Moves the Entity relative to its location.
			 * @param x_delta The x_value to add to its current x_location.
			 * @param y_delta The y_value to add to its current y_location.
			 * @param x_bound The furthest Entity can move on the x-axis.
			 * @param y_bound The furthest Entity can move on the y-axis.
			 * @return Wether the move was succesfull.
			 */
			virtual bool move(double x_delta, double y_delta, double x_bound, double y_bound);

			/** 
			 * Returns the type of the entity.
			 * @return The type of the entity.
			 */
			virtual std::string getType();

			/** 
			 * Notify the observers that the monster will be destructed.
			 * @return May return a list of ParticleObservers.
			 */
			virtual std::vector<Observer*> notifyDestruct();

			/** 
			 * Checks if the entity should be removed after a collission.
			 * @param entity The entity to check for.
		   	 * @param delete_other Whether to delete entity.
			 * @return Whether the entity should be deleted.
			 */
			virtual bool checkCollisionDeath(Entity* entity, bool& delete_other);
	};

}
#endif /* MONSTER_H_ */
