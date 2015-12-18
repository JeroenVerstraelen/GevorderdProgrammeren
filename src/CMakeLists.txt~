# Extend the CMake module path to find the FindSFML.cmake
# file in {project root}/cmake/Modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2.1 COMPONENTS system window graphics)

# The source files to compile
SET(SRC main.cpp Controller/LevelController Controller/MenuController Controller/parsers/LevelParser Controller/parsers/tinyxml/tinyxml Controller/parsers/tinyxml/tinystr Controller/parsers/tinyxml/tinyxmlerror Controller/parsers/tinyxml/tinyxmlparser Model/Entity Model/Shield Model/Bullet Model/Level Model/Monster Model/Player Model/ParticleGenerator Model/Button View/LevelWindow View/Observer View/EntityObserver View/ParticleObserver Utils/StopWatch Utils/RandomGenerator)

# Add include dirs for SFML
# (The SFML_INCLUDE_DIR variable is defined by FindSFML.cmake, if SFML was found)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

# The program we're compiling with the sources set above
ADD_EXECUTABLE(space ${SRC})

# Link target to SFML libs
# (The SFML_LIBRARIES variable is defined by FindSFML.cmake, if SFML was found)
TARGET_LINK_LIBRARIES(space ${SFML_LIBRARIES})

INSTALL(TARGETS space DESTINATION ${PROJECT_SOURCE_DIR}/bin)
