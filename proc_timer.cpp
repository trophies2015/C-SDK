#include "proc_timer.h"
#include "errors.h"

#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <thread>

void tkit::proc_timer::_run_helper() {
	using user_clock     = boost::chrono::process_user_cpu_clock;
	using system_clock   = boost::chrono::process_system_cpu_clock;
	using wall_clock     = boost::chrono::steady_clock;
	using millisecs      = boost::chrono::milliseconds;


	/* Measure CPU time for now. 
	 * There will be multiple modes eventually.
	 * I think CPU time might be more appropriate.
	 * I'll consider this option later.
	 */

	int status;
	const auto start = user_clock::now();
	const auto sys_start = system_clock::now();
	waitpid(_id, &status, 0);
	const auto duration = user_clock::now() - start;
	const auto system_duration = system_clock::now() - sys_start;
	const auto user_total = boost::chrono::duration_cast<millisecs>(duration).count();
	const auto system_total = boost::chrono::duration_cast<millisecs>(system_duration).count();
	const auto result = user_total + system_total;

	bool tled = (WIFSIGNALED(status) && WTERMSIG(status) == SIGPROF);
	tled = (tled || (result > _lim));
	if (tled)
		std::cout << "Time limit exceeded.\n";
	else
		std::cout << "Passed!\n";
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

	itimerval time_limit, old;
	time_limit.it_value = {_lim / 1000, (_lim % 1000) * 1000};
	time_limit.it_interval = {0, 0};

	// Limits on the child process:
	const rlimit process_lim = {1, 1};
	if (_id == 0) {
		setitimer(ITIMER_PROF, &time_limit, &old);
		setrlimit(RLIMIT_NPROC, &process_lim);
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
	tkit::proc_timer t("vim test.cpp", 1000);
        struct rlimit rl; 
        rl.rlim_cur = 1; 
	t.run(true);
	return EXIT_SUCCESS;
}
