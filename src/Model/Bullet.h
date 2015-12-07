//============================================================================
// Name        : Bullet.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : A bullet model.
//============================================================================

#ifndef BULLET_H_
#define BULLET_H_

#include "Entity.h"

class Bullet : public Entity {

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
		Bullet(std::vector<Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed = 0);

		/** 
		 * Moves the Bullet using its own speed.
		 * @param x_bound The furthest Entity can move on the x-axis.
		 * @param y_bound The furthest Entity can move on the y-axis.
		 * @return Wether the bullet was destroyed in the move.
		 */
		virtual bool move(double elapsed_time, double x_bound, double y_bound);

		/** 
		 * Returns the type of the entity.
		 * @return The type of the entity.
		 */
		virtual std::string getType();
};


#endif /* BULLET_H_ */
