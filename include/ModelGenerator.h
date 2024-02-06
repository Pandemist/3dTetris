#ifndef H_SHAPE
#define H_SHAPE

#define SHAPE_I 0
#define SHAPE_L 1
#define SHAPE_SQ 2
#define SHAPE_S 3
#define SHAPE_T 4
#define SHAPE_T_RIGHT 5
#define SHAPE_T_LEFT 6
#define SHAPE_TRIPOD 7

#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include "Tetromino.h"
#include "TetrominoTransforms.h"

class ModelGenerator {

public:
	ModelGenerator(int rowSize, int colSize, int depthSize);

	Tetromino* createTetro();

private:
	float models[8][5][3];

	void createMatrix(int rowSize, int colSize, int depthSize);
};

#endif
