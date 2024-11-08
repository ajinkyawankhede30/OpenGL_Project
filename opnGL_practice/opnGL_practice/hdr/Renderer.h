#pragma once
#include <glew.h>

#include "VertexArray.h"
#include "IndexBuffClass.h"
#include "Shaders.h"

#define ASSERT(x) if(!x) __debugbreak();
#define CallLog(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:

	void Draw(const VertexArray& va, const IndexBuffer& ib, Shaders& shader) const;
	void Clear() const;
private:

};