//============================================================================
// Name        : LevelParser.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : Parser for Space Invaders XML documents.
//============================================================================

#ifndef LEVELPARSER_H_
#define LEVELPARSER_H_

#include <string>
#include "tinyxml/tinyxml.h"

#include "../../Model/Level.h"
#include "../../View/LevelWindow.h"

namespace si {
namespace controller {

class LevelParser {
private:

	/*
	 * XML document to parse.
	 */
	TiXmlDocument doc;

	/*
	 * Root of the XML document to parse.
	 */
	TiXmlElement * root;

	/*
	 * Loads any XML file. Returns true when loading the file was succesfull.
	 * Returns false, when something went wrong during loading.
	 */
	bool loadFile(std::string filename);

	/*
	 * Helper functions for parsing.
	 */
	const char* readAttributeCString(TiXmlElement* elem, const char* tag);

	std::string readAttributeString(TiXmlElement* elem, const char* tag);

	const char* readElementCString(TiXmlElement* elem, const char* tag);

	std::string readElementString(TiXmlElement* elem, const char* tag);


public:
	/*
	 * Default constructor.
	 */
	LevelParser(){};

	/*
	 * Parse the level with the given XML file.
	 * @param file_name The XML file to parse, it will be changed to the file_name
	 * 	  of the level following this one.
	 * @param level The level to be constructed.
	 * @param window The window to be constructed.
   	 * @return Wether the element was parsed correctly.
	 */
	bool parseLevel(std::string& file_name, model::Level* level, view::LevelWindow* window);

};


} // Namespace controller
} // Namespace si

#endif /* LEVELPARSER_H_ */
