#include "Monster.h"
#include "Bullet.h"

#include "../View/Observer.h"
#include "../Utils/RandomGenerator.h"

namespace si {

	Monster::Monster(std::vector<Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed) 
		: Entity(obs, x_location, y_location, collision_radius, x_speed, y_speed) {}

	bool Monster::move(double x_delta, double y_delta, double x_bound, double y_bound) {
		if(_x + x_delta > 0 && _x + x_delta < x_bound && _y + y_delta > 0 && _y + y_delta < y_bound){

			_x += x_delta;
			_y += y_delta;

			std::vector<Observer*>::iterator observer_it;	
			for(observer_it = observers.begin(); observer_it != observers.end(); ++observer_it) {
				(*observer_it)->notify(this, MOVE);
				(*observer_it)->notify(this, ITERTEXTURE);
			}
		}
		return true;
	}

	std::string Monster::getType(){return "Monster";}

	std::vector<Observer*> Monster::notifyDestruct() {
		std::vector<Observer*> particle_observers;

		for(unsigned int i = 0; i < observers.size(); ++i) {
			Observer* particle_observer = observers[i]->notify(this, EXPLODE);	
			if(particle_observer != nullptr)
				particle_observers.push_back(particle_observer);
		}

		return particle_observers;
	}

	bool Monster::checkCollisionDeath(Entity* entity, bool& delete_other) {
		double other_x = entity->getLocation().first;
		double other_y = entity->getLocation().second;
		double other_collision_radius = entity->getCollisionRadius();

		// Check if the other entity is inside our collision radius.
		for(double check_x = other_x - other_collision_radius; check_x <= other_x + other_collision_radius; ++check_x){
			if(check_x > (_x - _collision_radius) && check_x < (_x + _collision_radius)) {
				for(double check_y = other_y - other_collision_radius; check_y <= other_y + other_collision_radius; ++check_y){
					if(check_y > (_y - _collision_radius) && check_y < (_y + _collision_radius)) { 	
						// Bullets from players are deadly!
						if(entity->getType() == "Bullet") {
							Bullet* bullet = static_cast<Bullet*>(entity);
							if(bullet->getSenderType() == "player") {
								delete_other = true;
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

}
