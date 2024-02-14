#include <iostream>
#include "Tetromino.h"
#include "Point.h"
#include "GridTetromino.h"

void Tetromino::setShape(const TetShape& shape) {
	this->shape = shape;
	this->color = static_cast<TetColor>(shape);
	switch (shape) {
	case TetShape::S:
		blockLocs = { Point(-1, 0), Point(0, 0), Point(0, 1), Point(1, 1) };
		break;
	case TetShape::Z:
		blockLocs = { Point(-1, 1), Point(0, 1), Point(0, 0), Point(1, 0) };
		break;
	case TetShape::L:
		blockLocs = { Point(0, 1), Point(0, 0), Point(0, -1), Point(1, -1) };
		break;
	case TetShape::J:
		blockLocs = { Point(0, 1), Point(0, 0), Point(0, -1), Point(-1, -1) };
		break;
	case TetShape::O:
		blockLocs = { Point(0, 1), Point(1, 1), Point(0, 0), Point(1, 0) };
		break;
	case TetShape::I:
		blockLocs = { Point(0, 2), Point(0, 1), Point(0, 0), Point(0, -1) };
		break;
	case TetShape::T:
		blockLocs = { Point(-1, 0), Point(0, 0), Point(1, 0), Point(0, -1) };
		break;
	}
}

void Tetromino::printToConsole() const {
	for (int y = 3; y > -3; y--) { // traverses through the grid using two for loops
		for (int x = -3; x < 3; x++) {
			bool found{ false };
			for (int i = 0; i < blockLocs.size(); i++) { // loops through the vector and searches if the specified point has any matching values
				if (blockLocs[i].getX() == x && blockLocs[i].getY() == y) {
					found = true;
					break;
				}
			}
			if (!found) {
				std::cout << ".";
			}
			else {
				std::cout << "X";
			}
		}
		std::cout << "\n";
	}
}

void Tetromino::rotateClockwise() {
	if (shape == TetShape::O) {
		return;
	}
	for (int i = 0; i < blockLocs.size(); i++) {
		blockLocs[i].swapXY();
		blockLocs[i].multiplyY(-1);
	}
}

TetShape Tetromino::getRandomShape() {
	int randShape = rand() % static_cast<int>(TetShape::COUNT);
	TetShape shape = static_cast<TetShape>(randShape);
	return shape;
}