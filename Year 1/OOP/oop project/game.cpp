//************************************//
//                                    //
//  BREAK BREAKER GAME                //
//  OOP SEMESTER PROJECT              //
//  ALEENA ZAHRA 23I-2514             //
//     BS-DS2B                        //
//                                    //
//************************************//

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <random>
using namespace std;
/////////////
// CLASSES //
/////////////

// Score
class Score
{
	int score;
	int y;

public:
	Score(int y = 0)
	{
		this->score = 0;
		this->y = y;
	}
	void decreaseScore(int amount)
	{
		this->score -= amount;
	}
	void increaseScore(int amount)
	{
		this->score += amount;
	}
	void resetScore()
	{
		this->score = 0;
	}
	int getCurrentScore()
	{
		return this->score;
	}
	void setCurrentScore(int amount)
	{
		this->score = amount;
	}
	void drawScore()
	{
		char scoreString[20];
		sprintf(scoreString, "Score: %d", score);
		DrawString(660, 40 + y, scoreString, colors[WHITE]);
	}
	void drawScoreBar()
	{
		DrawLine(645, 100 + y, 795, 100 + y, 15, colors[BLUE]);
		if (score != 0 && score <= 150)
		{
			DrawLine(645, 100 + y, 645 + score, 100 + y, 15, colors[YELLOW]);
		}
	}
};
// lives
class Lives
{
private:
	int lives;
	int totalLives;
	int y;

public:
	Lives(int y = 0)
	{
		this->lives = 2;
		this->totalLives = 2;
		this->y = y;
	}
	void setLives(int life)
	{
		this->lives = life;
	}
	void decreaseLives()
	{
		this->lives -= 1;
	}
	void increaseLives()
	{
		this->lives += 1;
	}
	void resetLives()
	{
		this->lives = this->totalLives;
	}
	int getCurrentLives()
	{
		return this->lives;
	}
	void drawLives()
	{
		char livesString[20];
		sprintf(livesString, "Lives: %d ", lives);
		DrawString(660, 120 + y, livesString, colors[WHITE]);
	}
};
// paddle
class Paddle
{
private:
	int xVelocity;
	int length;
	int height;
	int xCor;
	int yCor;
	int direction;
	float *color;

public:
	Paddle(int xCor = 280, int yCor = 20, int length = 80, int height = 20, int velocity = 0, int direction = 0)
	{
		this->xCor = xCor;
		this->yCor = yCor;
		this->length = length;
		this->height = height;
		this->xVelocity = velocity;
		this->direction = direction;
		color = colors[WHITE];
	}
	Paddle(const Paddle &paddle)
	{
		this->xCor = paddle.xCor;
		this->yCor = paddle.yCor;
		this->length = paddle.length;
		this->height = paddle.height;
		this->xVelocity = paddle.xVelocity;
		this->direction = paddle.direction;
		this->color = paddle.color;
	}
	/////////////////////////////////getters/////////////////////////////
	int getPaddleXVelocity()
	{
		return this->xVelocity;
	}
	int getPaddleLength()
	{
		return this->length;
	}
	int getPaddleDirection()
	{
		return this->direction;
	}
	int getPaddleHeight()
	{
		return this->height;
	}
	int getPaddleXCor()
	{
		return this->xCor;
	}
	int getPaddleYCor()
	{
		return this->yCor;
	}
	float *getPaddleColor()
	{
		return this->color;
	}
	///////////////////////////////////setters////////////////////////////
	void setPaddleColor(float *color)
	{
		this->color = color;
	}
	void setPaddleXVelocity(int xVelocity)
	{
		this->xVelocity = xVelocity;
	}
	void setPaddleLength(int length)
	{
		this->length = length;
	}
	void setPaddleHeight(int height)
	{
		this->height = height;
	}
	void setPaddleDirection(int direction)
	{
		this->direction = direction;
	}
	void setPaddleXCor(int xCor)
	{
		this->xCor = xCor;
	}
	void setPaddleYCor(int yCor)
	{
		this->yCor = yCor;
	}
	///////////////////////other functions///////////////////////////////////
	void PaddleMovement()
	{
		this->xCor = this->xCor + this->xVelocity * this->direction;
	}
	void drawPaddle()
	{
		DrawRectangle(xCor, yCor, length, height, color);
	}
	void doubleSize()
	{
		length = 2 * length;
	}
	void halfSize()
	{
		length = length / 2;
	}
	~Paddle()
	{
	}

	friend class Powerup;
};
// player class contains score,lives and paddle using COMPOSITION
class Player
{
private:
	int y;
	string name;
	Lives *playerLives; //compositiom
	Paddle *playerPaddle;
	Score *playerScore;

public:
	Player()
	{
		this->name = "";
		this->y = 0;
		this->playerLives = new Lives();
		this->playerPaddle = new Paddle();
		this->playerScore = new Score();
	}

	Player(string name)
	{
		this->name = name;
		this->y = 0;
		this->playerLives = new Lives();
		this->playerPaddle = new Paddle();
		this->playerScore = new Score();
	}

