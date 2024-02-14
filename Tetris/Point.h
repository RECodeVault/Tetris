#pragma once
#include <sstream>
#include <iostream>

class Point {
private:
	int x;
	int y;
public:
	/// <summary>
	/// costructor for point
	/// </summary>
	Point() {
		x = 0;
		y = 0;
	}

	/// <summary>
	/// Overloaded constructor for point
	/// </summary>
	/// <param name="x">integer x</param>
	/// <param name="y">integer y</param>
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	/// <summary>
	/// gets x
	/// </summary>
	/// <returns>integer x</returns>
	int getX() const {
		return x;
	}

	/// <summary>
	/// gets y
	/// </summary>
	/// <returns>integer y</returns>
	int getY() const {
		return y;
	}

	/// <summary>
	/// sets y
	/// </summary>
	/// <param name="y">integer y</param>
	void setY(int y) {
		this->y = y;
	}

	/// <summary>
	/// sets x
	/// </summary>
	/// <param name="x">integer x</param>
	void setX(int x) {
		this->x = x;
	}

	/// <summary>
	/// sets x and y
	/// </summary>
	/// <param name="x">integer x</param>
	/// <param name="y">integer y</param>
	void setXY(int x, int y);

	/// <summary>
	/// swap x and y
	/// </summary>
	void swapXY();

	/// <summary>
	/// multiply x by some factor
	/// </summary>
	/// <param name="factor">integer of result</param>
	void multiplyX(int factor) {
		x *= factor;
	}

	/// <summary>
	/// multiply y by some factor
	/// </summary>
	/// <param name="factor">integer of result</param>
	void multiplyY(int factor) {
		y *= factor;
	}

	/// <summary>
	/// To string function that returns the varialbes in string form
	/// </summary>
	/// <returns></returns>
	std::string toString() const;
};