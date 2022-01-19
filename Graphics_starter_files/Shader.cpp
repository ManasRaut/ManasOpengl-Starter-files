#include "include/Shader.h"

namespace AppName {
	std::vector<Shader*> Shader::shaderList;

	std::string readSource(const char* filename) {
		try {
			std::string contents;
			std::ifstream in(filename);
			char c;
			while (in.peek() != EOF) {
				in.get(c);
				contents += c;
			}
			return contents;
		}
		catch (...) {
			Debug::ERROR("Failed to read file: " + std::string(filename));
			return "ERROR";
		}
	}

	Shader* Shader::createShader(const char* vertexPath, const char* fragmentPath) {
		Shader* sh = new Shader(vertexPath, fragmentPath);
		Shader::shaderList.push_back(sh);
		return sh;
	}

	void Shader::deleteAllShaders() {
		for (int i = 0; i < shaderList.size(); i++) {
			shaderList.at(i)->deleteShader();
			delete shaderList.at(i);
		}
	}

	Shader::Shader(const char* vertexPath, const char* fragmentPath) {
		std::string vs = readSource(vertexPath);
		std::string fs = readSource(fragmentPath);

		if (vs == "ERROR" || fs == "ERROR") {
			return;
		}

		const char* vertexSource = vs.c_str();
		const char* fragmentSource = fs.c_str();

		GLuint vertexShader, fragmentShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		if (!checkCompileErrors(vertexShader, "VERTEX")) {
			Debug::INFO("Failed to load Vertex shader");
			return;
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		if (!checkCompileErrors(fragmentShader, "FRAGMENT")) {
			Debug::INFO("Failed to load fragment shader");
			return;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		if (!checkCompileErrors(ID, "PROGRAM")) {
			Debug::INFO("Failed to load Shader program");
			return;
		}

		Debug::INFO(std::string(vertexPath) + "Shader loaded");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	bool Shader::checkCompileErrors(GLuint shader, std::string type) {
		int success;
		char infoLog[512];
		if (type == "PROGRAM") {
			glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
			if (success == GL_FALSE)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
				return false;
			}
		} else {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::" + type + "::COMPILATION_FAILED\n" <<
					infoLog << std::endl;
				return false;
			};
		}
		return true;
	}

	void Shader::use() {
		glUseProgram(ID);
	}

	void Shader::deleteShader() {
		glDeleteProgram(ID);
	}

	void Shader::setFloat(const std::string uniformName, float value) {
		glUniform1f(glGetUniformLocation(ID, uniformName.c_str()), value);
	}

	void Shader::setInt(const std::string uniformName, int value) {
		glUniform1i(glGetUniformLocation(ID, uniformName.c_str()), value);
	}

	void Shader::setBool(const std::string uniformName, bool value) {
		glUniform1i(glGetUniformLocation(ID, uniformName.c_str()), value);
	}

	void Shader::setVec3(const std::string uniformName, glm::vec3 value) {
		glUniform3fv(glGetUniformLocation(ID, uniformName.c_str()), 1, glm::value_ptr(value));
	}

	void Shader::setMat4(const std::string uniformName, glm::mat4 mat) {
		glUniformMatrix4fv(glGetUniformLocation(ID, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}
}