	Player(string name, int x, int y)
	{
		this->name = name;
		this->y = x * 2;
		this->playerLives = new Lives(x * 2);
		this->playerPaddle = new Paddle(x, y);
		this->playerScore = new Score(x * 2);
	}
	void drawPlayerName()
	{
		DrawString(660, 140 + y, name, colors[WHITE]);
	}
	void drawPlayerVariables()
	{
		drawPlayerName();
		playerScore->drawScore();
		playerScore->drawScoreBar();
		playerPaddle->drawPaddle();
		playerLives->drawLives();
	}
	void PlayerPaddleMovement(int x)
	{
		playerPaddle->setPaddleXCor(x);
	}
	int getPaddleXCor()
	{
		return playerPaddle->getPaddleXCor();
	}
	int getPaddleYCor()
	{
		return playerPaddle->getPaddleYCor();
	}
	int getPaddleLength()
	{
		return playerPaddle->getPaddleLength();
	}
	int getPaddleHeight()
	{
		return playerPaddle->getPaddleHeight();
	}
	Paddle *getPaddle() const
	{
		return playerPaddle;
	}
	int getPlayerLives()
	{
		return playerLives->getCurrentLives();
	}
	void setPlayerLives(int x)
	{
		playerLives->setLives(x);
	}
	int getPlayerScore()
	{
		return playerScore->getCurrentScore();
	}
	void setPlayerScore(int x)
	{
		playerScore->setCurrentScore(x);
	}
	float *getPaddleColor()
	{
		return playerPaddle->getPaddleColor();
	}
	void setPaddleColor(float *x)
	{
		playerPaddle->setPaddleColor(x);
	}
	void initalizePaddle1()
	{
		playerPaddle->setPaddleYCor(20);
		playerPaddle->setPaddleXCor(240);
		playerPaddle->setPaddleLength(80);
		playerPaddle->setPaddleHeight(20);
		playerPaddle->setPaddleXVelocity(0);
	}
	void initalizePaddle2()
	{
		playerPaddle->setPaddleYCor(760);
		playerPaddle->setPaddleXCor(280);
		playerPaddle->setPaddleLength(80);
		playerPaddle->setPaddleHeight(20);
		playerPaddle->setPaddleXVelocity(0);
	}
	~Player()
	{
		delete playerLives;
		delete playerPaddle;
		delete playerScore;
	}
};
// ball class is related to level class by AGGREGATION
class Ball
{
private:
	int xVelocity;
	int yVelocity;
	int radius;
	int xCor;
	int yCor;
	float *color = colors[WHITE];

public:
	int speed;
	Ball(int xCor = 320, int yCor = 70, int radius = 20, int xVelocity = 0, int yVelocity = 0)
	{
		this->xCor = xCor;
		this->yCor = yCor;
		this->radius = radius;
		this->xVelocity = xVelocity;
		this->yVelocity = yVelocity;
	}
	//////////////////////////getters///////////////////////////////
	void initialize()
	{
		this->xCor = 320;
		this->yCor = 70;
		this->radius = 20;
		this->color = colors[WHITE];
		this->xVelocity = 0;
		this->yVelocity = 0;
	}
	int getBallYVelocity()
	{
		return this->yVelocity;
	}
	float *getBallColor()
	{
		return this->color;
	}
	int getBallXVelocity()
	{
		return this->xVelocity;
	}
	int getBallRadius()
	{
		return this->radius;
	}
	int getBallXCor()
	{
		return this->xCor;
	}
	int getBallYCor()
	{
		return this->yCor;
	}
	////////////////////////////setters/////////////////////////////
	void setBallRadius(int radius)
	{
		this->radius = radius;
	}
	void setBallXVelocity(int xVelocity)
	{
		this->xVelocity = xVelocity;
	}
	void setBallYVelocity(int yVelocity)
	{
		this->yVelocity = yVelocity;
	}
	void setBallColor(float *color)
	{
		this->color = color;
	}
	void setBallXCor(int xCor)
	{
		this->xCor = xCor;
	}
	void setBallYCor(int yCor)
	{
		this->yCor = yCor;
	}
	///////////////////////////other functions///////////////////////
	void ballMovement()
	{
		xCor += xVelocity;
		yCor += yVelocity;
	}
	void drawBall()
	{
		DrawCircle(xCor, yCor, radius, color);
	}
	~Ball()
	{
	}
	bool ballFellDown()
	{
		if (yCor <= 0)
		{
			initialize();
			return true;
		}
		return false;
	}
	void checkWallCollision()
	{
		if (xCor <= 20 || xCor >= 600)
		{
			// change ball direction
			xVelocity = -xVelocity;
		}
		if (yCor >= 780)
		{
			yVelocity = -yVelocity;
		}
	}

	//         if (distance <= max_distance) {
	//             // Determine direction of ball based on where it hits the paddle
	//             int direction = (getBallXCor() < paddle.getPaddleXCor()) ? -1 : 1;

	//             // Adjust ball's velocity based on where it hits the paddle
	//             setBallXVelocity(5 * direction); // Adjust this value as needed

	//             // Invert ball's vertical velocity to make it bounce
	//             setBallYVelocity(-getBallYVelocity());

	void bounce() {}

