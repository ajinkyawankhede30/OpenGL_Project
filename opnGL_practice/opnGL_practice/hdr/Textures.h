#pragma once
#include <iostream>

class Textures
{
public:
	Textures(const std::string& filename);
	~Textures();
	inline int GetWidth()  { return m_width; }
	inline int GetHeight() {return m_height;}
	void Bind();
	void UnBind();

private:
	unsigned int m_rendererID;
	unsigned char* m_imgBuffer;
	int m_width, m_height, m_BPP;
	std::string m_imgPath;

};

