#include "proc_timer.h"
#include "errors.h"

#include <sys/wait.h>
#include <iostream>
#include <cassert>
#include <cstdlib>

void tkit::proc_timer::_run_helper() {
	using user_clock     = boost::chrono::process_user_cpu_clock;
	using system_clock   = boost::chrono::process_system_cpu_clock;
	using wall_clock     = boost::chrono::steady_clock;
	using millisecs      = boost::chrono::milliseconds;


	/* Measure wall-clock time for now. 
	 * There will be multiple modes eventually.
	 * I think CPU time might be more appropriate.
	 * I'll consider this option later.
	 */

	int status;
	const auto start = wall_clock::now();
	waitpid(_id, &status, 0);
	const auto duration = wall_clock::now() - start;
	const auto total = boost::chrono::duration_cast<millisecs>(duration).count();
	std::cout << total << '\n';
}

void tkit::proc_timer::run(bool should_wait) {
 	std::vector<char*> cargs;
	for (int i = 0; i < _args.size(); i++) {
		const auto arg = _args[i];
		cargs.push_back(const_cast<char*>(arg.c_str()));
	}

	cargs.push_back(nullptr);
	_id = fork();
	if (_id == -1)
		throw fork_error();

	if (_id == 0) {
		execvp(_args[0].c_str(), cargs.data());
		_exit(EXIT_FAILURE);
	}

	std::thread run_thread(&tkit::proc_timer::_run_helper, this);
	if (should_wait)
		run_thread.join();
	else
		run_thread.detach();
}

int main(int argc, const char** argv) {
	tkit::proc_timer t("vim rose.cpp", 1.0);
	t.run(true);
	return EXIT_SUCCESS;
}