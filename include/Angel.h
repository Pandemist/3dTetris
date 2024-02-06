#ifndef __ANGEL_H__
#define __ANGEL_H__

#include <cmath>
#include <iostream>

#ifndef M_PI
	#define M_PI  3.14159265358979323846
#endif

#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

namespace Angel {

GLuint InitShader(const char* vertexShaderFile, const char* fragmentShaderFile);

const GLfloat  DegreesToRadians = M_PI / 180.0;

}
#include "vec.h"
#include "mat.h"
using namespace Angel;

#endif