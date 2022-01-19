#ifndef  CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Core.h"
#include "Shader.h"
#include "Debug.h"
#include "Window.h"

namespace AppName {

	class Camera {
	public:

		static Camera* currentCamera;

		glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		float speed = 5.0f;
		float sensitivity = 0.25f;
		float fov = 45.0f;
		float zNear = 0.1f, zFar = 100.0f;
		bool firstClick = true;

		Camera();
		void processMatrix(Shader* shader, glm::mat4 transformation);
		void processInput(GLFWwindow* window, float deltaTime);
	};

}
#endif // ! CAMERA_CLASS_H
