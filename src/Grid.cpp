#include "Grid.h"
#include <stdio.h>

Grid::Grid(int row, int col, int depth) {
	numOfRows = row;
	numOfColumns = col;
	depthSize = depth;

// Größe des 3D Spielfeldvektors in abhängigkeit zu den Konstanten
	grid.resize(numOfRows);
	for(int r = 0; r < numOfRows; r++) {
		grid[r].resize(numOfColumns);
		for(int c = 0; c < numOfColumns; c++) {
			grid[r][c].resize(depthSize);
			for(int d = 0; d < depthSize; d++) {
				grid[r][c][d] = NULL;
			}
		}
	}
}

bool Grid::isPositionFilled(int row, int col, int depth) {
	if(isGridInSpace(row, col, depth)) {
		return (grid[row][col][depth] != NULL);
	}
	return true;
}

void Grid::addBlocks(vec4 points[], vec4 color, int size) {
	for(int i = 0; i < size; i = i + T_POINTS_PER_BLOCK) {
		Block *block = new Block;

		block->color[0] = color[0];
		block->color[1] = color[1];
		block->color[2] = color[2];
		block->color[3] = color[3];

		int col = floor(points[i][0] + 0.5);
		int row = floor(points[i][1] + 0.5);
		int depth = floor(points[i][2] + 0.5);
		getMinXY(points, i, row, col, depth);
		grid[row][col][depth] = block;
	}
}

void Grid::getMinXY(vec4 points[], int offset, int &row, int &col, int &depth) {
	for(int i = 0; i < T_POINTS_PER_BLOCK; i++) {
		if(floor(points[offset + i][1] + .5) < row) {
			row = floor(points[offset + i][1] + 0.5);
		}

		if(floor(points[offset + i][0] + .5) < col) {
			col = floor(points[offset + i][0] + 0.5);
		}

		if(floor(points[offset + i][2] + .5) < depth) {
			depth = floor(points[offset + i][2] + 0.5);
		}

	}
}

bool Grid::canAddBlocks(vec4 points[], int size) {
	int row, col, depth;
	for(int i = 0; i < size; i = i + T_POINTS_PER_BLOCK) {
		row = floor(points[i][1] + 0.5);
		col = floor(points[i][0] + 0.5);
		depth = floor(points[i][2] + 0.5);
		getMinXY(points, i, row, col, depth);

		if(isPositionFilled(row, col, depth)) {
			return false;
		}
	}
	return true;
}

bool Grid::isRowFilled(int row) {
	for(int col = 0; col < numOfColumns; col++) {
		for(int depth = 0; depth < depthSize; depth++) {
			if(grid[row][col][depth] == NULL) {
				return false;
			}
		}
	}
	return true;
}

int Grid::checkForFullRows() {
	int rowsRemoved = 0;
	for(int row = numOfRows - 1; row >= 0; row--) {
		if(isRowFilled(row)) {
			removeRow(row);
			rowsRemoved++;
		}
	}
	return rowsRemoved;
}

void Grid::removeRow(int row) {
	if(row < numOfRows) {
		for(int col = 0; col < numOfColumns; col++) {
			for(int depth = 0; depth < depthSize; depth++) {
				delete grid[row][col][depth];
				grid[row][col][depth] = NULL;
			}
		}
	}

	for(int newRow = row; newRow < numOfRows - 1; newRow++) {
		for(int col = 0; col < numOfColumns; col++) {
			for(int depth = 0; depth < depthSize; depth++) {
				grid[newRow][col][depth] = grid[newRow + 1][col][depth];
			}
		}
	}
}

int Grid::getNumOfRows() {
	return numOfRows;
}

int Grid::getNumOfColumns() {
	return numOfColumns;
}

int Grid::getDepthSize() {
	return depthSize;
}

bool Grid::isGridInSpace(int row, int col, int depth) {
	if(row > -1 && row < numOfRows) {
		if(col > -1 && col < numOfColumns) {
			if(depth > -1 && depth < depthSize) {
				return true;
			}
		}
	}
	return false;
}