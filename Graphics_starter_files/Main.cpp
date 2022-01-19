#include <thread>
#include <chrono>

#include "include/Core.h"
#include "include/World.h"
#include "include/Window.h"
#include "include/Camera.h"
#include "include/Shader.h"
#include "include/Gui.h"
#include "include/SceneLoader.h"

using namespace AppName;

void update(float deltaTime) {

}

int main() {

	Window* window = Window::createWindow(800, 600, "AppName FPS = 0");
	if (window == nullptr) {
		Debug::ERROR("Program Exiting");
		return -1;
	}
	window->installWindowCallBacks();

	gladLoadGL();
	glClearColor(World::worldColor[0], World::worldColor[1],
		World::worldColor[2], World::worldColor[3]);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	double lastTime = glfwGetTime();
	double currentTime = lastTime;
	int frames = 0;

	double lastFrame = lastTime;
	double deltaTime = 0;

	Shader* gridShader = Shader::createShader("rs/shaders/grid.vert", "rs/shaders/grid.frag");
	Shader* cubeMapShader = Shader::createShader("rs/shaders/cubeMap.vert", "rs/shaders/cubeMap.frag");
	Shader* standardShader = Shader::createShader("rs/shaders/standard.vert", "rs/shaders/standard.frag");

	World::init();
	World::gridShader = gridShader;
	World::createSkyBox("lakeCubeMap");
	
	Camera camera;
	camera.position = glm::vec3(3.0f, 3.0f, 3.0f);
	camera.front = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f));

	SceneLoader sc;
	Model* cube = sc.loadOBJ("rs/models/ball.obj");
	cube->setShader(standardShader);
	cube->mass = 10.0f;

	GUI::init();

	Debug::INFO("Main loop started");
	Debug::INFO("Application running... \n");
	while (!glfwWindowShouldClose(window->nativeWindow)) {

		if (Core::appInFocus) {
			double curr = glfwGetTime();
			deltaTime = curr - lastFrame;
			lastFrame = curr;

			currentTime = glfwGetTime();
			if (currentTime - lastTime >= 1.0) {
				std::string title = "AppName FPS = " + std::to_string(frames) +
					" , " + std::to_string(deltaTime * 1000) + " ms";
				glfwSetWindowTitle(window->nativeWindow, title.c_str());
				frames = 0;
				lastTime = currentTime;
			}
			frames++;

			update(deltaTime);

			camera.processInput(window->nativeWindow, deltaTime);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (int i = 0; i < World::modelList.size(); i++) {
				World::modelList.at(i)->draw();
			}

			standardShader->setVec3("cameraPos", camera.position);
			cube->draw();

			World::drawWorld(cubeMapShader, camera);

			if (Core::isPaused) {
				GUI::render();
			}

			glfwSwapBuffers(window->nativeWindow);
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(17));
		}
		glfwPollEvents();
	}

	GUI::Destroy();
	World::deleteWorld();
	Shader::deleteAllShaders();
	Window::closeWindow(window);
	Debug::INFO("Program Exiting");
	return 0;
}