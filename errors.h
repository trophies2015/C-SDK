#ifndef TKIT_ERROR
#define TKIT_ERROR

#include <stdexcept>

namespace tkit {
	class exception : public std::exception { };
	class fork_error : public exception {
		virtual const char* what() {
			return "Failed to create process... could the system be out of resources?";
		}
	};

	class pipe_error : public exception {
		virtual const char* what() {
			return "Failed to create pipe for output process.";
		}
	};

	class exec_fail_error : public exception {
		virtual const char* what() {
			return "Failed to launch the desired program.";
		}
	};

	class runtime_error : public exception {
		virtual const char* what() {
			return "A runtime error occured.";
		}
	};
}

#endif