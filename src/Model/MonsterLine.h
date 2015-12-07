//============================================================================
// Name        : MonsterLine.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : Represents a line of monsters as an entity.
//============================================================================

#include <vector>
#include "Entity.h"
#include <list>
enum Direction { LEFT, RIGHT };

class MonsterLine : public Entity{
	private:

		/**
		 * The size of the MonsterLine.
		 */
		double _line_size = 0;

		/**
		 * This x value only goes up.
		 */
		double _total_x = 0;

		/**
		 * The entities in the monster line.
		 */
		std::list<Entity*> _monsters;

		/**
		 * The initial direction.
		 */
		Direction _direction = RIGHT;

		/**
		 * Recalculates the size of the MonsterLine.
		 */
		void recalculateLineSize();

	public:

		/**
		 * Constructs an instance of MonsterLine.
		 * @param direction The direction to move on the x-axis.
		 * @param x_speed The speed the entity will move sideways.
		 * @param y_speed The speed the entity will move vertically.
		 * @param x_bound The bound on the x_axis.
		 * @param monsters The monsters that are in the monster line.
		 */
		MonsterLine(Direction direction, double x_speed, double y_speed, double x_bound, std::list<Entity*> monsters);

		/**
		 * Destructor
		 */
		~MonsterLine();

		/**
		 * Adds an entity to the line.
		 * @param entity The entity to add.
		 */
		void addMonster(Entity* entity);

		/**
		 * Deletes an entity from the line.
		 * @param entity The entity to remove.
		 * @return Returns true if the line is empty.
		 */
		bool deleteMonster(Entity* entity);

		/** 
		 * Returns the type of the entity.
		 * @return The type of the entity.
		 */
		std::string getType();

		/**
		 * Moves the entire monster line with the given speed.
		 * @param elapsed_time The amount of time used for the previous game tick.
		 * @param x_bound The maximum x_value.
		 * @param y_bound The maximum y_value.
		 * @return Whether the line has reached the maximum y-value.
		 */
		virtual bool move(double elapsed_time, double x_bound, double y_bound);

		/** 
		 * Checks if the entity should be removed after a collission.
		 * @param entity The entity to check for.
		 * @return Whether the entity should be deleted.
		 */
		virtual bool checkCollisionDeath(Entity* entity);

		/** 
		 * Notify the observers that the Entity needs to be drawn.
		 */
		virtual void notifyDraw();
};
