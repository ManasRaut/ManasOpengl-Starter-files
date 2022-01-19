#include "include/Camera.h"

namespace AppName {
	Camera* Camera::currentCamera = nullptr;
	Camera::Camera() {
		Camera::currentCamera = this;
	}

	void Camera::processMatrix(Shader* shader, glm::mat4 transformations) {
		Window* win = Window::currentWindow;
		model = transformations;
		view = glm::lookAt(position, position + front, up);
		proj = glm::perspective(glm::radians(fov), ((1.0f * win->width) / win->height), zNear, zFar);

		shader->setMat4("model", model);
		shader->setMat4("view", view);
		shader->setMat4("proj", proj);
		shader->setVec3("cameraPos", position);
	}

	void Camera::processInput(GLFWwindow* window, float deltaTime) {
		Window* win = Window::currentWindow;

		if (!Core::isPaused) {
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { // front
				position += speed * front * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { // back
				position -= speed * front * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { // left
				position -= speed * glm::normalize(glm::cross(front, up)) * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { // right
				position += speed * glm::normalize(glm::cross(front, up)) * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { // up
				position += speed * up * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { // down
				position -= speed * up * deltaTime;
			}
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) { // mouse
				if (firstClick) {
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
					glfwSetCursorPos(window, (win->width / 2), (win->height / 2));
					firstClick = false;
					return;
				}
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				float xmove = (xpos - (win->width / 2)) * sensitivity;
				float ymove = (ypos - (win->height / 2)) * sensitivity;
				glfwSetCursorPos(window, (win->width / 2), (win->height / 2));

				glm::vec3 newOrientation = glm::rotate(front, glm::radians(-ymove), glm::normalize(glm::cross(front, up)));
				if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(89.0f)) {
					front = newOrientation;
				}

				front = glm::rotate(front, glm::radians(-xmove), up);
			}
			else {
				firstClick = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}
	}
}