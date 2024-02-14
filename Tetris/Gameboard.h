#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "Point.h"

class Gameboard
{
	friend int main();
	friend class TestSuite;
public:
	// CONSTANTS
	static const int MAX_X = 10;		// gameboard x dimension
	static const int MAX_Y = 19;		// gameboard y dimension
	static const int EMPTY_BLOCK = -1;	// contents of an empty block

private:
	// MEMBER VARIABLES -------------------------------------------------

	// the gameboard - a grid of X and Y offsets.  
	//  ([0][0] is top left, [MAX_Y-1][MAX_X-1] is bottom right) 
	int grid[MAX_Y][MAX_X];
	// the gameboard offset to spawn a new tetromino at.
	const Point spawnLoc{ MAX_X / 2, 0 };
	
public:	
	// METHODS -------------------------------------------------
	// 
	// constructor - empty() the grid
	Gameboard() {
		empty();
	}

	/// <summary>
	/// Fills board with EMPTY_BLOCK
	/// </summary>
	void empty();

	/// <summary>
	/// Prints grid contents to the board
	/// </summary>
	void printToConsole() const;

	/// <summary>
	/// Gets content a the given point
	/// </summary>
	/// <param name="point">Reference to point</param>
	/// <returns>Content at given point</returns>
	int getContent(const Point& point) const;				

	/// <summary>
	/// Gets the content at the given point
	/// </summary>
	/// <param name="x">integer x</param>
	/// <param name="y">integer y</param>
	/// <returns>Content at the given point</returns>
	int getContent(int x, int y) const;			

	/// <summary>
	/// Sets content at the given point if valid
	/// </summary>
	/// <param name="point">Reference to point</param>
	/// <param name="location">integer location</param>
	void setContent(const Point& point, int location);	
	
	/// <summary>
	/// Sets content at the given point if valid
	/// </summary>
	/// <param name="x">integer x</param>
	/// <param name="y">integer y</param>
	/// <param name="location">integer location</param>
	void setContent(int x, int y, int location);		
	
	/// <summary>
	/// Sets the content at the given point if valid
	/// </summary>
	/// <param name="locations">Vector of points</param>
	/// <param name="setContent">integer content</param>
	void setContent(std::vector<Point>& locations, int setContent);		

	/// <summary>
	/// Checks for of all points passed in are empty
	/// </summary>
	/// <param name="locaitons">Vector of points</param>
	/// <returns>true|false</returns>
	bool areAllLocsEmpty(const std::vector<Point>& locations) const;

	/// <summary>
	/// Remove all completed rows
	/// </summary>
	/// <returns>The amount removed</returns>
	int removeCompletedRows();

	/// <summary>
	/// Gets the spawn location 
	/// </summary>
	/// <returns>Spawn locations</returns>
	Point getSpawnLoc();

private:

	/// <summary>
	/// If the given point is valid
	/// </summary>
	/// <param name="point">Reference to a point</param>
	/// <returns>true|false</returns>
	bool isValidPoint(const Point& point) const;

	/// <summary>
	/// IF the given point is valid
	/// </summary>
	/// <param name="x">integer x</param>
	/// <param name="y">integer y</param>
	/// <returns>true|false</returns>
	bool isValidPoint(int x, int y) const;

	/// <summary>
	/// Checks for if a row is full
	/// </summary>
	/// <param name="rowIndex">integer rowIndex</param>
	/// <returns>true|false</returns>
	bool isRowCompleted(int rowIndex) const;	
	
	/// <summary>
	/// Fills a row
	/// </summary>
	/// <param name="rowIndex">integer rowIndex</param>
	/// <param name="content">integer content</param>
	void fillRow(int rowIndex, int content);
	
	/// <summary>
	/// Scan the board for completed rows
	/// </summary>
	/// <returns>completed row</returns>
	std::vector<int> getCompletedRowIndices() const;				

	/// <summary>
	/// Copy row contents into target rowIndex
	/// </summary>
	/// <param name="sourceRowIndex">integer sourceRowIndex</param>
	/// <param name="targetRowIndex">integer targetRowIndex</param>
	void copyRowIntoRow(int sourceRowIndex, int targetRowIndex);
		
	/// <summary>
	/// removes row
	/// </summary>
	/// <param name="rowIndex">integer rowIndex</param>
	void removeRow(int rowIndex);

	/// <summary>
	/// removes rows
	/// </summary>
	/// <param name="rowIndices">vector of rowIndices</param>
	void removeRows(std::vector<int>& rowIndices);
};

#endif  GAMEBOARD_H 

