//============================================================================
// Name        : Observer.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : An observer that tracks an Entity Model and draws it on a levelWindow.
//============================================================================

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <SFML/Graphics.hpp>
#include "LevelWindow.h"
#include "../Model/Entity.h"


/** 
 * Forward Declaration of Entity.
 */
class Entity;

/** 
 * Enumeration to give more detail to a notify call of an observer.
 */
enum Notification { MOVE, DRAW, DESTROY };


class Observer{
	/** 
	 * The level_window the observer will draw on.
	 */
	LevelWindow* level_window;

	/** 
	 * The sprite the observer will draw.
	 */
	sf::Sprite sprite;

	public:
		/**
		 * Default Constructor.
		 */
		Observer(LevelWindow* lw);

		/**
		 * Set the sprite of the Observer.
 		 * @param texture The texture to be used for the sprite.
		 */
		void setTexture(sf::Texture* texture);

		/**
		 * Notifies the observer of a given action by an observee.
 		 * @param entity A pointer to the observee.
 		 * @param n An enum type detailing the action.
		 */
		void notify(Entity* entity, Notification n);
};

#endif /* OBSERVER_H_ */
