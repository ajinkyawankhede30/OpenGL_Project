#pragma once
#include <iostream>
#include <string>
#include <glew.h>
#include <glfw3.h>

class IndexBuffer {

	unsigned int m_rendererID;
	unsigned int m_count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_count; }
};