	friend class Powerup;
};
// powerup is base class, it INHERITS 5 different powerup child classes
class Powerup
{
protected:
	int x, y;

public:
	Powerup() {}
	virtual void applyPowerup(Paddle *paddle, Ball *ball) {}
	void setXCor(int x) { this->x = x; }
	void setYCor(int y) { this->y = y; }
	virtual void setX2Cor(int x) {}
	virtual void setY2Cor(int y) {}
	virtual void setX3Cor(int x) {}
	virtual void setY3Cor(int y) {}
	int getXCor() { return x; }
	int getYCor() { return y; }
	void MovePowerupDown()
	{
		y = y - 1;
	}
	void MovePowerupUp()
	{
		y = y + 1;
	}
	virtual ~Powerup() {}
};
class PowerupGreen : public Powerup
{
	// triangle
private:
	int x2, x3, y2, y3;

public:
	PowerupGreen(int x = 0, int y = 0)
	{
		//
		this->x = x + 20;
		this->x2 = x + 40;
		this->x3 = x + 60;
		this->y = y;
		this->y2 = y + 40;
		this->y3 = y;
	}
	void setX2Cor(int x) { this->x2 = x; }
	void setY2Cor(int y) { this->y2 = y; }
	void setX3Cor(int x) { this->x3 = x; }
	void setY3Cor(int y) { this->y3 = y; }
	void MovePowerupDown()
	{
		this->y -= 1;
		this->y2 -= 1;
		this->y3 -= 1;
	}
	void drawPowerup()
	{
		DrawTriangle(x, y, x2, y2, x3, y3, colors[GREEN]);
	}
	void applyPowerup(Paddle *paddle, Ball *ball)
	{
		if (paddle->getPaddleLength() <= 160)
			paddle->doubleSize();
	} //////doubles size of paddle
	void undoPowerup(Paddle *paddle, Ball *ball) { paddle->halfSize(); }
	~PowerupGreen() {}
};
class PowerupPink : public Powerup
{
	// square
public:
	PowerupPink(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
	void drawPowerup() { DrawSquare(x, y, 20, colors[HOT_PINK]); }
	void applyPowerup(Paddle *paddle, Ball *ball)
	{
		if (paddle->getPaddleLength() > 40)
			paddle->halfSize();
	} ///////halves size of paddle
	void undoPowerup(Paddle *paddle, Ball *ball) { paddle->doubleSize(); }
	~PowerupPink() {}
};
class PowerupBlue : public Powerup
{
	// circle
	int radius;

public:
	PowerupBlue(int x = 0, int y = 0, int radius = 10)
	{
		this->x = x;
		this->y = y;
		this->radius = radius;
	}
	void drawPowerup() { DrawCircle(x, y, radius, colors[BLUE]); }
	void applyPowerup(Paddle *paddle, Ball *ball)
	{
		int xVel = ball->getBallXVelocity();
		int yVel = ball->getBallYVelocity();
		if (xVel > 3 || yVel > 3)
		{
			ball->setBallXVelocity(xVel / 2);
			ball->setBallYVelocity(yVel / 2);
		}
	} ///////halves speed of ball
	void undoPowerup(Paddle *paddle, Ball *ball)
	{
		int xVel = ball->getBallXVelocity();
		int yVel = ball->getBallYVelocity();
		ball->setBallXVelocity(xVel * 2);
		ball->setBallYVelocity(yVel * 2);
	} ///////doubles speed of ball
	~PowerupBlue() {}
};
class PowerupRed : public Powerup
{
	// rectangle
private:
	int length, height;

public:
	PowerupRed(int x = 0, int y = 0, int length = 40, int height = 20)
	{
		this->x = x;
		this->length = length;
		this->y = y;
		this->height = height;
	}
	void drawPowerup()
	{
		DrawRectangle(x, y, length, height, colors[RED]);
	}
	void applyPowerup(Paddle *paddle, Ball *ball)
	{
		int xVel = ball->getBallXVelocity();
		int yVel = ball->getBallYVelocity();
		if (xVel < 12 && yVel < 12)
		{
			ball->setBallXVelocity(xVel * 2);
			ball->setBallYVelocity(yVel * 2);
		}
	} ///////doubles speed of ball
	void undoPowerup(Paddle *paddle, Ball *ball)
	{
		int xVel = ball->getBallXVelocity();
		int yVel = ball->getBallYVelocity();
		ball->setBallXVelocity(xVel / 2);
		ball->setBallYVelocity(yVel / 2);
	} ///////halves speed of ball
	~PowerupRed() {}
};
class PowerupYellow : public Powerup
{
	// square
	Ball ball;
	Ball ball2;

public:
	PowerupYellow(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
	void drawPowerup() { DrawSquare(x, y, 20, colors[ORANGE]); }
	void applyPowerup(Paddle *paddle, Ball *ball)
	{

	} // add two more balls in diff directions from same coordinates
	void undoPowerup(Paddle *paddle, Ball *ball)
	{
	}
	~PowerupYellow() {}
};
// Brick is base class, it INHERITS 5 different Brick child classes
class Brick
{
protected:
	int length;
	int height;
	int xCor;
	int yCor;
	float *color;
	int startPowerupTime;
	bool powerupIsApplied;

public:
	Brick(int xCor = 0, int yCor = 0)
	{
		this->length = 80;
		this->height = 40;
		this->xCor = xCor;
		this->yCor = yCor;
	}
	void setXCor(int x) { xCor = x; }
	void setYCor(int y) { yCor = y; }
	void setLength(int l) { length = l; }
	void setHeight(int h) { height = h; }
	int getXCor() { return xCor; }
	int getYCor() { return yCor; }
	void setStartPowerupTime(int time) { startPowerupTime = time; }
	int getStartPowerupTime() { return startPowerupTime; }
	void setPowerupIsApplied(bool a) { powerupIsApplied = a; }
	bool getPowerupIsApplied() { return powerupIsApplied; }
	virtual int getPowerupXCor() {}
	virtual int getPowerupYCor() {}
	void setColor(float *x) { color = x; }
	float *getColor() { return color; }
	virtual void DrawBrick() {}
	virtual void implementPowerup()
	{
		cout << "in virtual void implement powerup\n";
	}
	virtual void applyPowerup(Paddle *paddle, Ball *ball)
	{
		cout << "in virtual void apply powerup\n";
	}
	virtual void drawPowerup()
	{
		cout << "in virtual draw power up \n";
	}
	virtual void undoPowerup(Paddle *paddle, Ball *ball)
	{
		cout << "in virtual undo power up\n";
	}
	virtual void movePowerupDown()
	{
		cout << "in virtual move power up down \n";
	}
	virtual int decreaseCollisions()
	{
		cout << "This shouldnt go here\n";
		return 9;
	}
	// pwerup things
	//  void powerupDownMovement(int i)
	//  {
	//  	powerup.MovePowerupDown();
	//  }
	//  void powerupUpMovement(int i)
	//  {
	//  	powerup.MovePowerupUp();
	//  }
	//  void drawPowerUp(){}
	virtual ~Brick() {}
};
class PinkBrick : public Brick
{
	int numOfCollisionsToBreak = 2;
	PowerupPink powerup;

public:
	PinkBrick()
	{
		color = colors[HOT_PINK];
	}
	int getCollisions()
	{
		return numOfCollisionsToBreak;
	}

