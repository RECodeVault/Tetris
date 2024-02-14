#include <iostream>
#include "GridTetromino.h"

void GridTetromino::move(int xOffSet, int yOffSet) {
	gridLoc.setX(gridLoc.getX() + xOffSet);
	gridLoc.setY(gridLoc.getY() + yOffSet);
}

std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const {
    std::vector<Point> mappedBlockLocs;

    for (const Point& blockLoc : Tetromino::blockLocs) {
        mappedBlockLocs.push_back(Point(gridLoc.getX() + blockLoc.getX(), gridLoc.getY() + blockLoc.getY()));
    }
    return mappedBlockLocs;
}