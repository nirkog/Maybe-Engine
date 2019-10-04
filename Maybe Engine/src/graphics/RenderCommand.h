#pragma once

#include "../core/math/vec3.h"
#include "GL.h"

namespace mb {

	class RenderCommand
	{
	public:
		static void SetClearColor(const Vec3& color);
		static void Clear();

		static void DrawArrays(GLenum mode, unsigned int start, unsigned int vertexCount);
		static void DrawElements(GLenum mode, unsigned int count, GLenum type, const void* indices);
	
		static void SetViewport(int x, int y, unsigned int width, unsigned int height);

		static void InitBlending();
	};

}