#include "Project.h"

Project::Project(const char* vertex, const char* fragment)
{
	shader = new Shader(vertex,fragment);

	spriteRender = new SpriteRenderer(*shader);
	
}
