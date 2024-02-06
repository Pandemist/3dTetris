#ifndef TETROMINO_H
#define TETROMINO_H

#include "Angel.h"

#define T_POINTS 144
#define T_POINTS_PER_BLOCK 36

class Tetromino {
public:
	Tetromino (vec4 points[T_POINTS], vec4 color, vec4 pivotPoint);
	virtual ~Tetromino();
	void setPoints(vec4 points[T_POINTS]);

	vec4 points[T_POINTS];
	vec4 color;
	vec4 pivotPoint;
};

#endif
