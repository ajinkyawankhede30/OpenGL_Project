#include <iostream>
#include <Renderer.h>



void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	if (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] ( " << error << " )" << ": " << function << ": " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shaders& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	CallLog(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
