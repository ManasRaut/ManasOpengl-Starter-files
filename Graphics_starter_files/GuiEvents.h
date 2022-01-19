#ifndef GUI_EVENTS_CPP
#define GUI_EVENTS_CPP

#include <string>
#include <fstream>

#include "include/SceneLoader.h"
#include "include/World.h"

namespace AppName {
	void loadModel(std::string filename, std::string shaderName) {
		std::string vs = shaderName + std::string(".vert");
		std::string fs = shaderName + std::string(".frag");

		//std::ifstream modelFile(filename.c_str());
		//std::ifstream shaderFile(shaderName.c_str());

		//if (modelFile.good() && shaderFile.good()) {
			SceneLoader sc;
			Model* model = sc.loadOBJ(filename);
			Shader* shader = Shader::createShader(vs.c_str(), fs.c_str());
			model->setShader(shader);
			World::modelList.push_back(model);
			Debug::INFO("Loaded new Model " + filename);
		/*}
		else
			Debug::INFO("Failed to load model " + filename);*/
	}
}

#endif
