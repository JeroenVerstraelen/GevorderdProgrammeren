#include "RandomGenerator.h"

namespace si {

	RandomGenerator* RandomGenerator::_instance = nullptr;

	RandomGenerator* RandomGenerator::getInstance(){
		if(_instance == NULL){
			static RandomGenerator instance;
			_instance = &instance;
		}

	 	return _instance;
	}


	int RandomGenerator::getRandomInt(int min, int max){
		std::uniform_real_distribution<double> dist(min, max);
		return dist(mt);
	}

}
