#include "Monster.h"

Monster::Monster(std::vector<Observer*> obs, double x_location, double y_location, double collision_radius, double x_speed, double y_speed) : Entity(obs, x_location, y_location, collision_radius, x_speed, y_speed){}

std::string Monster::getType(){return "Monster";}
