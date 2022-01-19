#include "include/SceneLoader.h"

namespace AppName {
	std::vector<std::string> readFile(std::string filename) {
		std::ifstream in(filename);
		std::string contents = "";
		char c;
		while (in.peek() != EOF) {
			in.get(c);
			contents += c;
		}

		std::vector<std::string> data;
		std::string temp = "";
		for (int i = 0; i < contents.size(); i++) {
			if (contents.at(i) == ' ' || contents.at(i) == '\n') {
				data.push_back(temp);
				temp = "";
				continue;
			}
			temp += contents.at(i);
		}
		data.push_back(temp);
		return data;
	}

	SceneLoader::SceneLoader() {

	}

	Model* SceneLoader::loadOBJ(std::string filename) {
		std::vector<std::string> contents = readFile(filename);
		std::vector<Mesh> meshes;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		bool isStarting = true;
		std::string currentMeshName = "";

		for (size_t i = 0; i < contents.size(); i) {
			if (contents.at(i) == "o") {
				if (isStarting) {
					isStarting = false;
					currentMeshName = contents.at(i + 1);
				}
				else {
					meshes.push_back(Mesh(currentMeshName, vertices, indices));
					positions.clear();
					texCoords.clear();
					indices.clear();
					vertices.clear();
					currentMeshName = contents.at(i + 1);
				}
				i += 2;
				continue;
			}
			else if (contents.at(i) == "v") {
				positions.push_back(glm::vec3(std::stof(contents.at(i + 1)), std::stof(contents.at(i + 2)), std::stof(contents.at(i + 3))));
				i += 4;
			}
			else if (contents.at(i) == "vt") {
				texCoords.push_back(glm::vec2(std::stof(contents.at(i + 1)), std::stof(contents.at(i + 2))));
				i += 3;
			}
			else if (contents.at(i) == "vn") {
				normals.push_back(glm::vec3(std::stof(contents.at(i + 1)), std::stof(contents.at(i + 2)), std::stof(contents.at(i + 3))));
				i += 4;
			}
			else if (contents.at(i) == "f") {
				std::string c1 = contents.at(i + 1);
				std::string c2 = contents.at(i + 2);
				std::string c3 = contents.at(i + 3);

				uint32_t p1 = std::stoi(c1.substr(0, c1.find_first_of("/"))) - 1;
				uint32_t p2 = std::stoi(c2.substr(0, c2.find_first_of("/"))) - 1;
				uint32_t p3 = std::stoi(c3.substr(0, c3.find_first_of("/"))) - 1;

				uint16_t t1 = std::stoi(c1.substr(c1.find_first_of("/") + 1, c1.find_last_of("/"))) - 1;
				uint16_t t2 = std::stoi(c2.substr(c2.find_first_of("/") + 1, c2.find_last_of("/"))) - 1;
				uint16_t t3 = std::stoi(c3.substr(c3.find_first_of("/") + 1, c3.find_last_of("/"))) - 1;

				uint32_t n1 = std::stoi(c1.substr(c1.find_last_of("/") + 1, c1.length())) - 1;
				uint32_t n2 = std::stoi(c2.substr(c2.find_last_of("/") + 1, c2.length())) - 1;
				uint32_t n3 = std::stoi(c3.substr(c3.find_last_of("/") + 1, c3.length())) - 1;

				vertices.push_back(Vertex{ positions.at(p1), texCoords.at(t1), normals.at(n1) });
				vertices.push_back(Vertex{ positions.at(p2), texCoords.at(t2), normals.at(n1) });
				vertices.push_back(Vertex{ positions.at(p3), texCoords.at(t3), normals.at(n1) });
				indices.push_back(indices.size());
				indices.push_back(indices.size());
				indices.push_back(indices.size());
				i += 4;
			}
			else {
				i++;
			}
		}
		meshes.push_back(Mesh(currentMeshName, vertices, indices));
		Debug::INFO("Loaded " + filename + " = Mesh count: " + std::to_string(meshes.size()));

		return new Model(meshes);
	}
}