	int decreaseCollisions()
	{
		numOfCollisionsToBreak--;
		return numOfCollisionsToBreak;
	}
	void applyPowerup(Paddle *paddle, Ball *ball)
	{
		powerup.applyPowerup(paddle, ball);
	}
	void undoPowerup(Paddle *paddle, Ball *ball)
	{
		powerup.undoPowerup(paddle, ball);
		powerupIsApplied = false;
	}
	void implementPowerup()
	{
		powerup.setXCor(xCor + 30);
		powerup.setYCor(yCor);
		powerup.drawPowerup();
	}
	void movePowerupDown()
	{
		powerup.MovePowerupDown();
	}
	void drawPowerup()
	{
		powerup.drawPowerup();
	}
	int getPowerupXCor() { return powerup.getXCor(); }
	int getPowerupYCor() { return powerup.getYCor(); }
	void DrawBrick() { DrawRectangle(xCor, yCor, length, height, color); }
	~PinkBrick() {}
};
class YellowBrick : public Brick
{
private:
	int numOfCollisionsToBreak = 2;
	PowerupYellow powerup;

public:
	YellowBrick()
	{
		color = colors[ORANGE];
	}
	int decreaseCollisions()
	{
		numOfCollisionsToBreak--;
		return numOfCollisionsToBreak;
	}
	void applyPowerup(Paddle *paddle, Ball *ball)
	{
		powerup.applyPowerup(paddle, ball);
	}
	void undoPowerup(Paddle *paddle, Ball *ball)
	{
		powerup.undoPowerup(paddle, ball);
		powerupIsApplied = false;
	}
	void implementPowerup()
	{
		powerup.setXCor(xCor + 30);
		powerup.setYCor(yCor);
		powerup.drawPowerup();
	}
	void movePowerupDown()
	{
		powerup.MovePowerupDown();
	}
	void drawPowerup()
	{
		powerup.drawPowerup();
	}
	int getPowerupXCor() { return powerup.getXCor(); }
	int getPowerupYCor() { return powerup.getYCor(); }
	void DrawBrick() { DrawRectangle(xCor, yCor, length, height, color); }
	~YellowBrick() {}
};
class RedBrick : public Brick
{
private:
	int numOfCollisionsToBreak = 3;
	PowerupRed powerup;

public:
	RedBrick()
	{
		color = colors[RED];
	}
	int decreaseCollisions()
	{
		numOfCollisionsToBreak--;
		return numOfCollisionsToBreak;
	}
	void applyPowerup(Paddle *paddle, Ball *ball)
	{
		powerup.applyPowerup(paddle, ball);
	}
	void undoPowerup(Paddle *paddle, Ball *ball)
	{
		powerup.undoPowerup(paddle, ball);
		powerupIsApplied = false;
	}
	void implementPowerup()
	{
		powerup.setXCor(xCor + 20);
		powerup.setYCor(yCor);
		powerup.drawPowerup();
	}
	void movePowerupDown()
	{
		powerup.MovePowerupDown();
	}
	void drawPowerup()
	{
		powerup.drawPowerup();
	}
	int getPowerupXCor() { return powerup.getXCor(); }
	int getPowerupYCor() { return powerup.getYCor(); }
	void DrawBrick() { DrawRectangle(xCor, yCor, length, height, color); }
	~RedBrick() {}
};
class BlueBrick : public Brick
{
private:
	int numOfCollisionsToBreak = 3;
	PowerupBlue powerup;

public:
	BlueBrick()
	{
		color = colors[BLUE];
	}
	int decreaseCollisions()
	{
		numOfCollisionsToBreak--;
		return numOfCollisionsToBreak;
	}
	void applyPowerup(Paddle *paddle, Ball *ball)
	{
		powerup.applyPowerup(paddle, ball);
	}
	void undoPowerup(Paddle *paddle, Ball *ball)
	{
		powerup.undoPowerup(paddle, ball);
		powerupIsApplied = false;
	}
	void implementPowerup()
	{
		powerup.setXCor(xCor + 40);
		powerup.setYCor(yCor + 20);
		powerup.drawPowerup();
	}
	void movePowerupDown()
	{
		powerup.MovePowerupDown();
	}
	void drawPowerup()
	{
		powerup.drawPowerup();
	}
	int getPowerupXCor() { return powerup.getXCor(); }
	int getPowerupYCor() { return powerup.getYCor(); }
	void DrawBrick() { DrawRectangle(xCor, yCor, length, height, color); }
	~BlueBrick() {}
};
class GreenBrick : public Brick
{
private:
	int numOfCollisionsToBreak = 1;
	PowerupGreen powerup;

public:
	GreenBrick()
	{
		color = colors[GREEN];
	}
	int decreaseCollisions()
	{
		numOfCollisionsToBreak--;
		return numOfCollisionsToBreak;
	}
	void applyPowerup(Paddle *paddle, Ball *ball)
	{
		powerup.applyPowerup(paddle, ball);
	}
	void undoPowerup(Paddle *paddle, Ball *ball)
	{
		powerup.undoPowerup(paddle, ball);
		powerupIsApplied = false;
	}
	void implementPowerup()
	{
		powerup.setXCor(xCor + 20);
		powerup.setYCor(yCor);
		powerup.setX2Cor(xCor + 40);
		powerup.setY2Cor(yCor + 40);
		powerup.setX3Cor(xCor + 60);
		powerup.setY3Cor(yCor);
		powerup.drawPowerup();
	}
	void movePowerupDown()
	{
		powerup.MovePowerupDown();
	}
	void drawPowerup()
	{
		powerup.drawPowerup();
	}
	int getPowerupXCor() { return powerup.getXCor(); }
	int getPowerupYCor() { return powerup.getYCor(); }
	void DrawBrick() { DrawRectangle(xCor, yCor, length, height, color); }
	~GreenBrick() {}
};
// cell struct contains booleans and coordinates info
struct cell
{
public:
	int cellNum, brickIndex = -1;
	int xCor, yCor;
	bool hasBrick;
	bool hasPowerup;
	bool hasPaddle;
	bool inGame;
	bool draw;
	cell() {}
	cell(int x, int y)
	{
		xCor = x;
		yCor = y;
		hasBrick = false;
		hasPowerup = false;
		hasPaddle = false;
		draw = true;
		if (y >= 600)
		{
			inGame = false;
		}
		else
			inGame = true;
	}
	cell(int x, int y, bool brick, bool powerup, bool paddle)
	{
		brickIndex = -1;
		xCor = x;
		yCor = y;
		hasBrick = brick;
		hasPowerup = powerup;
		hasPaddle = paddle;
		inGame = true;
		draw = true;
	}
	~cell() {}
};
// grid class has a 2d cell struct array as a member
class Grid
{
public:
	int xCor, yCor;
	cell grid[20][20];
	Grid()
	{
		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				// Each cell is 40 pixels so I multiplied the coordinates with 40
				int x = i * 40;
				int y = j * 40;
				grid[i][j] = cell(x, y);
			}
		}
	}
	void drawGrid()
	{
		// draw horizontal lines
		for (int y = 0; y <= 800; y += 40) // Draw lines at intervals of 40 pixels
		{
			DrawLine(0, y, 800, y, 1, colors[MISTY_ROSE]); // Draw horizontal line
		}
		// Draw vertical lines
		for (int x = 0; x <= 800; x += 40) // Draw lines at intervals of 40 pixels
		{
			DrawLine(x, 0, x, 800, 1, colors[MISTY_ROSE]); // Draw vertical line
		}
	}
	void returnGrid(int x, int y, int &xCor, int &yCor)
	{
		xCor = x / 40;
		yCor = y / 40;
		if (xCor < 0)
		{
			xCor = 0;
		}
		else if (xCor >= 20)
		{
			xCor = 19;
		}
		if (yCor < 0)
		{
			yCor = 0;
		}
		else if (yCor >= 20)
		{
			yCor = 19; // bcoz 0 to 19
		}
	}
	bool checkPowerupPaddleCollision(Powerup &powerup)
	{
		int i, j;
		returnGrid(powerup.getXCor(), powerup.getYCor(), i, j);
		return grid[i][j].hasPaddle;
	}
	int clearPaddlePosition()
	{ // gives length of paddle too, aka how many cells long it is
		int count = 0;
		for (int i = 0; i < 15; i++)
		{
			if (grid[19][i].hasPaddle){
				grid[19][i].hasPaddle = false;
			    count++;
			}
		}
		return count;
	}
	void updatePaddlePosition(int x, int y)
	{
		int length = clearPaddlePosition();
		int i, j;
		returnGrid(x, y, i, j);
		for (int k = 0; k < length; k++)
		{
			grid[i][j + k].hasPaddle = true;
		}
	}
	void updatePowerupPosition(int x, int y)
	{
		grid[x][y].hasPowerup = false;
		int x1 = x + 1;
		grid[x1][y].hasPowerup = true;
	}
	~Grid() {}
};
// Highscore does file handling things
class HighScore
{
public:
	void savePlayerData(int score)
	{
		ofstream file("highscore.txt", ios::app); // Open file in append mode
		if (file.is_open())
		{
			file << score; // Write player data to file
			cout << "Score was just saved in file!\n";
			file.close(); // Close the file
		}
		else
			cout << "\nwasnt able to open file for writing score\n";
	}
	void displayPlayerData()
	{
		int highscore = 0, index = 0;
		int scoreArray[50];
		ifstream file("highscore.txt");
		if (file.is_open())
		{
			// Read all scores into the array
			int score;
			while (file >> score)
			{
				scoreArray[index++] = score;
				if (score > highscore)
				{
					highscore = score;
				}
			}
			file.close();
			string h = "Highscore: " + to_string(highscore);
			DrawString(645, 400, h, colors[MISTY_ROSE]);
		}
		else
			cout << "\nCant read file for writing highscore\n";
	}
};
// levels is a base class with 3 child classes. POLYMORPHISM used by making virtual functions
// ENCAPSULATION of all classes done in level class
class Level
{
protected:
	bool drawPowerup;
	bool ballIsMoving;
	int levelCount;
	int numOfBricks;
	Brick *bricks[300];
	Player *player1;
	Ball ball;
	Grid grid;
	HighScore highscore;
	string playerName;
	bool scoreSaved = false;
	bool gamePlaying = true;
	bool won = false;

public:
	bool a = true;
	Level(int level = 1, int numOfBricks = 45, string name = "Player 1")
	{
		drawPowerup = false;
		ballIsMoving = false;
		this->levelCount = level;
		this->numOfBricks = numOfBricks;
		this->playerName = name;
		this->player1 = new Player(playerName);
		initializeBricks();
	}
	void drawGameOverScreen()
	{
		DrawSquare(800, 800, 400, colors[ORANGE]);
		DrawString(350, 400, "GAME OVER :(", colors[RED]);
	}
	void drawWinScreen()
	{
		DrawSquare(800, 800, 400, colors[ORANGE]);
		DrawString(350, 400, "YOU WIN :)", colors[RED]);
	}
	int getLevel() { return this->levelCount; }
	void setLevel(int level) { this->levelCount = level; }
	int getWinState() { return this->won; }
	void setWinState(int win) { this->won = win; }
	void increaseLevel()
	{
		this->levelCount += 1;
	}
	void drawLevelIcon()
	{
		string level = "Level: " + to_string(levelCount);
		DrawString(660, 760, level, colors[MISTY_ROSE]);
	}
	int getPlayer1Score()
	{
		return player1->getPlayerScore();
	}
	void setPlayer1Score(int score)
	{
		player1->setPlayerScore(score);
	}
	virtual void drawLevel()
	{
		if (gamePlaying)
		{
			DrawLine(640, 0, 640, 800, 20, colors[MISTY_ROSE]); // wall to seperate game and score screens
			drawBricks();
			drawLevelIcon();
			player1->drawPlayerName();
			player1->drawPlayerVariables();
			highscore.displayPlayerData();
			char name[16] = "Aleena 23i2514";
			DrawString(645, 360, name, colors[ORANGE]);
			ball.drawBall();
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					if (grid.grid[j][i].hasPowerup)
					{
						int index = grid.grid[j][i].brickIndex;
						bricks[index]->drawPowerup();
					}
				}
			}
		}
		else
			drawGameOverScreen();
	}
	void ballMovement()
	{
		ball.ballMovement();
	}
	void player1PaddleMovement(int x)
	{
		player1->PlayerPaddleMovement(x);
		if (!ballIsMoving)
		{
			ball.setBallXCor(x + 40);
		}
	}
	void initializeBricks()
	{
		srand(time(nullptr));
		int i = 0;
		while (i < numOfBricks)
		{
			int number = GetRandInRange(0, 5);
			switch (number)
			{
			case 0:
				bricks[i] = new PinkBrick();
				break;
			case 1:
				bricks[i] = new YellowBrick();
				break;
			case 2:
				bricks[i] = new GreenBrick();
				break;
			case 3:
				bricks[i] = new BlueBrick();
				break;
			case 4:
				bricks[i] = new RedBrick();
				break;
			}
			i++;
		}
	}
	void checkIfBallFalls()
	{
		if (ball.getBallYCor() <= 0)
		{
			int currentLives = player1->getPlayerLives();
			if (currentLives > 0)
				player1->setPlayerLives(currentLives - 1);
			ball.initialize();
			ballIsMoving = false;
			player1->initalizePaddle1();
		}
	}
	void setBrickCell(int a, bool exists = true)
	{
		int x = bricks[a]->getXCor();
		int x2 = x - 1 + 80; // dont need to get length as brick length is always 80
		int y = bricks[a]->getYCor();
		int i, j;
		grid.returnGrid(x, y, i, j);
		grid.grid[i][j].hasBrick = exists;
		grid.grid[i][j].brickIndex = a;
		grid.returnGrid(x2, y, i, j);
		grid.grid[i][j].hasBrick = exists;
		grid.grid[i][j].brickIndex = a; // both cells are set as having that brick Index
	}
	void setBrickDraw(int a, bool exists = false)
	{
		int x = bricks[a]->getXCor();
		int x2 = x - 1 + 80; // dont need to get length as brick length is always 80
		int y = bricks[a]->getYCor();
		int i, j;
		grid.returnGrid(x, y, i, j);
		grid.grid[i][j].draw = exists;
		grid.grid[i][j].brickIndex = a;
		grid.returnGrid(x2, y, i, j);
		grid.grid[i][j].draw = exists;
		grid.grid[i][j].brickIndex = a; // both cells are set as having that brick Index
	}
	void setPaddle1Cell(bool exists = true)
	{
		for (int l = 0; l < 16; l++)
		{
			grid.grid[l][0].hasPaddle = false;
		}
		int x = player1->getPaddleXCor();
		int x2 = x - 1 + player1->getPaddleLength();
		int y = player1->getPaddleYCor();
		int i, j;
		grid.returnGrid(x, y, i, j);
		grid.returnGrid(x2, y, i, j);
		for (int k = x + 1; k < x2; k++)
		{
			grid.returnGrid(k, y, i, j);
			grid.grid[i][j].hasPaddle = exists; // x=i,y=j
		}
	}
	virtual void setPaddle2Cell(bool exists = true) {}
	int ballAndBrickCollision(int &a, int &b)
	{
		int x = ball.getBallXCor();
		int y = ball.getBallYCor();
		int i, j;
		grid.returnGrid(x, y, i, j);
		a = i;
		b = j;
		if (grid.grid[i][j].hasBrick == true)
		{
			if (grid.grid[i][j].draw)
			{
				return grid.grid[i][j].brickIndex;
			}
		}

		return -1; // brick not there so index is -1
	}
	bool powerupAndPaddleCollision(int index)
	{
		// get x and y cor of powerup
		int x = bricks[index]->getPowerupXCor();
		int y = bricks[index]->getPowerupYCor();
		int i, j;
		grid.returnGrid(x, y, i, j);
		return grid.grid[i][j].hasPaddle;
	}
	bool ballAndPaddleCollision()
	{
		int x = ball.getBallXCor();
		int y = ball.getBallYCor();
		// get ballbottom
		int bottom = y - ball.getBallRadius();
		int i, j;
		grid.returnGrid(x, bottom, i, j);
		return grid.grid[i][j].hasPaddle;
	}
	// bool powerupAndPaddleCollision()
	// {
	// 	int x = powerup->getXCor();
	// 	int y = powerup->getYCor();
	// 	int i, j;
	// 	grid.returnGrid(x, y, i, j);
	// 	return grid.grid[i][j].hasPaddle;
	// }
	virtual void logic()
	{
		if (player1->getPlayerLives() > 0)
		{
			// ball movement
			ballMovement();
			ball.checkWallCollision();
			checkIfBallFalls();
			// brick collision and following logic ---> powerup implementation
			int xCell, yCell;
			int index = ballAndBrickCollision(xCell, yCell);
			if (index != -1)
			{
				bounceBallfromBrick(xCell * 40);
				ball.setBallColor(bricks[index]->getColor());
				// cout << "\nBRICK AND BALL COLLIDE, xCell is " << xCell << " and yCell is " << yCell << "and index is " << index;
				//  i need the brick's index so i can decrease its collisions count till it breaks
				int numOfCollisions = bricks[index]->decreaseCollisions();
				cout << "\nnum of collisons are " << numOfCollisions;
				if (numOfCollisions <= 0) // the num of collisions are now zero or less(hopefully not)
				{
					player1->setPlayerScore(player1->getPlayerScore() + 1);
					setBrickCell(index, false);
					setBrickDraw(index, false);
					// make a powerup in the same cell
					grid.grid[xCell][yCell].hasPowerup = true;
					bricks[index]->implementPowerup();
					int x = bricks[index]->getXCor();
					int y = bricks[index]->getYCor();
					int i, j;
					grid.returnGrid(x, y, i, j);
					grid.grid[i][j].hasPowerup = true;
				}
			}
			if (ballAndPaddleCollision())
			{
				bounceBall();
				player1->setPaddleColor(ball.getBallColor());
			}
			// make powerups move down
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					// draw powerup if it exists
					if (grid.grid[j][i].hasPowerup)
					{
						int index = grid.grid[j][i].brickIndex;
						bricks[index]->movePowerupDown();
						if (powerupAndPaddleCollision(index)) // check if the powerup has moved to where the paddle is
						{
							grid.grid[j][i].hasPowerup = false; // powerup dies
							// bricks[index]->implementPowerup();
							bricks[index]->applyPowerup(player1->getPaddle(), &ball); // powerup acquired by player
						}
					}
				}
			}
			// Check for powerup undo
			for (int i = 0; i < 10; ++i)
			{
				if (bricks[i]->getPowerupIsApplied())
				{ // Check if a brick has an active powerup
					if (glutGet(GLUT_ELAPSED_TIME) - bricks[i]->getStartPowerupTime() >= 500)
					{ // 500 millisecs is 5 secs
						bricks[i]->undoPowerup(player1->getPaddle(), &ball);
					}
				}
			}
		}
		else
		{
			gamePlaying = false;
			if (!scoreSaved)
			{
				int score = player1->getPlayerScore();
				highscore.savePlayerData(score);
				scoreSaved = true;
			}
		}
		glutPostRedisplay();
	}
	void startBallMovement(int v)
	{
		ball.setBallYVelocity(v);
		ball.ballMovement();
		ballIsMoving = true;
	}
	void bounceBall()
	{
		if (getPositionOfImpactPaddle1() < 0)
		{
			if (ball.getBallXVelocity() == 0)
				ball.setBallXVelocity(-5);
			else
				ball.setBallXVelocity(-abs(ball.getBallXVelocity())); // Hit left go left
		}
		else
		{
			if (ball.getBallXVelocity() == 0)
				ball.setBallXVelocity(5);
			else
				ball.setBallXVelocity(abs(ball.getBallXVelocity())); // Hit right go right
		}

		// Reverse the ball's y-velocity
		ball.setBallYVelocity(-ball.getBallYVelocity());
	}
	void bounceBallfromBrick(int xCor)
	{
		if (getPositionOfImpactBrick(xCor) < 0)
		{
			if (ball.getBallXVelocity() == 0)
				ball.setBallXVelocity(-5);
			else
				ball.setBallXVelocity(-abs(ball.getBallXVelocity())); // Hit left go left
		}
		else
		{
			if (ball.getBallXVelocity() == 0)
				ball.setBallXVelocity(5);
			else
				ball.setBallXVelocity(abs(ball.getBallXVelocity())); // Hit right go right
		}

		// Reverse the ball's y-velocity
		ball.setBallYVelocity(-ball.getBallYVelocity());
	}
	float getPositionOfImpactBrick(int xCor)
	{
		return ball.getBallXCor() - (2 * xCor + 80) / 2;
	}
	float getPositionOfImpactPaddle1()
	{
		return ball.getBallXCor() - (2 * (player1->getPaddleXCor()) + player1->getPaddleLength()) / 2;
	}
	bool winLevel()
	{
		// if all bricks are set to dont draw game won
		int count = 0;
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				count += grid.grid[x][y].draw;
			}
		}
		if (count == numOfBricks)
		{
			return true;
		}
		return false;
	}
	virtual void player2RightPaddleMovement() {}
	virtual void player2LeftPaddleMovement() {}
	virtual void drawBricks()
	{
		cout << "in base class virtual draw function\n";
	}
	virtual ~Level()
	{
		delete player1;
	}
};
class Level1 : public Level
{
	// draw brick pattern
public:
	Level1(string playerName, int level = 1, int numOfBricks = 35) {}

