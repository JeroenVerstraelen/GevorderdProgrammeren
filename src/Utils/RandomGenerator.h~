//============================================================================
// Name        : RandomGenerator.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : A basic random number generator.
//============================================================================

#include <random>

namespace si {

	class RandomGenerator
	{
		private:
			/**
			 * The instance of RandomGenerator being used.
			 */
			static RandomGenerator* _instance;

			/**
			 * Instance used for generating random numbers.
			 */
    			std::mt19937 mt;

			/**
			 * Default Constructor (hidden).
			 */
			RandomGenerator() : mt(std::random_device()()) {}

			/**
			 * Copy Constructor (not implemented).
			 */
			RandomGenerator(RandomGenerator const&)	= delete;

			/**
			 * Assignment Operator (not implemented).
			 */
			void operator=(RandomGenerator const&) 	= delete;

		public:
			/**
			 * Returns an instance of RandomGenerator.
			 * @return An instance of RandomGenerator.
			 */
			static RandomGenerator* getInstance();

			/**
			 * Gets the elapsed time since last reset.
			 * @param min The minimum value this method can return.
			 * @param max The maximum value this method can return.
			 * @return A random integer.
			 */
			int getRandomInt(int min, int max);
	};

}
