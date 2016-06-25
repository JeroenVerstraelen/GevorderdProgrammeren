#include "ParticleGenerator.h"
#include "../View/ParticleObserver.h"
#include "../Utils/RandomGenerator.h"
#include <utility>
#include <algorithm>

using namespace si;
using namespace si::model;

ParticleGenerator::ParticleGenerator(std::vector<view::Observer*> observers, unsigned int count, ParticleType type) : 
	_observers(observers),
	_m_particles(count),
	_m_emitter(std::make_pair(0,0)),
	_type(type)
{
}

ParticleGenerator::~ParticleGenerator() {
	// Delete the observers from the heap.
	std::vector<view::Observer*>::iterator observer_it;	
	for(observer_it = _observers.begin(); observer_it != _observers.end(); ++observer_it)
		delete (*observer_it);
}

void ParticleGenerator::setEmitter(double x, double y) {
	_m_emitter = std::make_pair(x, y);
	for (std::size_t i = 0; i < _m_particles.size(); ++i)
		resetParticle(i);
}

bool ParticleGenerator::update(double elapsed)
{
	if(_m_particles.size() == 0)
		return false;

	std::size_t particles_to_delete = 0;
	for (std::size_t i = 0; i < _m_particles.size(); ++i) {
		// update the particle lifetime
		Particle& p = _m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if(p.lifetime <= 0) {
			//p.lifetime = 0;
			switch(_type){
				case EXPLOSION: 
					particles_to_delete++;
					break;
				default:
					resetParticle(i);
			}
		}

		// Change the colors depending on the lifetime.
		/*
		float ratio1 = p.lifetime / 10050;
		float ratio2 = p.lifetime / 50050;
		float ratio3 = 0;

		std::get<0>(_rgb) = ratio1 * 255;
		std::get<1>(_rgb) = ratio2 * 255;
		std::get<2>(_rgb) = ratio3 * 255;
		*/
		// update the position of the corresponding vertex
		p.position = std::make_pair(p.position.first + p.velocity.first * elapsed, p.position.second + p.velocity.second * elapsed);
	}

	std::vector<view::Observer*>::iterator observer_it;
	for(observer_it = _observers.begin(); observer_it != _observers.end(); ++observer_it) {
		view::ParticleObserver* particle_observer = static_cast<view::ParticleObserver*>(*observer_it);
		particle_observer->notify(this, view::MOVE);
	}

	if(particles_to_delete == _m_particles.size())
		return false;

	return true;
}

void ParticleGenerator::resetParticle(std::size_t index) {
	RandomGenerator* rand_gen = RandomGenerator::getInstance(); 

	// give a random velocity and lifetime to the particle
	float angle = ((rand_gen->getRandomInt(0, 360) + 0) * 3.14f / 180.f);
	float speed = rand_gen->getRandomInt(0, 3000)/5000.0f + 0.0f;
	_m_particles[index].velocity = std::make_pair(std::cos(angle) * speed, std::sin(angle) * speed);
	_m_particles[index].lifetime = (rand_gen->getRandomInt(0, 50) + 5000);

	// reset the position of the corresponding vertex
       _m_particles[index].position = std::make_pair(_m_emitter.first, _m_emitter.second);
}

void ParticleGenerator::notifyDraw() {
	std::vector<view::Observer*>::iterator observer_it;
	for(observer_it = _observers.begin(); observer_it != _observers.end(); ++observer_it) {
		view::ParticleObserver* particle_observer = static_cast<view::ParticleObserver*>(*observer_it);
		particle_observer->notify(this, view::DRAW);
	}
}

std::vector<Particle> const& ParticleGenerator::getParticles() const{
	return _m_particles;
}

std::tuple<int, int, int>const& ParticleGenerator::getRGB() const {
	return _rgb;
}
