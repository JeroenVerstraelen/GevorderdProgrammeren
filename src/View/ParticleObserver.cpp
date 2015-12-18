#include "ParticleObserver.h"
#include <tuple>
#include "../Model/ParticleGenerator.h"

namespace si {

	ParticleObserver::ParticleObserver(LevelWindow* lw, int count) : Observer(lw), _m_vertices(sf::Points, count) {}

	void ParticleObserver::addTexture(sf::Texture& texture) {}

	Observer* ParticleObserver::notify(Entity* entity, Notification n){return nullptr;}

	void ParticleObserver::notify(ParticleGenerator* particle_generator, Notification n) {
		switch(n){
			case MOVE: 
			{
				std::vector<Particle> particles = particle_generator->getParticles();
				std::tuple<int, int, int> rgb = particle_generator->getRGB();

				for (std::size_t i = 0; i < particles.size(); ++i)
				{
					_m_vertices[i].position = sf::Vector2f(particles[i].position.first, particles[i].position.second);
					_m_vertices[i].color.r = static_cast<sf::Uint8>(std::get<0>(rgb));
					_m_vertices[i].color.g = static_cast<sf::Uint8>(std::get<1>(rgb));
					_m_vertices[i].color.b = static_cast<sf::Uint8>(std::get<2>(rgb));
				}
				break;
			}
		    	case DRAW: 
			{	
				level_window->draw(_m_vertices);
				break;
			}
			default:
				break;
		}
	}

	LevelWindow* ParticleObserver::getLevelWindow() const {
		return level_window;
	}

}
