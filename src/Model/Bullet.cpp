#include "Bullet.h"

Bullet::Bullet(std::vector<Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed) : Entity(obs, x_location, y_location, collision_radius, x_speed, y_speed){}

bool Bullet::move(double elapsed_time, double x_bound, double y_bound){
	double y_delta = _y_speed * elapsed_time;
	if(_y + y_delta > 0 && _y + y_delta < y_bound){
		_y += y_delta;

		std::vector<Observer*>::iterator observer_it;	
		for(observer_it = observers.begin(); observer_it != observers.end(); ++observer_it)
			(*observer_it)->notify(this, MOVE);

	}
	return true;
}

std::string Bullet::getType(){return "Bullet";}
