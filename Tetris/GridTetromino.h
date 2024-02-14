#ifndef GRIDTETROMINO_H
#define GRIDTETROMINO_H

#include "Tetromino.h"

class GridTetromino : public Tetromino
{	
	// MEMBER VARIABLES
private:
	Point gridLoc;	// the [x,y] location of this tetromino on the grid/gameboard. 
					// This loc changes each time the tetromino moves.

public:
	// constructor, initialize gridLoc to 0,0
	GridTetromino() { // sets the default value to 0,0
		gridLoc.setX(0); 
		gridLoc.setY(0);
	}

	Point getGridLoc() const{
		return gridLoc;
	}

	void setGridLoc(int x, int y) { // sets both of the gridLocs to the x, y coords
		gridLoc.setX(x);
		gridLoc.setY(y);
	}

	void setGridLoc(const Point& gridLoc) {
		GridTetromino::gridLoc = gridLoc;
	}
	
	void move(int xOffSet, int yOffSet);

	std::vector<Point> getBlockLocsMappedToGrid() const;

};

#endif GRIDTETROMINO_H 