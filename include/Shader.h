#ifndef SHADER_H
#define SHADER_H

#include "Angel.h"

char* readShaderSource(const char* shaderFile);

GLuint Angel::InitShader(const char* vShaderFile, const char* fShaderFile);
#endif
