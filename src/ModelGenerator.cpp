#include "ModelGenerator.h"

ModelGenerator::ModelGenerator(int rowSize, int colSize, int depthSize) {
	createMatrix(rowSize, colSize, depthSize);
}

void ModelGenerator::createMatrix(int rowSize, int colSize, int depthSize) {

// "Spawnpunkt" für jeden Block bestimmen
	int colCenter = colSize / 2 - 1;
	int depthCenter = depthSize / 2 - 1;
	rowSize = rowSize - 1;

	/*Form:
	 * 0-3	: Tetro (4) Blockkoordinaten
	 * 4	: Pivotpunkt
	 */

	//Straight shape
	models[SHAPE_I][0][0] = colCenter;
	models[SHAPE_I][1][0] = colCenter;
	models[SHAPE_I][2][0] = colCenter;
	models[SHAPE_I][3][0] = colCenter;
	models[SHAPE_I][4][0] = colCenter + 0.5f;

	models[SHAPE_I][0][1] = rowSize;
	models[SHAPE_I][1][1] = rowSize;
	models[SHAPE_I][2][1] = rowSize;
	models[SHAPE_I][3][1] = rowSize;
	models[SHAPE_I][4][1] = rowSize + 0.5f;

	models[SHAPE_I][0][2] = depthCenter - 1;
	models[SHAPE_I][1][2] = depthCenter;
	models[SHAPE_I][2][2] = depthCenter + 1;
	models[SHAPE_I][3][2] = depthCenter + 2;
	models[SHAPE_I][4][2] = depthCenter + 0.5f;

	//L
	models[SHAPE_L][0][0] = colCenter;
	models[SHAPE_L][1][0] = colCenter;
	models[SHAPE_L][2][0] = colCenter;
	models[SHAPE_L][3][0] = colCenter - 1;
	models[SHAPE_L][4][0] = colCenter + 0.5f;

	models[SHAPE_L][0][1] = rowSize;
	models[SHAPE_L][1][1] = rowSize;
	models[SHAPE_L][2][1] = rowSize;
	models[SHAPE_L][3][1] = rowSize;
	models[SHAPE_L][4][1] = rowSize + 0.5f;

	models[SHAPE_L][0][2] = depthCenter - 1;
	models[SHAPE_L][1][2] = depthCenter;
	models[SHAPE_L][2][2] = depthCenter + 1;
	models[SHAPE_L][3][2] = depthCenter + 1;
	models[SHAPE_L][4][2] = depthCenter + 0.5f;

	//Square
	models[SHAPE_SQ][0][0] = colCenter;
	models[SHAPE_SQ][1][0] = colCenter;
	models[SHAPE_SQ][2][0] = colCenter + 1;
	models[SHAPE_SQ][3][0] = colCenter + 1;
	models[SHAPE_SQ][4][0] = colCenter + 1;

	models[SHAPE_SQ][0][1] = rowSize;
	models[SHAPE_SQ][1][1] = rowSize;
	models[SHAPE_SQ][2][1] = rowSize;
	models[SHAPE_SQ][3][1] = rowSize;
	models[SHAPE_SQ][4][1] = rowSize + 1;

	models[SHAPE_SQ][0][2] = depthCenter;
	models[SHAPE_SQ][1][2] = depthCenter - 1;
	models[SHAPE_SQ][2][2] = depthCenter - 1;
	models[SHAPE_SQ][3][2] = depthCenter;
	models[SHAPE_SQ][4][2] = depthCenter;

	//T shape
	models[SHAPE_T][0][0] = colCenter;
	models[SHAPE_T][1][0] = colCenter;
	models[SHAPE_T][2][0] = colCenter + 1;
	models[SHAPE_T][3][0] = colCenter - 1;
	models[SHAPE_T][4][0] = colCenter + 0.5f;

	models[SHAPE_T][0][1] = rowSize;
	models[SHAPE_T][1][1] = rowSize - 1;
	models[SHAPE_T][2][1] = rowSize - 1;
	models[SHAPE_T][3][1] = rowSize - 1;
	models[SHAPE_T][4][1] = rowSize - 0.5f;

	models[SHAPE_T][0][2] = depthCenter;
	models[SHAPE_T][1][2] = depthCenter;
	models[SHAPE_T][2][2] = depthCenter;
	models[SHAPE_T][3][2] = depthCenter;
	models[SHAPE_T][4][2] = depthCenter + 0.5f;

	//S shape
	models[SHAPE_S][0][0] = colCenter + 1;
	models[SHAPE_S][1][0] = colCenter;
	models[SHAPE_S][2][0] = colCenter;
	models[SHAPE_S][3][0] = colCenter - 1;
	models[SHAPE_S][4][0] = colCenter + 0.5f;

	models[SHAPE_S][0][1] = rowSize;
	models[SHAPE_S][1][1] = rowSize;
	models[SHAPE_S][2][1] = rowSize - 1;
	models[SHAPE_S][3][1] = rowSize - 1;
	models[SHAPE_S][4][1] = rowSize + 0.5f;

	models[SHAPE_S][0][2] = depthCenter;
	models[SHAPE_S][1][2] = depthCenter;
	models[SHAPE_S][2][2] = depthCenter;
	models[SHAPE_S][3][2] = depthCenter;
	models[SHAPE_S][4][2] = depthCenter + 0.5f;

	//Tower Right shape
	models[SHAPE_T_RIGHT][0][0] = colCenter;
	models[SHAPE_T_RIGHT][1][0] = colCenter;
	models[SHAPE_T_RIGHT][2][0] = colCenter;
	models[SHAPE_T_RIGHT][3][0] = colCenter - 1;
	models[SHAPE_T_RIGHT][4][0] = colCenter + 0.5f;

	models[SHAPE_T_RIGHT][0][1] = rowSize;
	models[SHAPE_T_RIGHT][1][1] = rowSize - 1;
	models[SHAPE_T_RIGHT][2][1] = rowSize - 1;
	models[SHAPE_T_RIGHT][3][1] = rowSize - 1;
	models[SHAPE_T_RIGHT][4][1] = rowSize - 0.5f;

	models[SHAPE_T_RIGHT][0][2] = depthCenter;
	models[SHAPE_T_RIGHT][1][2] = depthCenter;
	models[SHAPE_T_RIGHT][2][2] = depthCenter - 1;
	models[SHAPE_T_RIGHT][3][2] = depthCenter - 1;
	models[SHAPE_T_RIGHT][4][2] = depthCenter + 0.5f;

	//Tower Left shape
	models[SHAPE_T_LEFT][0][0] = colCenter;
	models[SHAPE_T_LEFT][1][0] = colCenter;
	models[SHAPE_T_LEFT][2][0] = colCenter;
	models[SHAPE_T_LEFT][3][0] = colCenter + 1;
	models[SHAPE_T_LEFT][4][0] = colCenter + 0.5f;

	models[SHAPE_T_LEFT][0][1] = rowSize;
	models[SHAPE_T_LEFT][1][1] = rowSize - 1;
	models[SHAPE_T_LEFT][2][1] = rowSize - 1;
	models[SHAPE_T_LEFT][3][1] = rowSize - 1;
	models[SHAPE_T_LEFT][4][1] = rowSize - 0.5f;

	models[SHAPE_T_LEFT][0][2] = depthCenter;
	models[SHAPE_T_LEFT][1][2] = depthCenter;
	models[SHAPE_T_LEFT][2][2] = depthCenter - 1;
	models[SHAPE_T_LEFT][3][2] = depthCenter - 1;
	models[SHAPE_T_LEFT][4][2] = depthCenter + 0.5f;

	//Tripod shape
	models[SHAPE_TRIPOD][0][0] = colCenter - 1;
	models[SHAPE_TRIPOD][1][0] = colCenter;
	models[SHAPE_TRIPOD][2][0] = colCenter;
	models[SHAPE_TRIPOD][3][0] = colCenter;
	models[SHAPE_TRIPOD][4][0] = colCenter + 0.5f;

	models[SHAPE_TRIPOD][0][1] = rowSize - 1;
	models[SHAPE_TRIPOD][1][1] = rowSize - 1;
	models[SHAPE_TRIPOD][2][1] = rowSize;
	models[SHAPE_TRIPOD][3][1] = rowSize - 1;
	models[SHAPE_TRIPOD][4][1] = rowSize - 0.5f;

	models[SHAPE_TRIPOD][0][2] = depthCenter;
	models[SHAPE_TRIPOD][1][2] = depthCenter;
	models[SHAPE_TRIPOD][2][2] = depthCenter;
	models[SHAPE_TRIPOD][3][2] = depthCenter - 1;
	models[SHAPE_TRIPOD][4][2] = depthCenter + 0.5f;

}

