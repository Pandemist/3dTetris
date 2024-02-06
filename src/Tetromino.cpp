#include "Tetromino.h"

Tetromino::Tetromino(vec4 points[T_POINTS], vec4 color, vec4 pivotPoint) {
	setPoints(points);
	for(int i = 0; i < 4; i++) {
		this->color[i] = color[i];
		this->pivotPoint[i] = pivotPoint[i];
	}
}

Tetromino::~Tetromino() {}

void Tetromino::setPoints(vec4 points[T_POINTS]) {
	for(int i = 0; i < T_POINTS; i++) {
		for(int j = 0; j < 4; j++) {
			this->points[i][j] = points[i][j];
		}
	}
}
