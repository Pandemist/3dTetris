#ifndef H_GAME
#define H_GAME

#include "TetrominoTransforms.h"
#include "Grid.h"
#include "ModelGenerator.h"

#define GRID_ROW 23
#define GRID_COL 6
#define GRID_DEPTH 6
#define ANIMATE_STEPS 5

class Game {
public:
	Game();

	void logic();
	bool getTetro(vec4 *points, vec4 *color);
	void getBlocks(vec4 *points, vec4 *colors, int &size);
	bool getTetroTrans(mat4 &transformation);
	void moveTetrominoX(int x);
	void moveTetrominoY(int y);
	void moveTetrominoZ(int z);
	void rotateTetromino(int rotate, int rotationType);
	void moveTetrominoBottom();
	int getScore();
	bool isGameOver();
	void getTetroCenters(vec4 *points);
	bool isTetroFalling();
	void getGridCenters(vec4 *points, vec4 *colors, int &size);
	int getMovementToBottom();

	Tetromino *currTetro;
	bool animating;
	bool isPaused;
private:
	void checkTransformation();
	void checkAnimation();
	void getBlocksPoints(vec4 *points, int offset, int row, int col, int depth);
	void getBlockColors(vec4 *colors, int offset, int row, int col, int depth);

	bool shapeInFlight, moveToBottom, gameStarted, newblock;
	float moveX, moveY, moveZ;
	float animateX, animateY, animateZ;
	int rotationType, rotate, score, prevScore;
	int animationState, animationRotationType;
	float animationRotation;
};

#endif
