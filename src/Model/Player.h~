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
		 * Returns the type of the entity.
		 * @return The type of the entity.
		 */
		virtual std::string getType();
};

#endif /* PLAYER_H_ */
