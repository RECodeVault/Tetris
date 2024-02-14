#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "Gameboard.h"
#include "GridTetromino.h"
#include <SFML/Graphics.hpp>
#include <cassert>


class TetrisGame
{
public:
	// STATIC CONSTANTS
	static const int BLOCK_WIDTH;			  // pixel width of a tetris block, init to 32
	static const int BLOCK_HEIGHT;			  // pixel height of a tetris block, int to 32
	static const double MAX_SECONDS_PER_TICK; // the slowest "tick" rate (in seconds), init to 0.75
	static const double MIN_SECONDS_PER_TICK; // the fastest "tick" rate (in seconds), init to 0.20

private:	
	// MEMBER VARIABLES

	// State members ---------------------------------------------
	int score;					// the current game score.
    Gameboard board;			// the gameboard (grid) to represent where all the blocks are.
    GridTetromino nextShape;	// the tetromino shape that is "on deck".
    GridTetromino currentShape;	// the tetromino that is currently falling.
	
	// Graphics members ------------------------------------------
	sf::Sprite& blockSprite;		// the sprite used for all the blocks.
	sf::RenderWindow& window;		// the window that we are drawing on.
	const Point gameboardOffset;	// pixel XY offset of the gameboard on the screen
	const Point nextShapeOffset;	// pixel XY offset to the nextShape

	sf::Font scoreFont;				// SFML font for displaying the score.
	sf::Text scoreText;				// SFML text object for displaying the score
									
	// Time members ----------------------------------------------
	// Note: a "tick" is the amount of time it takes a block to fall one line.
	double secondsPerTick = MAX_SECONDS_PER_TICK; // the seconds per tick (changes depending on score)	

	double secondsSinceLastTick{ 0.0 };			// update this every game loop until it is >= secsPerTick,
												// we then know to trigger a tick.  Reduce this var (by a tick) & repeat.
	bool shapePlacedSinceLastGameLoop{ false };	// Tracks whether we have placed (locked) a shape on
												// the gameboard in the current gameloop	
public:
	// MEMBER FUNCTIONS

	TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset)
	: window(window), blockSprite(blockSprite), gameboardOffset(gameboardOffset), nextShapeOffset(nextShapeOffset) {
		reset();
		// setup our font for drawing the score
		if (!scoreFont.loadFromFile("font/RedOctober.ttf"))
		{
			assert(false && "Missing font: RedOctober.ttf");
		};
		scoreText.setFont(scoreFont);
		scoreText.setCharacterSize(18);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(425, 325);
	}
	/// <summary>
	/// Draws the shape
	/// </summary>
	void draw();

	/// <summary>
	///	Event activated on key press
	/// </summary>
	void onKeyPressed(const sf::Event& event);

	/// <summary>
	/// Processes the game loop
	/// </summary>
	void processGameLoop(float secondsSinceLastLoop);

	/// <summary>
	/// Processes each individual tick
	/// </summary>
	/// <returns>Shape at specified index</returns>
	void tick();

private:

	/// <summary>
	///	Resets the game
	/// </summary>
	/// <returns>Shape at specified index</returns>
	void reset();

	/// <summary>
	/// Picks next shape
	/// </summary>
	void pickNextShape();
	
	/// <summary>
	/// Spawns the next shape
	/// </summary>
	/// <returns>True|False</returns>
	bool spawnNextShape();																	

	/// <summary>
	/// Attempts to rotate and if possible returns true/false
	/// </summary>
	/// <returns>True|False</returns>
	bool attemptRotate(GridTetromino& shape);
   
	/// <summary>
	/// Attempts to rotate and if possible returns true/false
	/// </summary>
	/// <returns>True|False</returns>
	bool attemptMove(GridTetromino& shape, int x, int y);

	/// <summary>
	/// Drops shape to bottom
	/// </summary>
	void drop(GridTetromino& shape);

	/// <summary>
	/// Locks shape to gameboard
	/// </summary>
	void lock(const GridTetromino& shape);
	
	// Graphics methods ==============================================
	
	/// <summary>
	/// Draws block
	/// </summary>
	void drawBlock(const Point& topLeft, int xOffset, int yOffset, const TetColor& color);
			
	/// <summary>
	/// Draws gameboard
	/// </summary>
	void drawGameboard();
	
	/// <summary>
	/// Draws the entire tetromino
	/// </summary>
	void drawTetromino(const GridTetromino& tetromino, const Point& topLeft);
	
	/// <summary>
	/// Updates the score
	/// </summary>
	void updateScoreDisplay();

	// State & gameplay/logic methods ================================

	/// <summary>
	/// Checks for if the position is legal
	/// </summary>
	/// <returns>True|False</returns>
	bool isPositionLegal(const GridTetromino& shape) const;

	/// <summary>
	/// Checks for if it is within border
	/// </summary>
	/// <returns>True|False</returns>
	bool isWithinBorders(const GridTetromino& shape) const;

	/// <summary>
	/// Determines the game speed
	/// </summary>
	void determineSecondsPerTick();


};

#endif /* TETRISGAME_H */

