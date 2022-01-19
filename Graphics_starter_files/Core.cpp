#include "include/Core.h"

namespace AppName {

	bool Core::isPaused = false;
	bool Core::appInFocus = true;

	void Core::keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			isPaused = !isPaused;
		}
	}

	void Core::windowOutOfFocus(GLFWwindow* window, int focus) {
		if (focus) {
			appInFocus = true;
		}
		else {
			appInFocus = false;
		}
	}
}
