#include "include/Window.h"

namespace AppName {

	void windowResized(GLFWwindow* window, int w, int h) {
		Window* win = Window::currentWindow;
		if (win->nativeWindow != nullptr) {
			win->width = w;
			win->height = h;
			glViewport(0, 0, win->width, win->height);
		}
	}

	Window* Window::currentWindow = nullptr;

	Window::Window() {

	}

	Window* Window::createWindow(int w, int h, std::string title) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* win = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
		if (win == NULL) {
			Debug::ERROR("Falied to create window");
			glfwTerminate();
			return nullptr;
		}
		Window* window = new Window();
		window->width = w;
		window->height = h;
		window->nativeWindow = win;
		Window::currentWindow = window;
		glfwMakeContextCurrent(window->nativeWindow);
		Debug::INFO("Window Created");
		return window;
	}

	void Window::installWindowCallBacks() {
		if (nativeWindow != nullptr) {
			glfwSetWindowSizeCallback(nativeWindow, windowResized);
			glfwSetKeyCallback(nativeWindow, Core::keyPressed);
			glfwSetWindowFocusCallback(nativeWindow, Core::windowOutOfFocus);
		}
	}

	void Window::closeWindow(Window* window) {
		if (window->nativeWindow != nullptr) {
			glfwDestroyWindow(window->nativeWindow);
			Window::currentWindow = nullptr;
			Debug::INFO("Window Closed");
			glfwTerminate();
		}
	}
}