#include <chrono>
#include <ctime>
#include "StopWatch.h"

namespace si {

	StopWatch * StopWatch::_instance = nullptr;

	StopWatch* StopWatch::getInstance() {
		if(_instance == NULL){
			static StopWatch instance;
			_instance = &instance;
			instance._previous =  std::chrono::steady_clock::now();
			instance._previous_player_bullet_time = std::chrono::steady_clock::now();
			instance._previous_monster_bullet_time = std::chrono::steady_clock::now();
			instance._previous_monster_time = std::chrono::steady_clock::now();
		}
	 	return _instance;
	}

	void StopWatch::reset() {
	    	duration dur = std::chrono::steady_clock::now() - _previous;
		ms milliseconds = std::chrono::duration_cast<ms>(dur);
	     	_previous_time = milliseconds.count();
		_previous = std::chrono::steady_clock::now();
	}

	void StopWatch::fullReset() {
		_instance = NULL;
	}

	double StopWatch::getPreviousTime() {
		return _previous_time;
	}

	void StopWatch::resetPlayerBulletTime() {
		_previous_player_bullet_time = std::chrono::steady_clock::now();
	}

	double StopWatch::getPlayerBulletTime() {
	    	duration dur = std::chrono::steady_clock::now() - _previous_player_bullet_time;
		ms milliseconds = std::chrono::duration_cast<ms>(dur);
	     	return milliseconds.count();
	}

	void StopWatch::resetMonsterBulletTime() {
		_previous_monster_bullet_time = std::chrono::steady_clock::now();
	}

	double StopWatch::getMonsterBulletTime() {
	    	duration dur = std::chrono::steady_clock::now() - _previous_monster_bullet_time;
		ms milliseconds = std::chrono::duration_cast<ms>(dur);
	     	return milliseconds.count();
	}

	void StopWatch::resetMonsterTime() {
		_previous_monster_time =  std::chrono::steady_clock::now();
	}

	double StopWatch::getMonsterTime() {
	    	duration dur = std::chrono::steady_clock::now() - _previous_monster_time;
		ms milliseconds = std::chrono::duration_cast<ms>(dur);
	     	return milliseconds.count();
	}

}

