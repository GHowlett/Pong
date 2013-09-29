#ifndef GAME_PIECES
#define GAME_PIECES

#include "Common.h"

struct Ball
{
	sf::Shape Shape;
	float Radius;
	sf::Vector2f Velocity;
	float Elasticity;

	Ball()
	{
		Elasticity = 1.1;
		Radius = 10;
		Shape = sf::Shape::Circle(sf::Vector2f(0,0), Radius, sf::Color::Green);
		Velocity = sf::Vector2f(0,0);
	}

	void SetRandomVelocity(int Direction)
	{
		sf::Randomizer Randomizer;

		if( Direction == LEFT)
			Velocity.x = Randomizer.Random(-400, -250);
		else if( Direction == RIGHT)
			Velocity.x = Randomizer.Random(250,400);
		else
			Velocity.x = Randomizer.Random(-400, 400);

		Velocity.y = Randomizer.Random(-300,300);
	}
};

#endif