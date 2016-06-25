//============================================================================
// Name        : EntityObserver.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : Represents an observer that can track entities.
//============================================================================

#ifndef ENTITYOBSERVER_H_
#define ENTITYOBSERVER_H_

#include <SFML/Graphics.hpp>

#include "LevelWindow.h"
#include "Observer.h"

namespace si {
namespace view {

class EntityObserver : public Observer {
	public:
		/**
		 * Default Constructor.
		 * @param lw The window that the observer will draw on.
		 */
		EntityObserver(LevelWindow* lw);

		/**
		 * Add a texture to the Observer.
 		 * @param texture The texture to be added for the observer.
		 */
		virtual void addTexture(sf::Texture& texture);

		/**
		 * Notifies the observer of a given action by an observee.
 		 * @param entity The entity to observe.
 		 * @param n An enum type detailing the action.
		 * @return Can possibly return a pointer to an observer based on the action of the entity.
		 */
		virtual Observer* notify(model::Entity* entity, Notification n);

		/**
		 * Get the level window.
 		 * @return The level window of the instance.
		 */
		virtual LevelWindow* getLevelWindow() const;
};

} // Namespace view
} // Namespace si
#endif /* ENTITYOBSERVER_H_ */
