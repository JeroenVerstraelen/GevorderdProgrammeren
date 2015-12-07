#include <SFML/Graphics.hpp>
#include <vector>

#include "Entity.h"
#include "../View/Observer.h"


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


bool Entity::checkCollisionDeath(Entity* entity){
	double other_x = entity->getLocation().first;
	double other_y = entity->getLocation().second;
	// Check if the other entity is inside our collision radius.
	if(other_x > (_x - _collision_radius) && other_x < (_x + _collision_radius)) {
		if(other_y > (_y - _collision_radius) && other_y < (_y + _collision_radius)) { 	
			// Bullets are deadly!
			if(entity->getType() == "Bullet")
				return true;
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

std::pair<double, double> Entity::getLocation() const {
	return std::make_pair(_x, _y);
}
