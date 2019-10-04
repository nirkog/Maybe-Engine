#pragma once

#include <unordered_map>

#include "../core/File.h"
#include "../core/Log.h"
#include "../core/math/Vec2.h"
#include "../core/math/Vec3.h"
#include "../core/math/Vec4.h"
#include "../core/math/Mat4.h"
#include "GL.h"

namespace mb {

	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetID() const { return m_ID; }

		void SetUniform1i(const char* name, int v);
		void SetUniform1f(const char* name, float v);
		void SetUniform2f(const char* name, float v0, float v1);
		void SetUniform3f(const char* name, float v0, float v1, float v2);
		void SetUniform4f(const char* name, float v0, float v1, float v2, float v3);
		void SetUniformVec2(const char* name, const Vec2& vec);
		void SetUniformVec3(const char* name, const Vec3& vec);
		void SetUniformVec4(const char* name, const Vec4& vec);
		void SetUniformMat4(const char* name, const Mat4& mat);
	private:
		int GetUniformLocation(const char* name);
	private:
		std::unordered_map<const char*, int> m_UniformLocationCache;
		unsigned int m_ID;
	};

}