#include "include/Model.h"

namespace AppName {
	Model::Model(std::vector<Mesh> meshes) {
		m_meshes = meshes;
	}

	void Model::setShader(Shader* shader) {
		m_shader = shader;
	}

	void Model::setTexture(std::string meshName, GLuint texture) {
		for (int i = 0; i < m_meshes.size(); i++) {
			if (m_meshes.at(i).meshName == meshName) {
				m_meshes.at(i).setTexture(texture);
				break;
			}
		}
	}

	void Model::draw() {
		glm::mat4 m = glm::translate(modelMat, position);
		m = glm::scale(m, scaleVal);
		for (int i = 0; i < m_meshes.size(); i++) {
			m_meshes.at(i).draw(m_shader, m);
		}
	}

	void Model::resetTransformations() {
		modelMat = glm::mat4(1.0f);
	}

	void Model::translate(glm::vec3 dest) {
		position += dest;
	}

	void Model::rotate(float angle, glm::vec3 axis) {
		// TODO: Rotation
		//modelMat = glm::rotate(modelMat, glm::radians(angle), glm::normalize(axis));
	}

	void Model::scale(float x, float y, float z) {
		scaleVal = glm::vec3(x, y, z);
	}

	void Model::applyForce(glm::vec3 f) {
		instantForce = f;
	}

	void Model::Delete() {
		for (int i = 0; i < m_meshes.size(); i++) {
			m_meshes.at(i).Delete();
		}
	}
}