#include <SFML/Graphics.hpp>
#include <utility>
#include "EntityObserver.h"
#include "ParticleObserver.h"
#include "Observer.h"

using namespace si;
using namespace si::view;

EntityObserver::EntityObserver(LevelWindow* lw) : Observer(lw) {}

void EntityObserver::addTexture(sf::Texture& texture) {
	textures.push_back(texture);
	sprite.setTexture((textures[current_texture]));
	sprite.setOrigin(textures[current_texture].getSize().x / 2, textures[current_texture].getSize().y / 2);
}

Observer* EntityObserver::notify(model::Entity* entity, Notification n){
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
	    	case ITERTEXTURE: 
		{	
			current_texture++;
			if(current_texture > textures.size() - 1)
				current_texture = 0;
			sprite.setTexture(textures[current_texture]);
			sprite.setOrigin(textures[current_texture].getSize().x / 2, textures[current_texture].getSize().y / 2);
			break;
		}
	    	case EXPLODE: 
		{	
			ParticleObserver* p_obs = new ParticleObserver(level_window, 1000);
			return p_obs;
		}
		default:
		{
			break;
		}
	}
	return nullptr;
}	


LevelWindow* EntityObserver::getLevelWindow() const {
	return level_window;
}
