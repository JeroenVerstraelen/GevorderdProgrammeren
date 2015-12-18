#include <SFML/Graphics.hpp>
#include <vector>

#include "Entity.h"
#include "../View/Observer.h"

namespace si {

	Entity::Entity(){}

	Entity::Entity(std::vector<Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed) : observers(obs), _x(x_location), _y(y_location),
		      _collision_radius(collision_radius), _x_speed(x_speed), _y_speed(y_speed) 
	{
		// Add the observers.
		std::vector<Observer*>::iterator observer_it;	
		for(observer_it = observers.begin(); observer_it != observers.end(); ++observer_it)
			(*observer_it)->notify(this, MOVE);
	}

	Entity::~Entity(){
		// Delete the observers from the heap.
		std::vector<Observer*>::iterator observer_it;	
		for(observer_it = observers.begin(); observer_it != observers.end(); ++observer_it)
			delete (*observer_it);
	}

	std::string Entity::getType(){
		return "Entity";
	}

	bool Entity::move(double elapsed_time, double x_bound, double y_bound, Direction direction){return true;}

	bool Entity::move(double x_delta, double y_delta, double x_bound, double y_bound){
		if(_x + x_delta > 0 && _x + x_delta < x_bound && _y + y_delta > 0 && _y + y_delta < y_bound){

			_x += x_delta;
			_y += y_delta;

			std::vector<Observer*>::iterator observer_it;	
			for(observer_it = observers.begin(); observer_it != observers.end(); ++observer_it)
				(*observer_it)->notify(this, MOVE);

		}
		return true;
	}


	bool Entity::checkCollisionDeath(Entity* entity, bool& delete_other){
		double other_x = entity->_x;
		double other_y = entity->_y;
		double other_collision_radius = entity->_collision_radius;

		// Check if the other entity is inside our collision radius.
		for(double check_x = other_x - other_collision_radius; check_x <= other_x + other_collision_radius; ++check_x){
			if(check_x > (_x - _collision_radius) && check_x < (_x + _collision_radius)) {
				for(double check_y = other_y - other_collision_radius; check_y <= other_y + other_collision_radius; ++check_y){
					if(check_y > (_y - _collision_radius) && check_y < (_y + _collision_radius)) { 	
						// Bullets are deadly!
						if(entity->getType() == "Bullet")
							return true;
					}
				}
			}
		}
		return false;
	}

	bool Entity::setLocation(double x_location, double y_location){
		_x = x_location;
		_y = y_location;

		// Notify the observers of this move.
		std::vector<Observer*>::iterator observer_it;	
		for(observer_it = observers.begin(); observer_it != observers.end(); ++observer_it)
			(*observer_it)->notify(this, MOVE);
		return true;
	}

	void Entity::notifyDraw(){
		std::vector<Observer*>::iterator observer_it;	
		for(observer_it = observers.begin(); observer_it != observers.end(); ++observer_it)
			(*observer_it)->notify(this, DRAW);
	}

	std::vector<Observer*> Entity::notifyDestruct() {
		std::vector<Observer*> empty;	
		return empty;
	}

	std::pair<double, double> Entity::getLocation() const {
		return std::make_pair(_x, _y);
	}

	double Entity::getCollisionRadius() const {
		return _collision_radius;
	}

	std::vector<Observer*> Entity::getObservers() const {
		return observers;
	}

}
