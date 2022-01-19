#ifndef GUI_CLASS_H
#define GUI_CLASS_H

#include <glm/glm.hpp>

#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_opengl3.h"
#include "../ImGUI/imgui_impl_glfw.h"
#include "../ImGUI/imgui_stdlib.h"

#include "Core.h"
#include "Window.h"

namespace AppName {
	class Frame {
	public:
		Frame();
		std::string title;
		virtual void render();
	};

	class LoadModelFrame : public Frame {
	public:
		std::string filename, shaderName;
		virtual void render();
	};

	class GUI {
	public:
		static std::vector<Frame*> frames;
		static void init();
		static void render();
		static void Destroy();
	};
}

#endif // !GUI_CLASS_H