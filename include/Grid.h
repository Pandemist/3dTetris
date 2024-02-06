#ifndef GRID_H
#define GRID_H

#include <vector>
#include <stdio.h>
#include "Tetromino.h"
#include "Angel.h"

using namespace std;

struct Block {
	vec4 color;
};

class Grid {
public:
	Grid(int row, int col, int depth);

	int checkForFullRows();
	bool isPositionFilled(int row, int col, int depth);
	bool isRowFilled(int row);
	void addBlocks(vec4 points[], vec4 color, int size);
	bool canAddBlocks(vec4 points[], int size);
	int getNumOfRows();
	int getNumOfColumns();
	int getDepthSize();

	vector<vector<vector<Block*>>> grid;
private:
	int numOfRows;
	int numOfColumns;
	int depthSize;

	void removeRow(int rowIndex);
	void getMinXY(vec4 points[], int offset, int &row, int &col, int &depth);
	bool isGridInSpace(int row, int col, int depth);
};

#endif
