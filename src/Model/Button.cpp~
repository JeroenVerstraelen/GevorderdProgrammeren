#include "Button.h"
#include <iostream>

using namespace si;
using namespace si::model;

Button::Button(std::vector<view::Observer*> obs, double x, double y, double length, double height) 
	: Entity(obs, x, y, 0, 0), _length(length), _height(height) {}

std::string Button::getType() {
	return "Button";
}

void Button::switchHover(bool hover_over) {
	if(hover_over != hover) {
		// Notify the observers of the switch.
		std::vector<view::Observer*>::iterator observer_it;	
		for(observer_it = observers.begin(); observer_it != observers.end(); ++observer_it)
			(*observer_it)->notify(this, view::ITERTEXTURE);
		hover = hover_over;
	}
}

std::pair<double, double> Button::getCollisionBox() const {
	return std::make_pair(_length, _height);
}