	void drawBricks()
	{
		int index = -1;
		for (int i = 0; i < 5; i++) // y
		{
			for (int j = 0; j < 8; j++) // x
			{
				index++;
				int xCor = j * 80;
				int yCor = 720 - (i + 1) * 40; // Adjust yCor calculation
				// cout<<"\nIndex: "<<index<<"xCor , yCor: "<<xCor<<" , "<<yCor;
				// cout<<"\nCell is "<<xCor/40<<" , "<<yCor/40;
				if (grid.grid[xCor / 40][yCor / 40].draw)
				{ // has brick is destroyed and isnt to be drawn
					bricks[index]->setXCor(xCor);
					bricks[index]->setYCor(yCor);
					bricks[index]->DrawBrick();
					setBrickCell(index, true); // when drawing bricks I set cells to brick exists
				}
			}
		}
	}
	~Level1() {}
};
class Level2 : public Level
{
public:
	Level2(string playerName, int level = 2, int numOfBricks = 63)
	{
		levelCount = level;
	}
	// draw brick pattern
	void goAhead(int &xCor, int n)
	{
		if (n > 0)
		{
			xCor += 80;
			goAhead(xCor, n - 1);
		}
	}

	void printLine(int &xCor, int &yCor, int &index, int n, int s, int i = 0)
	{
		if (i < n)
		{
			index++;
			yCor -= 40;
			xCor = 80;
			goAhead(xCor, s);
			// draw brick
			if (grid.grid[xCor / 40][yCor / 40].draw)
			{
				bricks[index]->setXCor(xCor);
				bricks[index]->setYCor(yCor);
				bricks[index]->DrawBrick();
				setBrickCell(index, true); // when drawing bricks I set cells to brick exists
			}
			printLine(xCor, yCor, index, 2, s, i + 1);
		}
	}

