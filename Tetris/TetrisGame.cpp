#include "TetrisGame.h"

const int TetrisGame::BLOCK_WIDTH{ 32 };			  // pixel width of a tetris block, init to 32
const int TetrisGame::BLOCK_HEIGHT{ 32 };			  // pixel height of a tetris block, int to 32
const double TetrisGame::MAX_SECONDS_PER_TICK{ 0.75 }; // the slowest "tick" rate (in seconds), init to 0.75
const double TetrisGame::MIN_SECONDS_PER_TICK{ 0.20 }; // the fastest "tick" rate (in seconds), init to 0.20

// MEMBER FUNCTIONS

void TetrisGame::draw() {
	drawGameboard();
	drawTetromino(currentShape, gameboardOffset);
	drawTetromino(nextShape, nextShapeOffset);
	window.draw(scoreText);
}

void TetrisGame::onKeyPressed(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Up:
			attemptRotate(currentShape);
			break;
		case sf::Keyboard::Left:
			attemptMove(currentShape, -1, 0);
			break;
		case sf::Keyboard::Right:
			attemptMove(currentShape, 1, 0);
			break;
		case sf::Keyboard::Down:
			if (!attemptMove(currentShape, 0, 1)) {
				lock(currentShape);
			}
			break;
		case sf::Keyboard::Space:
			drop(currentShape);
		break;
		}	
	}
}

void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
	secondsSinceLastTick += secondsSinceLastLoop;
	if (secondsSinceLastTick > secondsPerTick) {
		tick();
		secondsSinceLastTick -= secondsPerTick;
	}
	if (shapePlacedSinceLastGameLoop) {
		shapePlacedSinceLastGameLoop = false;
		if (spawnNextShape()) {
			pickNextShape();
			score += 100 * board.removeCompletedRows();
			updateScoreDisplay();
			determineSecondsPerTick();
		}
		else {
			reset();
		}
	}
}

void TetrisGame::tick() {
	if (!attemptMove(currentShape, 0, 1)) {
		lock(currentShape);
	}
}

void TetrisGame::reset() {
	score = 0;
	secondsPerTick = MAX_SECONDS_PER_TICK;
	updateScoreDisplay();
	determineSecondsPerTick();
	board.empty();
	pickNextShape();
	spawnNextShape();
	pickNextShape();
}

void TetrisGame::pickNextShape() {
	nextShape.setShape(nextShape.getRandomShape());
}

bool TetrisGame::spawnNextShape() {
	currentShape.setShape(nextShape.getShape());
	currentShape.setGridLoc(board.getSpawnLoc());
	return isPositionLegal(currentShape);
}

bool TetrisGame::attemptRotate(GridTetromino& shape) {
	GridTetromino temp = shape;
	temp.rotateClockwise();
	if (isPositionLegal(temp)) {
		shape.rotateClockwise();
		return true;
	}
	return false;
}

bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) {
	GridTetromino temp = shape;
	temp.move(x, y);
	if (isPositionLegal(temp)) {
		shape.move(x, y);
		return true;
	}
	return false;
}

void TetrisGame::drop(GridTetromino& shape) {
	while (true) {
		if (!attemptMove(shape, 0, 1)) {
			lock(shape);
			return;
		}
	}
}

void TetrisGame::lock(const GridTetromino& shape) { 
	std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();
	board.setContent(mappedLocs, static_cast<int>(shape.getColor()));
	shapePlacedSinceLastGameLoop = true;
}

// Graphics methods ==============================================

void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, const TetColor& color) {
	blockSprite.setTextureRect(sf::IntRect(static_cast<int>(color) * 32, 0, 32, 32));
	blockSprite.setPosition(sf::Vector2f(xOffset * BLOCK_WIDTH + topLeft.getX(), yOffset * BLOCK_HEIGHT + topLeft.getY()));
	TetrisGame::window.draw(blockSprite);
}

void TetrisGame::drawGameboard() {
	for (int x = 0; x < Gameboard::MAX_X; x++) { // iterate through the gameboard and draw the block at the filled spaces
		for (int y = 0; y < Gameboard::MAX_Y; y++) {
			if (board.getContent(x, y) != Gameboard::EMPTY_BLOCK) {
				int numColor = board.getContent(x, y);
				TetColor color = static_cast<TetColor>(numColor);
				drawBlock(gameboardOffset, x, y, color);
			}
		}
	}
}

void TetrisGame::drawTetromino(const GridTetromino& tetromino, const Point& topLeft) {
	for (const auto& block : tetromino.getBlockLocsMappedToGrid()) {
		int xOffset = block.getX();
		int yOffset = block.getY();

		TetColor color = tetromino.getColor();
		if (yOffset >= 0 || topLeft.getX() == nextShapeOffset.getX() && topLeft.getY() == nextShapeOffset.getY()) { // draw block if the blocks are in the valid borders, otherwise ignore drawing it
			drawBlock(topLeft, xOffset, yOffset, color);
		}
	}
}

void TetrisGame::updateScoreDisplay() {
	std::stringstream ss;
	ss << "Score: " << score;
	std::string str = ss.str();
	scoreText.setString(str);
}

// State & gameplay/logic methods ================================

bool TetrisGame::isPositionLegal(const GridTetromino& shape) const {
	if (isWithinBorders(shape) && board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid())) { // checks for if it is in the border as well as not colliding with another block
		return true;
	}

	return false;
}

bool TetrisGame::isWithinBorders(const GridTetromino& shape) const {
	for (const auto& block : shape.getBlockLocsMappedToGrid()) {
		int x = block.getX();
		int y = block.getY();

		if (x < 0 || x >= Gameboard::MAX_X || y >= Gameboard::MAX_Y) { // check to be between the left, right and bottom border
			return false;
		}
	}

	return true;
}

void TetrisGame::determineSecondsPerTick() {
	static double scoreMultiplier = 0.0001; // base score multiplier, make it static so it extends its durability
	double adjustedSecsPerTick = MAX_SECONDS_PER_TICK - (score * scoreMultiplier); // multiply the score wiht the score mltiplier and then subtract it to the ticks
	scoreMultiplier += 0.0001; // increment the score multiplier to speed up the game

	if (adjustedSecsPerTick < MIN_SECONDS_PER_TICK) { // if it dips below the fastest tick speed
		adjustedSecsPerTick = MIN_SECONDS_PER_TICK;
	}

	secondsPerTick = adjustedSecsPerTick; // assign the adjusted tick speed
}