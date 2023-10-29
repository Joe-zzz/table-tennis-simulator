#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include"SpriteRenderer.h"

class Project
{
private:
	
	bool state;
	
public:
	Project(const char* vertex,const char* fragment);
	Shader* shader;
	SpriteRenderer* spriteRender;


};

