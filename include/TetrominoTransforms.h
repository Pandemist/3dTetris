#ifndef TETROMINO_TRANSFORMS_H
#define TETROMINO_TRANSFORMS_H

#include "Tetromino.h"
#include "Grid.h"
#include "math.h"
#define CCW 90
#define CW -90
#define ROTATE_X 1
#define ROTATE_Y 2
#define ROTATE_Z 3

bool canAdd(Tetromino &tetro, Grid &grid);
void toBottom(Tetromino &tetro, Grid &grid);
bool move(Tetromino &tetro, Grid &grid, int x, int y, int z);
bool canRotate(Tetromino &tetro, Grid &grid, int theta, int type);
bool canMove(Tetromino &tetro, Grid &grid, int x, int y, int z);
bool rotateTet(Tetromino &tetro, Grid &grid, int theta, int type);
bool shapeAtBottom(Tetromino &tetro, Grid &grid);
void calculateTetrominoBlock(vec4 *points, vec4 *tempPoints, int i);
mat4 getRotationM(float theta, int type, float originX, float originY, float originZ);
int distanceFromBottom(Tetromino &tetro, Grid &grid);

#endif