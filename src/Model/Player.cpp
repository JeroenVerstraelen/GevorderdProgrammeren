#include "Player.h"
#include "Bullet.h"

namespace si {

	Player::Player(std::vector<Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed) 
		: Entity(obs, x_location, y_location, collision_radius, x_speed, y_speed){}

	bool Player::move(double elapsed_time, double x_bound, double y_bound, Direction direction){
		double x_delta = 0;
		if(direction == RIGHT){
			 x_delta = _x_speed * elapsed_time;
		}
		else if(direction == LEFT) {
			x_delta = -(_x_speed * elapsed_time);
		}
		if(_x + x_delta > 0 && _x + x_delta < x_bound - (2 * _collision_radius)) {
			_x += x_delta;

			std::vector<Observer*>::iterator observer_it;	
			for(observer_it = observers.begin(); observer_it != observers.end(); ++observer_it)
				(*observer_it)->notify(this, MOVE);
			return true;
		}
		return false;
	}

	bool Player::checkCollisionDeath(Entity* entity, bool& delete_other) {
		double other_x = entity->getLocation().first;
		double other_y = entity->getLocation().second;
		double other_collision_radius = entity->getCollisionRadius();

		// Check if the other entity is inside our collision radius.
		for(double check_x = other_x - other_collision_radius; check_x <= other_x + other_collision_radius; ++check_x){
			if(check_x > (_x - _collision_radius) && check_x < (_x + _collision_radius)) {
				for(double check_y = other_y - other_collision_radius; check_y <= other_y + other_collision_radius; ++check_y){
					if(check_y > (_y - _collision_radius) && check_y < (_y + _collision_radius)) { 	
						// Bullets from monsters are deadly!
						if(entity->getType() == "Bullet") {
							Bullet* bullet = static_cast<Bullet*>(entity);
							if(bullet->getSenderType() == "monster")
								return false;
						}
					}
				}
			}
		}
		return false;
	}

	std::string Player::getType(){return "Player";}

}
