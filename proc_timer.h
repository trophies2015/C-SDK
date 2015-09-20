#ifndef TKIT_PROC_TIMER
#define TKIT_PROC_TIMER

#if !(defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
	#error You need to compile this file on a UNIX system.
#endif

#include <boost/chrono.hpp>
#include <vector>
#include <string>
#include <thread>

#include "utils.h"

namespace tkit {
	class proc_timer {
	public:
		proc_timer(const std::string& path, int lim) 
			:_lim(lim),
			_args(utils::split(path, ' ')),
			_id(-1)
		{

		}

		pid_t id() const { return _id; }
		int lim() const { return _lim; } // milliseconds.
		void run(bool);
	private:
		pid_t _lim;
		int _id;
		std::vector<std::string> _args;
		void _run_helper();
	};
};

#endif