#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <limits>
#include <algorithm>

#include "Level.h"
#include "Entity.h"
#include "Player.h"
#include "../Utils/StopWatch.h"
#include "../Utils/RandomGenerator.h"

namespace si {

	Level::Level(std::pair<double, double> bounds) : _bounds(bounds) {}

	Level::~Level(){
		for(auto &entity : _entities)
			delete entity;

		for(auto &p_gen : _particle_generators)
			delete p_gen;
	}

	LevelStatus Level::tick(StopWatch* stop_watch){
		double elapsed_time = stop_watch->getPreviousTime();

		// The entities to remove after the AI has been handled.
		std::vector<Entity*> entities_to_remove;

		/*
		 * Handle AI.
		 */
		for(auto &entity : _entities) {
			// Bullets
			if(entity->getType() == "Bullet") {
				if(!entity->move(elapsed_time, _bounds.first, _bounds.second)){
					entities_to_remove.push_back(entity);
					continue;
				}
				for(auto &other : _entities) {
					if(entity != other){
						bool delete_bullet = false;
						if(other->checkCollisionDeath(entity, delete_bullet))
							entities_to_remove.push_back(other);
						if(delete_bullet)
							entities_to_remove.push_back(entity);
					}
				}
			}
		}

		// Monsters
		if(stop_watch->getMonsterTime() >= 1000) {
			// Get the properties of the monster block.
			double min_x = std::numeric_limits<double>::infinity();
			double max_x = 0;
			double max_y = 0;
			for(auto &entity : _entities) {
				if(entity->getType() == "Monster") {
					if(entity->getLocation().first > max_x)
						max_x = entity->getLocation().first;
					if(entity->getLocation().first < min_x)
						min_x = entity->getLocation().first;
					if(entity->getLocation().second > max_y)
						max_y = entity->getLocation().second;
				}
			}	

			// If the monsters have moved down past a certain point.
			if(max_y >= _y_monster_limit){
				// Level has ended.
				return FAILURE;
			}
		
			// Calculate the x and y delta.
			double x_delta = 0;
			double y_delta = 0;
			if(_monster_moving_right) {
				x_delta = _x_monster_speed;
				if(max_x + x_delta >= _x_monster_limit) {
					x_delta = 0;
					y_delta = _y_monster_speed;
					_monster_moving_right = false;
				}
			}
			else {
				x_delta = -_x_monster_speed;
				if(min_x + x_delta <= 0) {
					x_delta = 0;
					y_delta = _y_monster_speed;
					_monster_moving_right = true;
				}
			}

			// Move all the monsters.
			for(auto &entity : _entities) { 
				if(entity->getType() == "Monster")
					entity->move(x_delta, y_delta, _bounds.first, _bounds.second);
			}

			stop_watch->resetMonsterTime();	
		}	

		// Update the particle generators.
		std::vector<ParticleGenerator*> _pgens_to_remove;
		for(auto &p_gen : _particle_generators) {
			if(!p_gen->update(elapsed_time)) {
				_pgens_to_remove.push_back(p_gen);
			}
			p_gen->notifyDraw();
		}
		// Delete the particle generators that are done.
		for(auto &p_gen : _pgens_to_remove) {
			std::vector<ParticleGenerator*>::iterator it;
			it = std::find(_particle_generators.begin(), _particle_generators.end(), p_gen);
			if(it != _particle_generators.end()) {
				_particle_generators.erase(it);
				delete p_gen;
			}
		}

		// Remove the entities that have been killed by a bullet.
		for(auto &entity : entities_to_remove) {
			if(entity != NULL){
				std::vector<Entity*>::iterator it = std::find(_entities.begin(), _entities.end(), entity);
				if(it != _entities.end()) {
					if(entity == _player)
						return FAILURE;
					if(entity->getType() == "Monster") {
						// Generate particles on monster death.
						std::vector<Observer*> particle_observers = entity->notifyDestruct();
						ParticleGenerator* p_gen = new ParticleGenerator(particle_observers, 1000, EXPLOSION);
						p_gen->setEmitter(entity->getLocation().first, entity->getLocation().second);
						_particle_generators.push_back(p_gen);
					}
					_entities.erase(it);
					delete entity;
				}
			}
		}	

		// Check if there are any monsters left.
		bool monsters_left = false;
		for(auto &entity : _entities){
			if(entity->getType() == "Monster") {
				monsters_left = true;
				break;
			}
		}
		if(!monsters_left)
			return SUCCES;

		// Notify all to draw
		for(auto &entity : _entities)
			entity->notifyDraw(); 

		return NORMAL;
	}

	void Level::setPlayer(Player* p){
		_player = p;
	}

	void Level::setBounds(std::pair<double, double> bounds){
		_bounds = bounds;
	}

	void Level::setMonsterAI(double x_speed, double y_speed, double x_limit, double y_limit, bool moving_right) {
			_x_monster_speed = x_speed;
			_y_monster_speed = y_speed;
			_x_monster_limit = x_limit;
			_y_monster_limit = y_limit;
			_monster_moving_right = moving_right;
	}

	void Level::addEntity(Entity* entity){
		_entities.push_back(entity);
	}

	std::vector<Entity*> Level::getMonstersCanShoot() const {
		// Calculate the different columns of the monster block.
		std::vector<int> monster_column_x;
	
		for(auto &entity : _entities) {
			if(entity->getType() == "Monster") { 
				double monster_x = entity->getLocation().first;
				bool column_found = false;
				for(auto x_to_search : monster_column_x) {
					if(x_to_search == monster_x)
						column_found = true;
				}
				if(!column_found) 
					monster_column_x.push_back(monster_x);
			}
		}
		// Calculate the max y-value per column.
		std::vector<int> column_max_y;	
		for(auto column : monster_column_x)
			column_max_y.push_back(0);
		for(auto &entity : _entities) {
			if(entity->getType() == "Monster") { 
				double monster_x = entity->getLocation().first;
				double monster_y = entity->getLocation().second;
				unsigned int index = 0;
				for( ; index < monster_column_x.size()-1; ++index) {
					if(monster_column_x[index] == monster_x)
						break;
				}
				if(monster_y > column_max_y[index])
					column_max_y[index] = monster_y;
			}
		}
		// Calculate the monsters that are able to shoot.
		std::vector<Entity*> monsters_can_shoot;
		for(auto &entity : _entities) {
			if(entity->getType() == "Monster") { 
				double monster_x = entity->getLocation().first;
				double monster_y = entity->getLocation().second;
				unsigned int index = 0;
				for( ; index < monster_column_x.size()-1; ++index) {
					if(monster_column_x[index] == monster_x)
						break;
				}
				if(monster_y == column_max_y[index])
					monsters_can_shoot.push_back(entity);
			}			
		}

		return monsters_can_shoot;
	}

	Player* Level::getPlayer() const {
		return _player;
	}

	std::pair<double, double> const Level::getBounds() const {
		return _bounds;
	}

	std::vector<Entity*> const& Level::getEntities() const {
		return _entities;
	}

}


