#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <utility>

#include "Level.h"
#include "Entity.h"
#include "Player.h"

Level::Level(std::pair<double, double> bounds, double y_offset) : _bounds(bounds), _y_offset(y_offset) {}

Level::~Level(){
	for(auto &entity : _entities)
		delete entity;
}

bool Level::tick(double elapsed_time){
	// Handle AI.
	for(auto &entity : _entities) {
		// Monsters
		if(entity->getType() == "MonsterLine")
			entity->move(elapsed_time, _bounds.first, _bounds.second);
		
		// Bullets
		if(entity->getType() == "Bullet") {
			entity->move(elapsed_time, _bounds.first, _bounds.second);
			std::vector<Entity*> entities_to_remove;
			for(auto &entity : _entities) {
				if(entity->checkCollisionDeath(entity))
					entities_to_remove.push_back(entity);
			}

			for(auto &entity : entities_to_remove) {
				std::list<Entity*>::iterator it = std::find(_entities.begin(), _entities.end(), entity);
				if(it != _entities.end()) {
					if(entity == _player)
						return false;
					_entities.erase(it);
					delete entity;
				}
			}	
		}
	}

	// Notify all to draw
	for(auto &entity : _entities)
		entity->notifyDraw(); 

	return true;
}

void Level::setPlayer(Player* p){
	_player = p;
}

void Level::setYOffset(double offset){
	_y_offset = offset;
}

void Level::setBounds(std::pair<double, double> bounds){
	_bounds = bounds;
}

void Level::addEntity(Entity* entity){
	_entities.push_back(entity);
}

Player* Level::getPlayer() const{
	return _player;
}

std::pair<double, double> const& Level::getBounds() const{
	return _bounds;
}


