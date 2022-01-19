#ifndef SCENE_LOADER_CLASS_H
#define SCENE_LOADER_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Core.h"
#include "Model.h"
#include "Mesh.h"

namespace AppName {
	class SceneLoader
	{
	public:
		SceneLoader();
		Model* loadOBJ(std::string filename);
	};
}

#endif // !SCENE_LOADER_CLASS_H

