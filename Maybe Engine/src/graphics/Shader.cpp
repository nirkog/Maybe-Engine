#include "Shader.h"

namespace mb {

	unsigned int CompileShader(const char* source, unsigned int type)
	{
		unsigned int id;
		GLCall(id = glCreateShader(type));
		GLCall(glShaderSource(id, 1, &source, 0));
		GLCall(glCompileShader(id));

		int success = 0;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

		if(!success)
		{
			int length;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

			char* log = (char*) malloc(length * sizeof(char));
			GLCall(glGetShaderInfoLog(id, length, &length, log));

			Log::Error("ERROR COMPILING {} SHADER!", (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT");
			Log::Error(log);

			delete log;
		}

		return id;
	}

	unsigned int CreateProgram(unsigned int vertexID, unsigned int fragmentID)
	{
		unsigned int id;
		GLCall(id = glCreateProgram());

		GLCall(glAttachShader(id, vertexID));
		GLCall(glAttachShader(id, fragmentID));

		GLCall(glLinkProgram(id));

		int success = 0;
		GLCall(glGetProgramiv(id, GL_LINK_STATUS, &success));
		if (!success)
		{
			int length;
			GLCall(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length));

			char* log = (char*) malloc(length * sizeof(char));
			GLCall(glGetProgramInfoLog(id, length, &length, log));

			Log::Error("ERROR LINKING SHADER {}!", log);

			delete log;
		}

		GLCall(glDeleteShader(vertexID));
		GLCall(glDeleteShader(fragmentID));
	
		return id;
	}

	Shader::Shader(const char* vertexPath, const char* fragmentPath)
		: m_ID(0)
	{
		File vertexFile(vertexPath);
		char* vertexSource = (char*) malloc(vertexFile.Length() + 1);
		vertexSource[vertexFile.Length()] = '\0';
		vertexFile.Read(vertexSource, vertexFile.Length());

		unsigned int vertexID = CompileShader(vertexSource, GL_VERTEX_SHADER);

		delete vertexSource;

		File fragmentFile(fragmentPath);
		char* fragmentSource = (char*) malloc(fragmentFile.Length() + 1);
		fragmentSource[fragmentFile.Length()] = '\0';
		fragmentFile.Read(fragmentSource, fragmentFile.Length());

		unsigned int fragmentID = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

		delete fragmentSource;

		m_ID = CreateProgram(vertexID, fragmentID);
	}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(m_ID));
	}

	void Shader::Bind() const
	{
		GLCall(glUseProgram(m_ID));
	}

	void Shader::Unbind() const
	{
		GLCall(glUseProgram(0));
	}

	int Shader::GetUniformLocation(const char* name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		GLCall(int location = glGetUniformLocation(m_ID, name));

		if (location == -1)
			Log::Warn("Warning: uniform {} does not exist!", name);

		m_UniformLocationCache[name] = location;

		return location;
	}

	void Shader::SetUniform1i(const char* name, int v)
	{
		GLCall(glUniform1i(GetUniformLocation(name), v));
	}

	void Shader::SetUniform2f(const char* name, float v0, float v1)
	{
		GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
	}

	void Shader::SetUniform3f(const char* name, float v0, float v1, float v2)
	{
		GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
	}

	void Shader::SetUniform4f(const char* name, float v0, float v1, float v2, float v3)
	{
		GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
	}

	void Shader::SetUniformVec2(const char* name, const Vec2& vec)
	{
		GLCall(glUniform2f(GetUniformLocation(name), vec.x, vec.y));
	}

	void Shader::SetUniformVec3(const char* name, const Vec3& vec)
	{
		GLCall(glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z));
	}

	void Shader::SetUniformVec4(const char* name, const Vec4& vec)
	{
		GLCall(glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w));
	}

	void Shader::SetUniformMat4(const char* name, const Mat4& mat)
	{
		const Mat4 transposed = mat.Transpose();
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, transposed.GetData()));
	}
}