	void drawBricksActually(int xCor = 80, int yCor = 720, int index = -1, int n = 5, int i = 0)
	{
		if (i <= n / 2)
		{

			printLine(xCor, yCor, index, n, i);
			drawBricksActually(xCor + 80, yCor, index, n, i + 1);
		}
		return;
	}
	void drawLowerHalf(int xCor = 160, int yCor = 440, int index = 7)
	{
		for (int i = 0; i < 2; i++)
		{
			if (grid.grid[xCor / 40][yCor / 40].draw)
			{
				bricks[index]->setXCor(xCor);
				bricks[index]->setYCor(yCor);
				bricks[index]->DrawBrick();
				setBrickCell(index, true); // when drawing bricks I set cells to brick exists
				index++;
			}
			yCor -= 40;
		}
		xCor -= 80;
		for (int i = 0; i < 2; i++)
		{
			if (grid.grid[xCor / 40][yCor / 40].draw)
			{
				bricks[index]->setXCor(xCor);
				bricks[index]->setYCor(yCor);
				bricks[index]->DrawBrick();
				setBrickCell(index, true); // when drawing bricks I set cells to brick exists
				index++;
			}
			yCor -= 40;
		}
	}

	void drawBricks()
	{
		drawBricksActually(80, 720, 0, 5, 0);
		drawLowerHalf();
	}

