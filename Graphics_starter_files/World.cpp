#include "include/World.h"

namespace AppName {

	GLuint World::gridVAO = 0;
	GLuint World::gridVBO = 0;
	GLuint World::cubeMapTexture = 0;
	GLuint World::cubeMapVAO = 0;
	GLuint World::cubeMapVBO = 0;
	GLuint World::cubeMapEBO = 0;
	
	Shader* World::gridShader = nullptr;
	float World::worldColor[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	bool World::isUsingSkyBox = false;
	std::vector<Model*> World::modelList;

	void World::init() {
		int k = 0;
		float grid[36 * 3] = {};
		for (int i = -4; i <= 4; i++) {
			grid[k++] = i; grid[k++] = 0; grid[k++] = 4;
			grid[k++] = i; grid[k++] = 0; grid[k++] = -4;
		}
		for (int i = -4; i <= 4; i++) {
			grid[k++] = 4; grid[k++] = 0; grid[k++] = i;
			grid[k++] = -4; grid[k++] = 0; grid[k++] = i;
		}

		float cubeVerts[] = {
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
		};
		GLuint cubeIndices[] = {
			6, 2, 1, 1, 5, 6,
			7, 4, 0, 0, 3, 7,
			6, 5, 4, 4, 7, 6,
			2, 3, 0, 0, 1, 2,
			5, 1, 0, 0, 4, 5,
			6, 7, 3, 3, 2, 6
		};

		// cube map cube
		glGenVertexArrays(1, &cubeMapVAO);
		glBindVertexArray(cubeMapVAO);

		glGenBuffers(1, &cubeMapVBO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeMapVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

		glGenBuffers(1, &cubeMapEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeMapEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// grid
		glGenVertexArrays(1, &gridVAO);
		glBindVertexArray(gridVAO);

		glGenBuffers(1, &gridVBO);
		glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(grid), grid, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void World::createSkyBox(std::string folder) {
		std::string textures[] = {
			"right.jpg", "left.jpg", "top.jpg",
			"bottom.jpg", "front.jpg", "back.jpg"
		};
		
		glGenTextures(1, &cubeMapTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		stbi_set_flip_vertically_on_load(false);
		int w, h, channels;
		for (int i = 0; i < 6; i++) {
			std::string filename = "rs/textures/" + folder + "/" + textures[i];
			unsigned char* imageData = stbi_load(filename.c_str(), &w, &h, &channels, 0);
			if (imageData) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 
					GL_RGB, w, h, GL_FALSE, GL_RGB, GL_UNSIGNED_BYTE, imageData);
				stbi_image_free(imageData);
			}
			else {
				Debug::ERROR("Failed to load cubemap texture: " + textures[i]);
				stbi_image_free(imageData);
			}
		}
		stbi_set_flip_vertically_on_load(true);
	}

	void World::drawWorld(Shader* shader, Camera& camera) {
		if (gridShader != nullptr) {
			glBindVertexArray(gridVAO);
			gridShader->use();
			camera.processMatrix(gridShader, glm::mat4(1.0f));
			glDrawArrays(GL_LINES, 0, 108);
		}
	
		glDepthFunc(GL_EQUAL);
		glBindVertexArray(cubeMapVAO);
		shader->use();
		camera.processMatrix(shader, glm::mat4(1.0f));
		glm::mat4 view = glm::mat4(glm::mat3(camera.view));
		shader->setMat4("view", view);
		shader->setInt("cubeMap", 0);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDepthFunc(GL_LESS);
	}

	void World::deleteWorld() {
		glDeleteBuffers(1, &gridVBO);
		glDeleteVertexArrays(1, &gridVAO);
		glDeleteBuffers(1, &cubeMapVBO);
		glDeleteBuffers(1, &cubeMapEBO);
		glDeleteVertexArrays(1, &cubeMapVAO);
		glDeleteTextures(1, &cubeMapTexture);
		for (int i = 0; i < modelList.size(); i++) {
			modelList.at(i)->Delete();
			delete modelList.at(i);
		}
	}
}