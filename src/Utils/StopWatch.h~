//============================================================================
// Name        : StopWatch.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : A simple stopwatch that can keep track of elapsed time.
//============================================================================

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <chrono>
#include <ctime>

namespace si {

	class StopWatch
	{
		private:
		    	typedef std::chrono::duration<float> duration;
			typedef std::chrono::milliseconds ms;

			/**
			 * The instance of StopWatch being used.
			 */
			static StopWatch* _instance;

			/**
			 * The time of the last global reset.
			 */
			std::chrono::time_point<std::chrono::steady_clock> _previous;

			/**
			 * The elapsed_time between the last two resets.
			 */
			double _previous_time = 0;

			/**
			 * The time of the last player bullet time reset.
			 */
			std::chrono::time_point<std::chrono::steady_clock> _previous_player_bullet_time;

			/**
			 * The time of the last monster bullet time reset.
			 */
			std::chrono::time_point<std::chrono::steady_clock> _previous_monster_bullet_time;

			/**
			 * The time of the last monster time reset.
			 */
			std::chrono::time_point<std::chrono::steady_clock> _previous_monster_time;

			/**
			 * Default Constructor (hidden).
			 */
			StopWatch(){}

			/**
			 * Copy Constructor (not implemented).
			 */
			StopWatch(StopWatch const&) 		= delete;

			/**
			 * Assignment operator (not implemented).
			 */
			void operator=(StopWatch const&)  	= delete;

		public:
			/**
			 * Returns an instance of StopWatch.
			 * @return An instance of StopWatch.
			 */
			static StopWatch* getInstance();

			/**
			 * Resets the stopWatch.
			 */
			void reset();

			/**
			 * Deletes the current instance.
			 */
			void fullReset();

			/**
			 * Gets the duration between the last two resets.
			 * @return The elapsed time in milliseconds.
			*/
			double getPreviousTime();

			/**
			 * Resets the player bullet time.
			 */
			void resetPlayerBulletTime();

			/**
			 * Gets the elapsed time since last player bullet time reset.
			 * @return The elapsed time in milliseconds.
			 */
			double getPlayerBulletTime();

			/**
			 * Resets the monster bullet time.
			 */
			void resetMonsterBulletTime();

			/**
			 * Gets the elapsed time since last monster bullet time reset.
			 * @return The elapsed time in milliseconds.
			 */
			double getMonsterBulletTime();

			/**
			 * Resets the monster time.
			 */
			void resetMonsterTime();

			/**
			 * Gets the elapsed time since last monster time reset.
			 * @return The elapsed time in milliseconds.
			 */
			double getMonsterTime();
	};

}
#endif /* STOPWATCH_H_ */
