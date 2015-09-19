#if !(defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
	#error You need to compile this file on a UNIX system.
#endif

#include "utils.h"
#include <unistd.h>
#include <vector>
#include <string>
#include <thread>

namespace tkit {
	class proc_timer {
	public:
		proc_timer(const std::string& path, int lim) 
			:_lim(lim),
			_args(utils::split(path, ' ')),
			_run_thread(std::thread(&proc_timer::_run_helper, this)),
			_id(-1)
		{
		
		}

		pid_t id() const { return _id; }
		int lim() const { return _lim; } // milliseconds.
		void run();
	private:
		int _lim;
		int _id;
		std::vector<std::string> _args;
		std::thread _run_thread;
		void _run_helper();
	};
};