#include <iostream>
#include "Point.h"

void Point::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}

void Point::swapXY() {
	int temp = x;
	x = y;
	y = temp;
}

std::string Point::toString() const {
	std::stringstream ss;
	ss << "[" << x << "," << y << "]";
	std::string str = ss.str();
	return str;
}