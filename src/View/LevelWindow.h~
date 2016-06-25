//============================================================================
// Name        : LevelWindow.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : Wraps the sf::RenderWindow for use as a level.
//============================================================================


#ifndef LEVELVIEW_H_
#define LEVELVIEW_H_

#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <map>

namespace si {
namespace view {

class LevelWindow : public sf::RenderWindow{
	/** 
	 * All the textures used in this window/level.
	 */
	std::map<std::string, sf::Texture> textures;

	/** 
	 * The sprite used for the background of the window.
	 */
	sf::Sprite background;

	public:
		/**
		 * Constructor.
		 */
		LevelWindow();

		/**
		 * Constructor inherited from sf::RenderWindow.
		 * @param vm The video mode to use.
		 * @param title The window title to use.
		 * @param style The style of window to use.
		 * @param settings The OpenGL settings to use for the window.
		 */
  		LevelWindow(sf::VideoMode mode, const std::string& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());


		/**
		 * Destructor
		 */
		virtual ~LevelWindow();

		/**
		 * Runs the current level.
		 * @param file_path The location of the texture file.
		 * @param key Optional key name to look up the texture in the map.
 		 * @return Wether The action succeeded.
		 */
		bool addTexture(std::string file_path, std::string key = "");

		/**
		 * Sets the background of the level.
		 * @param background_texture The texture to use as a background.
		 */
		void setBackground(sf::Texture& background_texture);

		/**
		 * Draws the background of the level.
		 */
		void drawBackground();

		/**
		 * Returns the textures used in this level/window.
 		 * @return A map of textures with file_name as key.
		 */
		std::map<std::string, sf::Texture>& getTextures();
};

} // Namespace view
} // Namespace si
#endif /* LEVELVIEW_H_ */
