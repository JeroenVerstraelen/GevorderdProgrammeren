#include <SFML/Graphics.hpp>
#include <utility>
#include "LevelWindow.h"
#include "Observer.h"

Observer::Observer(LevelWindow* lw) : level_window(lw){}

void Observer::setTexture(sf::Texture* texture){
	sprite.setTexture(*texture);
}

void Observer::notify(Entity* entity, Notification n){
	switch(n){
		case MOVE: 
		{
			std::pair<double, double> l = entity->getLocation();
			sprite.setPosition(sf::Vector2f(l.first, l.second));
			break;
		}
	    	case DRAW: 
		{	
			level_window->draw(sprite);
			break;
		}
	}
}	
