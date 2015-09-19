#include <utils.h>
#include <vector>
#include <string>

namespace tkit {
	class proc_timer {
	public:
		proc_timer(const std::string& path, double lim) 
			:_lim(lim),
			:_args(utils::split(path))
		{
			// some initialization work here...
		}

		pid_t id() const { 
			return _id;
		}

	private:
		double _lim;
		pid_t _id;
		std::vector<std::string> _args;
	};
};