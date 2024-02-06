#include "ViewGrid.h"

ViewGrid::ViewGrid() {
	calculatePartialGridFaces();
	calculatePartialGrid(0);
}

void ViewGrid::calculatePartialGrid(float rotationY) {
	setDisplayedFaces(rotationY);
	int index = 0;
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < faceSizes[i]; j++) {
			if(displayFaces[i]) {
				partialGrid[index] = gridFaces[i][j];

				if(i == 5) {
					colorBuffer[index] = vec4(0.7, 0.7, 0.7, 1);
				}else{
					colorBuffer[index] = vec4(1.0, 1.0, 1.0, 1);
				}

				index++;
			}
		}
	}
	partialGridSize = index + 1;
}

int ViewGrid::getSize() {
	return partialGridSize;
}

void ViewGrid::setDisplayedFaces(float rotationY) {

	//Check to show the back face
	displayFaces[0] = (rotationY < 90 || rotationY > 270);

	//Check to show the front face
	displayFaces[1] = (rotationY > 90 && rotationY < 270);

	//Check to show the left face
	displayFaces[2] = (rotationY < 0 || rotationY > 180);

	//Check to show the right face
	displayFaces[3] = (rotationY > 0 && rotationY < 180);

	//Check to show the top face
	displayFaces[4] = false;

	//Check to show the bottom face
	displayFaces[5] = true;
}

void ViewGrid::calculatePartialGridFaces() {
	int index = 0;

	//Face 1 Back
	for(int row = 0; row <= GRID_ROW; row++) {
		gridFaces[0][index] = vec4(0, row, 0, 1);
		gridFaces[0][index + 1] = vec4(GRID_COL, row, 0, 1);
		index += 2;
	}
	for(int col = 0; col <= GRID_COL; col++) {
		gridFaces[0][index] = vec4(col, 0, 0, 1);
		gridFaces[0][index + 1] = vec4(col, GRID_ROW, 0, 1);
		index += 2;
	}
	faceSizes[0] = index;
	index = 0;

	//Face 2 Front
	for(int row = 0; row <= GRID_ROW; row++) {
		gridFaces[1][index] = vec4(0, row, GRID_DEPTH, 1);
		gridFaces[1][index + 1] = vec4(GRID_COL, row, GRID_DEPTH, 1);
		index += 2;
	}
	for(int col = 0; col <= GRID_COL; col++) {
		gridFaces[1][index] = vec4(col, 0, GRID_DEPTH, 1);
		gridFaces[1][index + 1] = vec4(col, GRID_ROW, GRID_DEPTH, 1);
		index += 2;
	}
	faceSizes[1] = index;
	index = 0;

	//Face 3 Left
	for(int row = 0; row <= GRID_ROW; row++) {
		gridFaces[2][index] = vec4(0, row, 0, 1);
		gridFaces[2][index + 1] = vec4(0, row, GRID_DEPTH, 1);
		index += 2;
	}
	for(int depth = 0; depth <= GRID_DEPTH; depth++) {
		gridFaces[2][index] = vec4(0, 0, depth, 1);
		gridFaces[2][index + 1] = vec4(0, GRID_ROW, depth, 1);
		index += 2;
	}
	faceSizes[2] = index;
	index = 0;

	//Face 4 Right
	for(int row = 0; row <= GRID_ROW; row++) {
		gridFaces[3][index] = vec4(GRID_COL, row, 0, 1);
		gridFaces[3][index + 1] = vec4(GRID_COL, row, GRID_DEPTH, 1);
		index += 2;
	}
	for(int depth = 0; depth <= GRID_DEPTH; depth++) {
		gridFaces[3][index] = vec4(GRID_COL, 0, depth, 1);
		gridFaces[3][index + 1] = vec4(GRID_COL, GRID_ROW, depth, 1);
		index += 2;
	}
	faceSizes[3] = index;
	index = 0;

	//Face 5 Top
	for(int col = 0; col <= GRID_COL; col++) {
		gridFaces[4][index] = vec4(col, GRID_ROW, 0, 1);
		gridFaces[4][index + 1] = vec4(col, GRID_ROW, GRID_DEPTH, 1);
		index += 2;
	}
	for(int depth = 0; depth <= GRID_DEPTH; depth++) {
		gridFaces[4][index] = vec4(0, GRID_ROW, depth, 1);
		gridFaces[4][index + 1] = vec4(GRID_COL, GRID_ROW, depth, 1);
		index += 2;
	}

	faceSizes[4] = index;
	index = 0;

	//Face 6 Bottom
	for(int col = 0; col <= GRID_COL; col++) {
		gridFaces[5][index] = vec4(col, 0, 0, 1);
		gridFaces[5][index + 1] = vec4(col, 0, GRID_DEPTH, 1);
		index += 2;
	}
	for(int depth = 0; depth <= GRID_DEPTH; depth++) {
		gridFaces[5][index] = vec4(0, 0, depth, 1);
		gridFaces[5][index + 1] = vec4(GRID_COL, 0, depth, 1);
		index += 2;
	}
	faceSizes[5] = index;
}