	~Level2() {}
};
class Level3 : public Level
{
private:
	Player *player2;

public:
	Level3(string name, string player2Name, int level = 3, int numOfBricks = 45, int x = 280, int y = 760)
	{
		playerName = name;
		levelCount = level;
		player2 = new Player(player2Name, x, y);
	}
	/// player movement
	void player2LeftPaddleMovement()
	{
		int a = player2->getPaddleXCor();
		if (a - 10 >= 0)
		{
			player2->PlayerPaddleMovement(a - 10);
		}
	}
	void player2RightPaddleMovement()
	{
		int a = player2->getPaddleXCor();
		if (a + 10 <= 560)
		{
			player2->PlayerPaddleMovement(a + 10);
		}
	}
	void bounceBall2()
	{
		if (getPositionOfImpactPaddle2() < 0)
		{
			if (ball.getBallXVelocity() == 0)
				ball.setBallXVelocity(-5);
			else
				ball.setBallXVelocity(-abs(ball.getBallXVelocity())); // Hit left go left
		}
		else
		{
			if (ball.getBallXVelocity() == 0)
				ball.setBallXVelocity(5);
			else
				ball.setBallXVelocity(abs(ball.getBallXVelocity())); // Hit right go right
		}
		// Reverse the ball's y-velocity
		ball.setBallYVelocity(-ball.getBallYVelocity());
	}
	float getPositionOfImpactPaddle2()
	{
		return ball.getBallXCor() - (2 * (player2->getPaddleXCor()) + player2->getPaddleLength()) / 2;
	}
	// void powerupUpMovement()
	// {
	// 	}

	void print(int starCount, int spaceCount, int &index, int &xCor, int &yCor)
	{
		if ((index >= 22) || (starCount <= 0 && spaceCount <= 0))
		{
			return;
		}
		else if (spaceCount > 0)
		{
			xCor += 80; // skip a brick here
			print(starCount, spaceCount - 1, index, xCor, yCor);
		}
		else
		{
			// make a brick here and increase index
			bricks[index]->setXCor(xCor);
			bricks[index]->setYCor(yCor);
			if (grid.grid[xCor / 40][yCor / 40].draw)
			{
				bricks[index]->DrawBrick();
				// cout << "\nINDEX " << index << " has XCOR " << xCor << " , YCOR " << yCor;
				setBrickCell(index, true); // when drawing bricks I set cells to brick exists
			}
			index++;
			xCor += 80;
			print(--starCount, spaceCount, index, xCor, yCor);
		}
	}

