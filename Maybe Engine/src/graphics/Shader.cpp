#include "Shader.h"

namespace mb { namespace graphics {

	unsigned int Shader::m_ActiveShader = 0;

	std::string ReadFile(const char* fileName)
	{
		std::stringstream stream;
		std::ifstream file(fileName);
		std::string line;

		if (file.is_open())
		{
			while (getline(file, line))
			{
				stream << line << "\n";
			}
			file.close();
		}

		return stream.str();
	}

	unsigned int CompileShader(std::string source, unsigned int type)
	{
		const char* shaderSource = source.c_str();
		unsigned int id;
		GLCall(id = glCreateShader(type));
		GLCall(glShaderSource(id, 1, &shaderSource, 0));
		GLCall(glCompileShader(id));

		int success = 0;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

		if (!success)
		{
			int length;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

			char* log = (char*)malloc(length * sizeof(char));
			GLCall(glGetShaderInfoLog(id, length, &length, log));

			const char* typeString = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
			std::cout << "ERROR SHADER:" << typeString << "!" << std::endl;
			std::cout << log << std::endl;

			free(log);
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

			char* log = (char*)malloc(length * sizeof(char));
			GLCall(glGetProgramInfoLog(id, length, &length, log));

			std::cout << "ERROR LINKING SHADERS " << log << "!" << std::endl;
		
			free(log);
		}

		GLCall(glDeleteShader(vertexID));
		GLCall(glDeleteShader(fragmentID));

		return id;
	}

	Shader::Shader(const char* vertexFile, const char* fragmentFile)
		: m_ID(0)
	{
		m_VertexSource = ReadFile(vertexFile);
		m_FragmentSource = ReadFile(fragmentFile);

		unsigned int vertexID = CompileShader(m_VertexSource, GL_VERTEX_SHADER);
		unsigned int fragmentID = CompileShader(m_FragmentSource, GL_FRAGMENT_SHADER);

		m_ID = CreateProgram(vertexID, fragmentID);
	}

	Shader::~Shader()
	{
		//GLCall(glDeleteProgram(m_ID));
	}

	void Shader::Bind() const
	{
		if (m_ActiveShader != m_ID)
		{
			GLCall(glUseProgram(m_ID));
			m_ActiveShader = m_ID;
			//std::cout << "Binding shader" << std::endl;
		}
	}

	void Shader::Unbind() const
	{
		GLCall(glUseProgram(0));
		m_ActiveShader = 0;
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationsCache.find(name) != m_UniformLocationsCache.end())
			return m_UniformLocationsCache[name];
	
		GLCall(int location = glGetUniformLocation(m_ID, name.c_str()));
		
		if (location == -1)
			std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;

		m_UniformLocationsCache[name] = location;
		return location;
	}

	void Shader::SetUniform1i(const std::string& name, int v)
	{
		GLCall(glUniform1i(GetUniformLocation(name), v));
	}

	void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
	}

	void Shader::SetUniformVec2(const std::string& name, const maths::Vec2& v)
	{
		GLCall(glUniform2f(GetUniformLocation(name), v.x, v.y));
	}

	void Shader::SetUniformVec3(const std::string& name, const maths::Vec3& v)
	{
		GLCall(glUniform3f(GetUniformLocation(name), v.x, v.y, v.z));
	}

	void Shader::SetUniformMat4(const std::string& name, const maths::Mat4& mat)
	{
		maths::Mat4 transposed = mat.Transpose();
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, transposed.GetData()));
	}

} }