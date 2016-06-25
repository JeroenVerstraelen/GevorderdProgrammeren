#include "Bullet.h"

using namespace si;
using namespace si::model;

Bullet::Bullet(std::vector<view::Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed) 
	       : Entity(obs, x_location, y_location, collision_radius, x_speed, y_speed) {}

bool Bullet::move(double elapsed_time, double x_bound, double y_bound, Direction direction) {
	double y_delta = _y_speed * elapsed_time;
	if(_y + y_delta > 0 && _y + y_delta < 2 * y_bound) {
		_y += y_delta;

		std::vector<view::Observer*>::iterator observer_it;	
		for(observer_it = observers.begin(); observer_it != observers.end(); ++observer_it)
			(*observer_it)->notify(this, view::MOVE);
		return true;
	}
	return false;
}

bool Bullet::checkCollisionDeath(Entity* entity, bool& delete_other) {
	return false;
}

void Bullet::setSenderType(std::string sender_type) {
	_sender_type = sender_type;
}

std::string Bullet::getSenderType() {
	return _sender_type;
}


std::string Bullet::getType() {return "Bullet";}