	void diamondShape(int num, int star, int space = 1, int count = 1, int index = -1, int xCor = 80, int yCor = 600)
	{
		if (count == num || index == 22)
		{
			return;
		}
		index++;
		print(star, 0, index, xCor, yCor);
		index--;
		xCor -= 80;
		print(0, space, index, xCor, yCor);
		index++;
		print(star, 0, index, xCor, yCor);
		yCor -= 40;
		xCor = 80; // next line
		// cout<<"\nthe index is "<<index<<" and the yCor is "<<yCor<<" the count is "<<count;
		if (count < ((num + 1) / 2))
		{
			index--;
			diamondShape(num, --star, space += 2, ++count, index, xCor, yCor);
		}
		else
		{
			index--;
			diamondShape(num, ++star, space -= 2, ++count, index, xCor, yCor);
		}
	}
	void drawBricks()
	{
		diamondShape(6, ((6 + 1) / 2));
	}
	void drawLevel()
	{
		if (gamePlaying)
		{
			DrawLine(640, 0, 640, 800, 20, colors[MISTY_ROSE]); // wall to seperate game and score screens
			drawBricks();
			// side screen
			drawLevelIcon();
			highscore.displayPlayerData();
			char name[16] = "Aleena 23i2514";
			DrawString(645, 360, name, colors[ORANGE]);
			// ball
			ball.drawBall();
			// draw player things
			player1->drawPlayerVariables();
			player1->drawPlayerName();
			player2->drawPlayerVariables();
			player2->drawPlayerName();
			// draw powerups
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					if (grid.grid[j][i].hasPowerup)
					{
						int index = grid.grid[j][i].brickIndex;
						bricks[index]->drawPowerup();
					}
				}
			}
		}
		else
			drawGameOverScreen();
		glutPostRedisplay();
	}
	void checkIfBallGoesUp()
	{
		if (ball.getBallYCor() >= 800)
		{
			int currentLives = player2->getPlayerLives();
			if (currentLives > 0)
				player2->setPlayerLives(currentLives - 1);
			ball.initialize();
			ballIsMoving = false;
			player1->initalizePaddle1();
			player2->initalizePaddle2();
		}
	}
	void setPaddle2Cell(bool exists = true)
	{
		for (int l = 0; l < 16; l++)
		{
			grid.grid[l][19].hasPaddle = false;
		}
		int x = player2->getPaddleXCor();
		int x2 = x - 1 + player2->getPaddleLength();
		int y = player2->getPaddleYCor();
		int i, j;
		grid.returnGrid(x, y, i, j);
		grid.grid[i][j].hasPaddle = exists;
		grid.returnGrid(x2, y, i, j);
		grid.grid[i][j].hasPaddle = exists;
		for (int k = x + 1; k < x2; k++)
		{
			grid.returnGrid(k, y, i, j);
			grid.grid[i][j].hasPaddle = exists; // x=i,y=j
		}
	}
	bool ballAndPaddle2Collision()
	{
		int x = ball.getBallXCor();
		int y = ball.getBallYCor();
		// get balltop
		int top = y + ball.getBallRadius();
		int i, j;
		grid.returnGrid(x, top, i, j);
		return grid.grid[i][j].hasPaddle;
	}
	void logic()
	{
		// ball movement
		if (player2->getPlayerLives() > 0 && player1->getPlayerLives() > 0)
		{
			ballMovement();
			if (ball.getBallXCor() <= 20 || ball.getBallXCor() >= 600)
			{
				ball.setBallXVelocity(-ball.getBallXVelocity());
			}
			// ball check paddle collisons
			if (ballAndPaddleCollision())
			{
				bounceBall();
				player1->setPaddleColor(ball.getBallColor());
			}
			if (ballAndPaddle2Collision())
			{
				bounceBall2();
				player2->setPaddleColor(ball.getBallColor());
			}
			checkIfBallFalls();
			checkIfBallGoesUp();
			// brick and powerups
			int xCell, yCell;
			int index = ballAndBrickCollision(xCell, yCell);
			if (index != -1)
			{
				bounceBallfromBrick(xCell * 40);
				ball.setBallColor(bricks[index]->getColor());
				cout << "\nBRICK AND BALL COLLIDE, xCell is " << xCell << " and yCell is " << yCell << "and index is " << index;
				// i need the brick's index so i can decrease its collisions count till it breaks
				int numOfCollisions = bricks[index]->decreaseCollisions();
				cout << "\nnum of collisons are " << numOfCollisions;
				if (numOfCollisions <= 0) // the num of collisions are now zero
				{
					player1->setPlayerScore(player1->getPlayerScore() + 1);
					setBrickCell(index, false);
					setBrickDraw(index, false);
					grid.grid[xCell][yCell].hasPowerup = true;
					bricks[index]->implementPowerup();
					cout << "Drew powerup\n"; // destroy the brick and spawn a powerup in the same cell
				}
			}
			// make powerups move down
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					if (grid.grid[j][i].hasPowerup)
					{
						int index = grid.grid[j][i].brickIndex;
						bricks[index]->movePowerupDown();
						if (powerupAndPaddleCollision(index)) // check if the powerup has moved down to where the paddle is
						{
							grid.grid[j][i].hasPowerup = false; // powerup dies
							// bricks[index]->implementPowerup();
							bricks[index]->applyPowerup(player1->getPaddle(), &ball); // players acquire powerup functionality
							bricks[index]->applyPowerup(player2->getPaddle(), &ball);
							bricks[index]->setPowerupIsApplied(true);
							bricks[index]->setStartPowerupTime(glutGet(GLUT_ELAPSED_TIME));
						}
						// check cell of powerup
						// check paddle collisions
					}
				}
			}
			// Check for powerup undo
			for (int i = 0; i < 10; ++i)
			{
				if (bricks[i]->getPowerupIsApplied())
				{ // Check if a brick has an active powerup
					if (glutGet(GLUT_ELAPSED_TIME) - bricks[i]->getStartPowerupTime() >= 500)
					{ // 500 millisecs is 5 secs
						bricks[i]->undoPowerup(player2->getPaddle(), &ball);
						bricks[i]->undoPowerup(player1->getPaddle(), &ball);
					}
				}
			}
		}
		else
		{
			gamePlaying = false;
			if (!scoreSaved)
			{
				int score1 = player1->getPlayerScore();
				highscore.savePlayerData(score1);
				int score = player2->getPlayerScore();
				highscore.savePlayerData(score);
				scoreSaved = true;
			}
		}
	}
	~Level3() {}
};
//////////////////////////////////////////
//  THE SOLE GLOBAL OBJECT DECLARATION  //
//////////////////////////////////////////
Level *level = new Level1("player2"); // a pointer to base class level so as to use polymorphism
									  // to access all 3 levels and their functionalities
void SetCanvasSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void GameDisplay()
{
	glClearColor(0, 0, 0.0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	// if (level->getWinState() == false)
	// {
	// 	switch (level->getLevel())
	// 	{
	// 	case 1:
	// 		level = new Level2("Player 1");
	// 	case 2:
	// 		level = new Level3("Player 1", "Player 2");
	// 	case 3:
	// 		level->setWinState(true);
	// 		level->drawWinScreen();
	// 	}
	//}
	level->drawLevel();
	level->logic();

	glutSwapBuffers();
	glutPostRedisplay();
}
void NonPrintableKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		level->player2LeftPaddleMovement();
		level->setPaddle2Cell();
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		level->player2RightPaddleMovement();
		level->setPaddle2Cell();
	}
	else if (key == GLUT_KEY_UP)
	{
	}

	else if (key == GLUT_KEY_DOWN)
	{
	}
	glutPostRedisplay();
}
void PrintableKeys(unsigned char key, int x, int y)
{
	if (key == 27 /* Escape key ASCII*/)
	{
		exit(1);
	}

	if (key == '1')
	{
		int score = level->getPlayer1Score();
		delete level;
		level = new Level1("player2");
		level->setPlayer1Score(score);
	}
	if (key == '2')
	{
		int score = level->getPlayer1Score();
		delete level;
		level = new Level2("player2");
		level->setPlayer1Score(score);
	}
	if (key == '3')
	{
		int score = level->getPlayer1Score();
		delete level;
		level = new Level3("player 1", "player2");
		level->setPlayer1Score(score);
	}
	glutPostRedisplay();
}
void Timer(int m)
{
	// level->logic();

	glutTimerFunc(1000.0, Timer, 0);
}
void MousePressedAndMoved(int x, int y)
{
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y)
{
	if (x >= 0 && x < 560)
	{
		level->player1PaddleMovement(x);
		level->setPaddle1Cell();
	}
	glutPostRedisplay();
}
void MouseClicked(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON)
	{
		level->startBallMovement(6);
		cout << "Left Button Pressed" << endl;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		cout << "Right Button Pressed" << endl;
	}
	glutPostRedisplay();
}
int main(int argc, char *argv[])
{

	int width = 800, height = 800;

	InitRandomizer();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(width, height);
	glutCreateWindow("aleena 23i2514 oop project");
	SetCanvasSize(width, height);
	glutDisplayFunc(GameDisplay);
	glutSpecialFunc(NonPrintableKeys);
	glutKeyboardFunc(PrintableKeys);
	glutTimerFunc(1000.0, Timer, 0);
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved);
	glutMotionFunc(MousePressedAndMoved);
	glutMainLoop();
	return 1;
}
#endif
