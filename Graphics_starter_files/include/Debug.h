#ifndef DEBUG_H
#define DEBUG_H

#include "Core.h"

namespace AppName {
	struct Debug {
		static void INFO(std::string title);
		static void WARN(std::string title);
		static void ERROR(std::string title);
		static void DEBUG(std::string title);
	};
}
#endif // !DEBUG_H
