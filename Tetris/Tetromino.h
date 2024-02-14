#pragma once
#include <iostream>
#include <vector>
#include "Point.h"

enum class TetColor { RED, ORANGE, YELLOW, GREEN, BLUE_LIGHT, BLUE_DARK, PURPLE }; // enum class to hold the colors for the enum class TetColor
enum class TetShape { S, Z, L, J, O, I, T, COUNT }; // enum class to hold the shape for the enum class TetShape

class Tetromino {
private:
	TetColor color;
	TetShape shape;
public:
	std::vector<Point> blockLocs{}; // Vector for the blockLocs 
	/// <summary>
	/// Constructor for the Tetromino class
	/// </summary>
	Tetromino()  {
		setShape(TetShape::T);
	}

	/// <summary>
	/// gets the color
	/// </summary>
	/// <returns>Color at specified index</returns>
	TetColor getColor() const {
		return color;
	}

	/// <summary>
	/// gets the shape
	/// </summary>
	/// <returns>Shape at specified index</returns>
	TetShape getShape() const {
		return shape;
	}

	/// <summary>
	/// Sets the shape of the enum class TetShape
	/// </summary>
	/// <param name="shape">Enum class TetShape</param>
	void setShape(const TetShape& shape);

	/// <summary>
	/// Takes vector and alters its points to rotate 90 degrees clockwise
	/// </summary>
	void rotateClockwise();

	/// <summary>
	/// Prints grid and determines if there is a shape point occupying the space
	/// </summary>
	void printToConsole() const;

	static TetShape getRandomShape();

	/// <summary>
	/// Friend class of testSuite so if can run test cases
	/// </summary>
	friend class TestSuite;
};