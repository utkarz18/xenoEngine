#include<iostream>
#include "shader.h"

namespace xeno{ namespace graphics {

	Shader::Shader(const char* vertPath, const char* fragPath)
	{
		m_VertPath = vertPath;
		m_FragPath = fragPath;
		m_ShaderID = load();
	}
	
	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	unsigned int Shader::load()
	{
		unsigned int program = glCreateProgram();
		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = read_file(m_VertPath);
		std::string fragSourceString = read_file(m_FragPath);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		compileShader(vertex, vertSource, "vertex");
		compileShader(fragment, fragSource, "fragment");

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	void Shader::compileShader(unsigned int id, const char* shaderSource, std::string shadertype)
	{
		glShaderSource(id, 1, &shaderSource, NULL);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile " << shadertype << " shader!" << std::endl << message << std::endl;
			glDeleteShader(id);
			return;
		}
	}

	int Shader::getUniformLocation(const char* name)
	{
		return glGetUniformLocation(m_ShaderID, name);
	}

	void Shader::setUniform1f(const char* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void  Shader::setUniform1fv(const char* name, float* value, int count)
	{
		glUniform1fv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1i(const char* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void  Shader::setUniform1iv(const char* name, int* value, int count)
	{
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform2f(const char* name, const maths::vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const char* name, const maths::vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const char* name, const maths::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const char* name, const maths::mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	void Shader::enable() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}
} }