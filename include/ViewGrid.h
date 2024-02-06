#ifndef H_VIEWING_GRID
#define H_VIEWING_GRID

#include "Game.h"

#define VG_MAX_GRID_SIZE GRID_COL * GRID_ROW * GRID_DEPTH
#define VG_NUMBER_OF_FACES 6

class ViewGrid {
public:
	ViewGrid();
	void getGridPoints(float rotation, vec4 *buffer, int &size, int gridType);
	void getGridColor(vec4 *buffer);
	int getSize();

	vec4 partialGrid[VG_MAX_GRID_SIZE];
	vec4 colorBuffer[VG_MAX_GRID_SIZE];
	void calculatePartialGrid(float rotationY);

private:
	void setDisplayedFaces(float rotationY);
	void calculatePartialGridFaces();
	int partialGridSize;

	vec4 gridFaces[6][GRID_COL * GRID_ROW];
	int faceSizes[6];
	bool displayFaces[6];
};

#endif
