#include "VertexBuffClass.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		//generate buffer
		CallLog(glGenBuffers(1, &m_rendererID));

		//select buffer
		CallLog(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));

		//assign data to buffer
		CallLog(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

VertexBuffer::~VertexBuffer()
	{
		CallLog(glDeleteBuffers(1, &m_rendererID));
	}

	void VertexBuffer::Bind() const
	{
		CallLog(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	}

	void VertexBuffer::Unbind() const
	{
		CallLog(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
