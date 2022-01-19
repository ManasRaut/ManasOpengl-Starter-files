#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include "Core.h"

namespace AppName {

	class Window {
	public:
		unsigned int width = 600;
		unsigned int height = 600;

		GLFWwindow* nativeWindow = nullptr;
		static Window* currentWindow;

		Window();
		void installWindowCallBacks();

		static Window* createWindow(int w, int h, std::string title);
		static void closeWindow(Window* window);
	};
}

#endif // !WINDOW_CLASS_H