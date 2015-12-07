#include <stdlib.h>
#include <time.h>  
#include "RandomGenerator.h"

RandomGenerator& RandomGenerator::getInstance(){
	static RandomGenerator instance;
	return instance;
}


int RandomGenerator::getRandomInt(int min, int max){
  srand (time(NULL));
  return rand() % max + min;
}
