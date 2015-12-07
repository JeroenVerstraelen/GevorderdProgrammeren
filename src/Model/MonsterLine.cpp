#include <limits>
#include <list>
#include <algorithm>
#include <stdlib.h> 
#include <stdexcept>
#include "MonsterLine.h"
#include "Entity.h"

MonsterLine::MonsterLine(Direction direction, double x_speed, double y_speed, double x_bound, std::list<Entity*> monsters) : _direction(direction), 
			_monsters(monsters)
{
	_x_speed = x_speed;
	_y_speed = y_speed;
	double max_x = 0;
	double min_x = std::numeric_limits<double>::infinity();
	for(auto &monster : _monsters) {
		if(monster->getLocation().first > max_x) {
			max_x = monster->getLocation().first;
		}
		if(monster->getLocation().first < min_x) {
			min_x = monster->getLocation().first;
		}
	}

	// Calculate the size of the line.
	_line_size = max_x - min_x;
	
	// Calculate current x value.
	if(direction == RIGHT) {
		_total_x = max_x;
		return;
	} 
	_total_x = min_x + x_bound;
}

MonsterLine::~MonsterLine(){
	for(auto &monster: _monsters)
		delete monster;
}


void MonsterLine::recalculateLineSize(){
	double max_x = 0;
	double min_x = std::numeric_limits<double>::infinity();
	for(auto &monster : _monsters) {
		if(monster->getLocation().first > max_x) {
			max_x = monster->getLocation().first;
		}
		if(monster->getLocation().first < min_x) {
			min_x = monster->getLocation().first;
		}
	}

	// Calculate the size of the line.
	_line_size = max_x - min_x;
}

void MonsterLine::addMonster(Entity* monster) {
	_monsters.push_back(monster);
	recalculateLineSize();
}

bool MonsterLine::deleteMonster(Entity* entity) {
	std::list<Entity*>::iterator it = std::find(_monsters.begin(), _monsters.end(), entity);
	if(it != _monsters.end()){
		_monsters.erase(it);
		delete entity;
		recalculateLineSize();
	}

	return _monsters.empty();
}

std::string MonsterLine::getType(){
	return "MonsterLine";
}

bool MonsterLine::move(double elapsed_time, double x_bound, double y_bound) {
	if(_line_size > x_bound)
		throw std::runtime_error("Monster line is larger than bounds.");

	// The amount to move each monster on the x-axis.
	double x_delta = (_x_speed * elapsed_time);

	// Calculate location on screen.
	int current_multiple = (_total_x / x_bound); 
	_total_x += x_delta;
	int next_multiple = (_total_x / x_bound);

	// Temp gets the first say in if we move left or right.
	double temp = 0;
	if(next_multiple % 2 == 1){
		temp = x_bound - _line_size;
		x_delta = -x_delta;
	}
	// New_x is the actual location of the leftmost or rightmost
	// entity depending on the direction we're moving.
	double new_x = abs(temp - (_total_x - (next_multiple * x_bound)));

	// If the leftmost entity goes beyond the bounds, move to the right.
	if(new_x < 0)
		x_delta = -x_delta;
		

	// If we go past the screen, move down.
	if(current_multiple != next_multiple or new_x < 0){
		for(auto &monster : _monsters)
			monster->move(0, _y_speed, x_bound, y_bound);
		if(_monsters.front()->getLocation().second >= y_bound){
			// Level has ended.
			return true;	
		}
	}

	// Move all the entities.
	for(auto &monster : _monsters)
		monster->move(x_delta, 0, x_bound, y_bound);

	return false;
}

bool MonsterLine::checkCollisionDeath(Entity* entity) {
	for(auto &monster : _monsters){
		if(monster->checkCollisionDeath(entity)){
			return deleteMonster(monster);
		}
	}
	return false;
}


void MonsterLine::notifyDraw(){
	for(auto &monster : _monsters) {
		monster->notifyDraw();
	}
}
