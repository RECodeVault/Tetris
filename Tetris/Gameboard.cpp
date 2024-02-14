#include <iostream>
#include <vector>
#include <iomanip>
#include "Point.h"
#include "Gameboard.h"
#include <cassert>

void Gameboard::empty() {
	for (int i = 0; i < MAX_Y; i++) {
		fillRow(i, EMPTY_BLOCK); // fills the row with EMPTY_BLOCK
	}
}

void Gameboard::printToConsole() const {
	for (int i = 0; i < MAX_Y; i++) { // iterate through the grid and print out the contents if there is any 
		for (int j = 0; j < MAX_X; j++) {
			std::cout << std::setw(2);
			if (grid[i][j] == EMPTY_BLOCK) {
				std::cout << '.';
			}
			else {
				std::cout << grid[i][j];
			}
		}
		std::cout << '\n';
	}
}

int Gameboard::getContent(const Point& point) const {
	assert(isValidPoint(point));
	return grid[point.getY()][point.getX()];
}

int Gameboard::getContent(int x, int y) const {
	assert(isValidPoint(x, y));
	return grid[y][x];
}

void Gameboard::setContent(const Point& point, int content) {
	if (isValidPoint(point.getX(), point.getY())) {
		grid[point.getY()][point.getX()] = content;
	}
}

void Gameboard::setContent(int x, int y, int content) {
	if (isValidPoint(x, y)) {
		grid[y][x] = content;
	}
}

void Gameboard::setContent(std::vector<Point>& locations, int content) {
	for (const auto& pt: locations) {
		setContent(pt, content);
	}
}

bool Gameboard::areAllLocsEmpty(const std::vector<Point>& locations) const {
	for (int i = 0; i < locations.size(); i++) {
		const Point point = locations[i];
		if (isValidPoint(point.getX(), point.getY())) {
			if (getContent(point) != EMPTY_BLOCK) {
				return false;
			}
		}
	}
	return true; 
}

int Gameboard::removeCompletedRows() {
	std::vector<int> completedRows = getCompletedRowIndices(); // assign the completed row to the new vector
	removeRows(completedRows); // remove the row completely
	return completedRows.size();
}

Point Gameboard::getSpawnLoc() {
	return spawnLoc;
}

bool Gameboard::isValidPoint(const Point& point) const {
	return point.getX() >= 0 && point.getX() < MAX_X && point.getY() >= 0 && point.getY() < MAX_Y;
}

bool Gameboard::isValidPoint(int x, int y) const {
	return x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y;
}

bool Gameboard::isRowCompleted(int rowIndex) const {
	assert(rowIndex >= 0 && rowIndex < MAX_Y); // checks for if it is in range

	for (int i = 0; i < MAX_X; i++) { 
		if (grid[rowIndex][i] == EMPTY_BLOCK) {
			return false;
		}
	}
	return true;
}

void Gameboard::fillRow(int rowIndex, int content) {
	assert(rowIndex >= 0 && rowIndex < MAX_Y); // checks for if it is in range

	for (int i = 0; i < MAX_X; i++) { // iterates through and fills row index with content
		grid[rowIndex][i] = content;
	}
}

std::vector<int> Gameboard::getCompletedRowIndices() const {
	std::vector<int> completedRows;

	for (int i = 0; i < MAX_Y; i++) {
		if (isRowCompleted(i)) {
			completedRows.push_back(i);
		}
	}
	return completedRows;
}

void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex) {

	for (int i = 0; i < MAX_X; i++) { // copies row contents into the target row
		grid[targetRowIndex][i] = grid[sourceRowIndex][i];
	}
}

void Gameboard::removeRow(int rowIndex) {
	assert(rowIndex >= 0 && rowIndex < MAX_Y);
	for (int i = rowIndex - 1; i >= 0; i--) {
		copyRowIntoRow(i, i + 1);
	}
	fillRow(0, EMPTY_BLOCK);
}

void Gameboard::removeRows(std::vector<int>& rowIndices) {
	for (int i = 0; i < rowIndices.size(); i++) {
		removeRow(rowIndices[i]); // iterate through rows and delete them
	}
}