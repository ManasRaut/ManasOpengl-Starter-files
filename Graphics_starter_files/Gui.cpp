#include "include/Gui.h"
#include "GuiEvents.h"

namespace AppName {

	std::vector<Frame*> GUI::frames;

	void GUI::init() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(Window::currentWindow->nativeWindow, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.Fonts->AddFontFromFileTTF("rs/Ubuntu-L.ttf", 16);

		LoadModelFrame* loadFrame = new LoadModelFrame();
		frames.push_back(loadFrame);

		Debug::INFO("ImGui initialized");
	}
	void GUI::render() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		for (int i = 0; i < frames.size(); i++) {
			frames.at(i)->render();
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUI::Destroy() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		Debug::INFO("ImGui destructed");
	}

	Frame::Frame() {}
	void Frame::render() {}

	void LoadModelFrame::render() {
		std::string pos = glm::to_string(Camera::currentCamera->position);
		ImGui::Begin("Load Model");
		ImGui::Text(pos.c_str());
		ImGui::InputText("Filename", &filename);
		ImGui::InputText("Shader", &shaderName);
		if (ImGui::Button("Load")) {
			loadModel(filename, shaderName);
		}
		ImGui::End();
	}
}
