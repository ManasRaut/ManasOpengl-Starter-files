#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include "Core.h"
#include "Mesh.h"
#include "Camera.h"

namespace AppName {
	class Model {

	public:
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 scaleVal = glm::vec3(1.0f);
		glm::vec4 rotation = glm::vec4(0.0f);

		float mass = 0.0f;
		glm::vec3 instantForce = glm::vec3(0.0f);
		glm::vec3 velocity = glm::vec3(0.0f);

		glm::mat4 modelMat = glm::mat4(1.0f);

		Model(std::vector<Mesh> meshes);
		void setShader(Shader* shader);
		void setTexture(std::string meshName, GLuint texture);
		void draw();
		void Delete();

		void resetTransformations();
		void translate(glm::vec3 dest);
		void rotate(float angle, glm::vec3 axis);
		void scale(float x, float y, float z);
		void applyForce(glm::vec3 f);

	private:
		std::vector<Mesh> m_meshes;
		Shader* m_shader;
	};
}
#endif // !MODEL_CLASS_H
