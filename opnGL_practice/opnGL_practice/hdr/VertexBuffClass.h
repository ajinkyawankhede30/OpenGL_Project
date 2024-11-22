#pragma once
#include <iostream>
#include <string>
#include <glew.h>
#include <glfw3.h>

class VertexBuffer {

	unsigned int m_rendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};