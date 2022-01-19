#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <iostream>

#include <stb/stb_image.h>

#include "Core.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

namespace AppName {
	class World {
	public:
		static GLuint gridVAO, gridVBO, cubeMapVAO, cubeMapVBO, cubeMapEBO;
		static GLuint cubeMapTexture;
		static Shader* gridShader;
		static float worldColor[4];
		static bool isUsingSkyBox;
		static std::vector<Model*> modelList;

		static void init();
		static void createSkyBox(std::string folder);
		static void drawWorld(Shader* shader, Camera& camera);
		static void deleteWorld();
	};
}
#endif // !WORLD_CLASS_H
