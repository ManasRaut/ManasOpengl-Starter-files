#include "include/Debug.h"

namespace AppName {
	void Debug::INFO(std::string title) {
		std::cerr << "[INFO]  " << title << std::endl;
	}

	void Debug::WARN(std::string title) {
		std::cerr << "[WARN]  " << title << std::endl;
	}

	void Debug::ERROR(std::string title) {
		std::cerr << "[ERR]   " << title << std::endl;
	}

	void Debug::DEBUG(std::string title) {
		std::cerr << "[DEBUG] " << title << std::endl;
	}
}