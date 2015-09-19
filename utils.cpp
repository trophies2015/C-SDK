#include <sstream>
#include <deque>

#include "utils.h"

namespace utils {
	std::string trim(const std::string& str) {
		std::deque<char> current;
		for (char c : str)
			current.push_back(c);

		while (current.front() == ' ')
			current.pop_front();
		
		while (current.back() == ' ')
			current.pop_back();

		std::string result;
		for (char c : current)
			result += c;

		return result;
	}

	std::vector<std::string> split(const std::string& big, char delim) {
		std::stringstream ss(big);
		std::string item;
		std::vector<std::string> result;
		while (std::getline(ss, item, delim)) {
			item = trim(item);
			if (item.empty())
				continue;

			result.push_back(item);
		}

		return result;
	}
}