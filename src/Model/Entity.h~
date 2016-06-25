//============================================================================
// Name        : Entity.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : An Entity model.
//============================================================================

#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>
#include <utility>

#include "../View/Observer.h"

namespace si {

/** 
 * Forward declaration of Observer.
 */
namespace view {
	class Observer;
}

namespace model {

enum Direction { LEFT, RIGHT, UP, DOWN};

class Entity {
	protected:
		/** 
		 * The speed to move at on the x-axis.
		 */
		double _x_speed = 0;

		/** 
		 * The speed to move at on the y-axis.
		 */
		double _y_speed = 0;

		/** 
		 * Location on the x-axis.
		 */
		double _x = 0;

		/** 
		 * Location on the y-axis.
		 */
		double _y = 0;

		/** 
		 * The radius that other entities can collide with.
		 */
		double _collision_radius = 0;

		/** 
		 * Observers to be notified.
		 */
		std::vector<view::Observer*> observers;

   	public:

		/** 
		 * Default Constructor.
		 */
		Entity();

		/** 
		 * Constructor.
		 * @param obs The vector of observers to use for this entity.
		 * @param x_location The location on the x_axis.
		 * @param y_location The location on the y_axis.
		 * @param collision_radius The radius that other entities can collide with.
		 * @param x_speed The speed the entity will move sideways.
		 * @param y_speed The speed the entity will move vertically.
		 */
		Entity(std::vector<view::Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed = 0);

		/** 
		 * Destructor.
		 */
		virtual ~Entity();

		/** 
		 * Returns the type of the entity.
		 * @return The type of the entity.
		 */
		virtual std::string getType();

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
		 * Moves the Entity relative to its location.
		 * @param x_delta The x_value to add to its current x_location.
		 * @param y_delta The y_value to add to its current y_location.
		 * @param x_bound The furthest Entity can move on the x-axis.
		 * @param y_bound The furthest Entity can move on the y-axis.
		 * @return Wether the move was succesfull.
		 */
		virtual bool move(double x_delta, double y_delta, double x_bound, double y_bound);

		/** 
		 * Checks if the entity should be removed after a collission.
		 * @param entity The entity to check for.
	   	 * @param delete_other Whether to delete entity.
		 * @return Whether the entity should be deleted.
		 */
		virtual bool checkCollisionDeath(Entity* entity, bool& delete_other);

		/** 
		 * Moves the Entity to an absolute location.
		 * @param x_location The location on the x_axis.
		 * @param y_location The location on the y_axis.
		 * @return Wether the relocation was succesfull.
	 	 */
		virtual bool setLocation(double x_location, double y_location);

		/** 
		 * Notify the observers that the Entity needs to be drawn.
		 */
		virtual void notifyDraw();

		/** 
		 * Notify the observers that the Entity will be destructed.
		 * @return May return a list of ParticleObservers.
		 */
		virtual std::vector<view::Observer*> notifyDestruct();

		/** 
		 * Returns the current location of the Entity.
		 * @return The current location of the Entity (x,y).
		 */
		virtual std::pair<double, double> getLocation() const;

		/** 
		 * Returns the collision radius of the entity.
		 * @return The collision radius of the entity.
		 */
		virtual double getCollisionRadius() const;

		/** 
		 * Returns the observers of the entity.
		 * @return The observers of the entity.
		 */
		virtual std::vector<view::Observer*> getObservers() const;
};

} // Namespace model
} // Namespace si
#endif /* ENTITY_H_ */
