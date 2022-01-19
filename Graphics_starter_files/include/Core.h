#ifndef CORE_CLASS_H
#define CORE_CLASS_H

#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Debug.h"

namespace AppName {
	struct Core {
		static bool isPaused;
		static bool appInFocus;

		static void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void windowOutOfFocus(GLFWwindow* window, int focus);
	};
}

#endif // !CORE_CLASS_H
