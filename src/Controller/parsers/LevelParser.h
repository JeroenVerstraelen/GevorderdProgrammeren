//============================================================================
// Name        : GameParser.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : ArcadeGame in C++
//============================================================================

#ifndef LevelParser_H
#define LevelParser_H
#include <string>
#include <map>
#include "tinyxml/tinyxml.h"

#include "../../Model/Level.h"
#include "../../View/LevelWindow.h"


using namespace std;


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

	string readAttributeString(TiXmlElement* elem, const char* tag);

	const char* readElementCString(TiXmlElement* elem, const char* tag);

	string readElementString(TiXmlElement* elem, const char* tag);


public:
	/*
	 * Default constructor.
	 */
	LevelParser(){};

	/*
	 * Parse the level with the given XML file.
	 * @param file_name The XML file to parse.
	 * @param level The level to be constructed.
	 * @param window The window to be constructed.
   	 * @return Wether the element was parsed correctly.
	 */
	bool parseLevel(std::string file_name, Level* level, LevelWindow* window);
	
};

#endif
