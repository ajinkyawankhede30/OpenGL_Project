#include "IndexBuffClass.h"
#include "Renderer.h"


	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
		:m_count(count)
	{
		//generate buffer
		CallLog(glGenBuffers(1, &m_rendererID));

		//select buffer
		CallLog(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));

		//assign data to buffer
		CallLog(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		CallLog(glDeleteBuffers(1, &m_rendererID));
	}

	void IndexBuffer::Bind() const
	{
		CallLog(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	}

	void IndexBuffer::Unbind() const
	{
		CallLog(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}