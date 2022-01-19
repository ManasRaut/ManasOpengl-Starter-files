#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core.h"
#include "Debug.h"
#include "Window.h"

namespace AppName {
	class Shader {
	public:
		static std::vector<Shader*> shaderList;
		GLuint ID = 0;

		static Shader* createShader(const char* vertexPath, const char* fragmentPath);
		static void deleteAllShaders();

		Shader(const char* vertexPath, const char* fragmentPath);
		void use();
		void deleteShader();

		void setFloat(const std::string uniformName, float value);
		void setInt(const std::string uniformName, int value);
		void setBool(const std::string uniformName, bool value);
		void setVec3(const std::string uniformName, glm::vec3 value);
		void setMat4(const std::string uniformName, glm::mat4 mat);
		bool checkCompileErrors(GLuint shader, std::string type);
	};
}

#endif