Tetromino* ModelGenerator::createTetro() {
	int shapeType = rand() % 8;
// DEBUG
//	shapeType = SHAPE_I;
	vec4 color, points[T_POINTS], pivotPoint, tempPoints[8];
	switch(shapeType) {
		case SHAPE_I:
			// Türkis
			color[0] = 0;
			color[1] = 1;
			color[2] = 1;
			color[3] = 1;
			break;
		case SHAPE_L:
			// Orange
			color[0] = 1;
			color[1] = 0.5;
			color[2] = 0;
			color[3] = 1;
			break;
		case SHAPE_S:
			// Grün
			color[0] = 0;
			color[1] = 1;
			color[2] = 0;
			color[3] = 1;
			break;
		case SHAPE_SQ:
			// Gelb
			color[0] = 1;
			color[1] = 1;
			color[2] = 0;
			color[3] = 1;
			break;
		case SHAPE_T:
			// Lila
			color[0] = 1;
			color[1] = 0;
			color[2] = 1;
			color[3] = 1;
			break;
		case SHAPE_T_LEFT:
			// Rot
			color[0] = 1;
			color[1] = 0;
			color[2] = 0;
			color[3] = 1;
			break;
		case SHAPE_T_RIGHT:
			// Blau
			color[0] = 0;
			color[1] = 0;
			color[2] = 1;
			color[3] = 1;
			break;
		case SHAPE_TRIPOD:
			// Hell Grün
			color[0] = 0.5;
			color[1] = 1;
			color[2] = 0;
			color[3] = 1;
			break;
	}

	int blockNumber = 0;
	for (int i = 0; i < T_POINTS; i = i + T_POINTS_PER_BLOCK) {
		for (int j = 0; j < 2; j++) {
			tempPoints[j * 4][0] = models[shapeType][blockNumber][0];
			tempPoints[j * 4][1] = models[shapeType][blockNumber][1] + j;
			tempPoints[j * 4][2] = models[shapeType][blockNumber][2];
			tempPoints[j * 4][3] = 1.0f;

			tempPoints[1 + j * 4][0] = models[shapeType][blockNumber][0];
			tempPoints[1 + j * 4][1] = models[shapeType][blockNumber][1] + j;
			tempPoints[1 + j * 4][2] = models[shapeType][blockNumber][2] + 1;
			tempPoints[1 + j * 4][3] = 1.0f;

			tempPoints[2 + j * 4][0] = models[shapeType][blockNumber][0] + 1;
			tempPoints[2 + j * 4][1] = models[shapeType][blockNumber][1] + j;
			tempPoints[2 + j * 4][2] = models[shapeType][blockNumber][2];
			tempPoints[2 + j * 4][3] = 1.0f;

			tempPoints[3 + j * 4][0] = models[shapeType][blockNumber][0] + 1;
			tempPoints[3 + j * 4][1] = models[shapeType][blockNumber][1] + j;
			tempPoints[3 + j * 4][2] = models[shapeType][blockNumber][2] + 1;
			tempPoints[3 + j * 4][3] = 1.0f;
		}
		calculateTetrominoBlock(points, tempPoints, i);
		blockNumber++;
	}

	pivotPoint[0] = models[shapeType][4][0];
	pivotPoint[1] = models[shapeType][4][1];
	pivotPoint[2] = models[shapeType][4][2];
	pivotPoint[3] = 1.0f;
	Tetromino *tetro = new Tetromino(points, color, pivotPoint);
	return tetro;

}