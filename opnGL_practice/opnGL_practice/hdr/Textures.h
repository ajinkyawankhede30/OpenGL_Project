#pragma once
#include <iostream>

class Textures
{
public:
	Textures(std::string filename);
	~Textures();
	void Bind();
	void UnBind();

private:
	unsigned int m_id;

};

