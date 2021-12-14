#pragma once
#include <external_includes.h>

namespace nGraphics
{
	GLuint LoadTextureFromFile(const char* fileName, GLenum minificationFilter = GL_LINEAR, GLenum magnificationFilter = GL_LINEAR);
}