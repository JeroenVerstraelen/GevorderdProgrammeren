//============================================================================
// Name        : StopWatch.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : A simple stopwatch that can keep track of elapsed time.
//============================================================================

#include <chrono>
#include <ctime>

class StopWatch
{
	public:
		/**
		 * Returns an instance of StopWatch.
		 * @return An instance of StopWatch.
		 */
		static StopWatch& getInstance();

		/**
		 * Resets the stopWatch.
		 */
		void reset();

		/**
		 * Gets the elapsed time since last reset.
		 * @return The elapsed time in milliseconds.
		 */
		double getElapsedTime();

	private:
		/**
		 * The time since last reset.
		 */
		std::chrono::time_point<std::chrono::steady_clock> previous;

		/**
		 * Default Constructor (hidden).
		 */
        	StopWatch();

	public:
		/**
		 * Copy Constructor (not implemented).
		 */
		StopWatch(StopWatch const&) 		= delete;

		/**
		 * Assignment operator (not implemented).
		 */
		void operator=(StopWatch const&)  	= delete;
};
