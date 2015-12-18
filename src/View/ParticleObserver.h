#ifndef PARTICLEOBSERVER_H_
#define PARTICLEOBSERVER_H_

#include "Observer.h"
#include "../Model/ParticleGenerator.h"

namespace si {

	class ParticleGenerator;

	class ParticleObserver : public Observer {
	private:

		/** 
		 * The VertexArray representing the particles.
		 */
		sf::VertexArray _m_vertices;

	public:

		/** 
		 * Constructor
		 * @param lw The window that the observer will draw on.
		 * @param count The amount of particles to observe.
		 */	
		ParticleObserver(LevelWindow* lw, int count);

		/**
		 * Destructor.
		 */
		virtual ~ParticleObserver(){}

		/**
		 * Set the sprite of the Observer.
		 * @param texture The texture to be used for the sprite.
		 */
		virtual void addTexture(sf::Texture& texture);

		/**
		 * Notifies the observer of a given action by an observee.
		 * @param entity The entity to observe.
		 * @param n An enum type detailing the action.
		 * @return Will always return a nullptr.
		 */
		virtual Observer* notify(Entity* entity, Notification n);

		/**
		 * Notifies the observer of a given action by an observee.
		 * @param particle_generator The particleGenerator to observe.
		 * @param n An enum type detailing the action.
		 */
		virtual void notify(ParticleGenerator* particle_generator, Notification n);

		/**
		 * Get the level window.
		 * @return The level window of the instance.
		 */
		virtual LevelWindow* getLevelWindow() const;
	};

}
#endif /* PARTICLEOBSERVER_H_ */
