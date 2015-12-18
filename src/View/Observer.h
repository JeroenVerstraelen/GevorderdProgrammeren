//============================================================================
// Name        : Observer.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : An abstract class representing an Observer.
//============================================================================

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "LevelWindow.h"
#include "../Model/Entity.h"

namespace si {

	/** 
	 * Forward Declaration of Entity.
	 */
	class Entity;

	/** 
	 * Enumeration to give more detail to a notify call of an observer.
	 */
	enum Notification { MOVE, DRAW, DESTROY, EXPLODE, ITERTEXTURE };


	class Observer{
		protected:
			/** 
			 * The level_window the observer will draw on.
			 */
			LevelWindow* level_window;

			/** 
			 * The sprite the observer will draw.
			 */
			sf::Sprite sprite;

			/**
			 * The textures used for the sprite.
			 */
			std::vector<sf::Texture> textures;

			/**
			 * The index of the current texture.
			 */
			unsigned int current_texture = 0;

		public:
			/**
			 * Default Constructor.
			 * @param lw The window that the observer will draw on.
			 */
			Observer(LevelWindow* lw);

			/**
			 * Destructor.
			 */
			virtual ~Observer();

			/**
			 * Add a texture to the Observer.
	 		 * @param texture The texture to be added for the observer.
			 */
			virtual void addTexture(sf::Texture& texture) = 0;

			/**
			 * Notifies the observer of a given action by an observee.
	 		 * @param entity The entity to observe.
	 		 * @param n An enum type detailing the action.
			 * @return Can possibly return a pointer to an observer based on the action of the entity.
			 */
			virtual Observer* notify(Entity* entity, Notification n) = 0;

			/**
			 * Get the level window.
	 		 * @return The level window of the instance.
			 */
			virtual LevelWindow* getLevelWindow() const = 0;
	};

}
#endif /* OBSERVER_H_ */
