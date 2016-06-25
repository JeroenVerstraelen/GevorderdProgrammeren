//==============================================================================================================================
// Name        : Button.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : Represents a button in a menu.
//==============================================================================================================================

#ifndef BUTTON_H_
#define BUTTON_H_

#include <vector>
#include <utility>
#include "Entity.h"
#include "../View/Observer.h"

namespace si {
namespace model {

class Button : public Entity {
	private:
		/** 
		 * Collision box properties.
		 */
		double _length = 0;
		double _height = 0;

		/**
		 * Whether a mouse is hovering over the button.
		 */
		bool hover = false;

	public:

		/** 
		 * Constructor.
		 * @param obs The observers to notify when the button changes.
		 * @param x The location on the x-axis (The middle of the model).
		 * @param y The location on the y-axis (The middle of the model).
		 * @param length The length of the button (Collision box).
		 * @param height The height of the button (Collision box).
		 */
		Button(std::vector<view::Observer*> obs, double x, double y, double length, double height);

		/** 
		 * Returns the type of the entity.
		 * @return the type of the entity.
		 */
		virtual std::string getType();

		/** 
		 * Switches if the button is being hovered over or not.
		 * @param hover_over Whether the mouse is currently hovering over the button.
		 */
		void switchHover(bool hover_over);

		/** 
		 * Returns the length and height of the collision box.
		 * @return the length and height of the collision box.
		 */
		std::pair<double, double> getCollisionBox() const;
};

} // Namespace model
} // Namespace si
#endif /* BUTTON_H_ */
