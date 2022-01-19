#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<glm/glm.hpp>

#include "Core.h"
#include "Shader.h"
#include "Camera.h"

namespace AppName {
	struct Vertex {
		glm::vec3 position;
		glm::vec2 texCoords;
		glm::vec3 normal;
	};

	class Mesh {
	public:
		std::string meshName = "";
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		Mesh(std::string name, std::vector<Vertex> vertices, std::vector<uint32_t> indices);
		void Delete();
		void setTexture(GLuint texture);
		void draw(Shader* shader, glm::mat4 trans);

	private:
		std::vector<Vertex> m_vertices;
		std::vector<GLuint> m_indices;
		GLuint m_texture;

	};
}
#endif // !MESH_CLASS_H
