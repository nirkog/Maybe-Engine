#include "RenderCommand.h"

namespace mb {

	void RenderCommand::SetClearColor(const Vec3& color)
	{
		GLCall(glClearColor(color.x, color.y, color.z, 1));
	}

	void RenderCommand::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void RenderCommand::DrawArrays(GLenum mode, unsigned int start, unsigned int vertexCount)
	{
		GLCall(glDrawArrays(mode, start, vertexCount));
	}

	void RenderCommand::DrawElements(GLenum mode, unsigned int count, GLenum type, const void* indices)
	{
		GLCall(glDrawElements(mode, count, type, indices));
	}

	void RenderCommand::SetViewport(int x, int y, unsigned int width, unsigned int height)
	{
		GLCall(glViewport(x, y, width, height));
	}

	void RenderCommand::InitBlending()
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

}