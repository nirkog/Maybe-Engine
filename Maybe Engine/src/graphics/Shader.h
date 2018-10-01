#pragma once

#include <iostream>
#include <unordered_map>

#include "../maths/maths.h"

namespace mb { namespace graphics {
	class Shader 
	{
	public:
		Shader(const char* vertexFile, const char* fragmentFile);
		~Shader();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetID() const { return m_ID; }

		void SetUniform1i(const std::string& name, int v);
		void SetUniform3f(const std::string& name, float v0, float v1, float v2);
		void SetUniformVec2(const std::string& name, const maths::Vec2& v);
		void SetUniformVec3(const std::string& name, const maths::Vec3& v);
		void SetUniformMat4(const std::string& name, const maths::Mat4& mat);
	private:
		int GetUniformLocation(const std::string& name);
	private:
		std::unordered_map<std::string, int> m_UniformLocationsCache;
		std::string m_VertexSource, m_FragmentSource;
		unsigned int m_ID;
		static unsigned int m_ActiveShader;
	};
} }