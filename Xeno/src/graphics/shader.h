#pragma once

#include <xenogl.h>

#include "../utils/fileUtils.h"
#include "../maths/maths.h"

namespace xeno{ namespace graphics {

	class Shader
	{
	private:
		unsigned int m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;
		const char* m_ShaderFor;

	public:
		Shader(const char* vertPath, const char* fragPath, const char* shaderFor);
		~Shader();


		void setUniform1f(const char* name, float value);
		void setUniform1fv(const char* name, float* value, int count);
		void setUniform1i(const char* name, int value);
		void setUniform1iv(const char* name, int* value, int count);
		void setUniform2f(const char* name, const maths::vec2& vector);
		void setUniform3f(const char* name, const maths::vec3& vector);
		void setUniform4f(const char* name, const maths::vec4& vector);
		void setUniformMat4(const char* name, const maths::mat4& matrix);

	
		void enable() const;
		void disable() const;

	private:
		unsigned int load();
		int getUniformLocation(const char* name);
		void compileShader(unsigned int id, const char* shaderSource, std::string shadertype);
	
	};
} }
