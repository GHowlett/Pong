#ifndef PROGRAM
#define PROGRAM

#include "Common.h"
#include "Input Component.h"
#include "Physics Component.h"
#include "Game Pieces.h"

class Ball;

class Program
{
public:

	Program();

	void Initialize();

	void Begin();

	friend class PhysicsComponent;
	friend class InputComponent;

private:
	//TODO:  AI component

	//Window stuff
	sf::RenderWindow Window;
	sf::View View;
	sf::Color BackroundColor;

	//Tools
	sf::Randomizer Randomizer;

	//Game Pieces
	Ball Ball;
	sf::Shape RightPaddle, LeftPaddle;

	//Physics
	PhysicsComponent PhysicsComponent; // How do you avoid statements like these?

	//Input
	InputComponent InputComponent;

	//Scoring
	unsigned int PlayerScore, OpponentScore;


	void InitializeWindow();

	void InitializeGamePieces();

	void Draw();
};

#endif