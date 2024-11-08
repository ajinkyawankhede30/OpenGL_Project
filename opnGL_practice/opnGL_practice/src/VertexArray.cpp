#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	CallLog(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
	CallLog(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		//enable vertex attribute
		CallLog(glEnableVertexAttribArray(i));

		//assign attributes
		CallLog(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeofType(element.type);

	}
}

void VertexArray::Bind() const
{
	CallLog( glBindVertexArray(m_rendererID));
}

void VertexArray::Unbind() const
{
	CallLog(glBindVertexArray(0));
}