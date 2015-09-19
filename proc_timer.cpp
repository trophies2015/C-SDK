#include "proc_timer.h"
#include "errors.h"

#include <sys/wait.h>
#include <unistd.h>
#include <cassert>
#include <cstdlib>
#include <thread>
#include <iostream>

void tkit::proc_timer::_run_helper() {
	assert(_id == -1);
	_id = fork();
	if (_id == -1)
		throw fork_error();

	std::vector<char*> cargs;
	for (std::string arg : _args)
		cargs.push_back(const_cast<char*>(arg.c_str()));

	cargs.push_back(nullptr);
	if (_id == 0) {
		execvp(cargs[0], cargs.data());
		_exit(EXIT_FAILURE);
	}

	int status;
	waitpid(_id, &status, 0);
	_id = -1;
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		throw exec_fail_error();

	return;
}

void tkit::proc_timer::run() {
	_run_thread.detach();
}

int main(int argc, const char** argv) {
	tkit::proc_timer t("something", 1.0);
	t.run();
	return 0;
}