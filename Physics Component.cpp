#include "Common.h"
#include "Physics Component.h"
#include "Program.h"

PhysicsComponent::PhysicsComponent(Program& program): m_Program(program){}
	
void PhysicsComponent::Update(float TimeElapsed)
{
	sf::Vector2f MoveVector(m_Program.Ball.Velocity.x * TimeElapsed, m_Program.Ball.Velocity.y * TimeElapsed);
	m_Program.Ball.Shape.Move( MoveVector );

	switch (CheckWallCollision())
	{
		case NONE: break;
		case TOP:
		case BOTTOM: m_Program.Ball.Velocity.y *= (-1 * m_Program.Ball.Elasticity); break;
		//case RIGHT:
		//case LEFT: m_Program.Ball.Velocity.x *= (-1 * m_Program.Ball.Elasticity); break;
	}

	switch (CheckPaddleCollision())
	{	//TODO: add detection and handling of vertical collisions
		case NONE: break;
		case RIGHT:
		case LEFT: m_Program.Ball.Velocity.x *= (-1 * m_Program.Ball.Elasticity); break;
	}

	switch (CheckIfGoal())
	{
		case LEFT:  m_Program.PlayerScore++; 
					m_Program.Ball.Shape.SetPosition(0,0);
					m_Program.Ball.SetRandomVelocity(RIGHT);
					break;
		case RIGHT: m_Program.OpponentScore++; 
					m_Program.Ball.Shape.SetPosition(0,0);
					m_Program.Ball.SetRandomVelocity(LEFT);
					break;
	}
}

//returns the side the ball went in
int PhysicsComponent::CheckIfGoal()
{
	if( m_Program.Ball.Shape.GetPosition().x >= (400 + m_Program.Ball.Radius) )
		return RIGHT;

	else if( m_Program.Ball.Shape.GetPosition().x <= -(400 + m_Program.Ball.Radius) )
		return LEFT;

	else 
		return NONE;
}

//returns what wall was hit
int PhysicsComponent::CheckWallCollision()
{
	if (m_Program.Ball.Shape.GetPosition().y >= (300 - m_Program.Ball.Radius))
		return BOTTOM;

	else if (m_Program.Ball.Shape.GetPosition().y <= (-300 + m_Program.Ball.Radius))
		return TOP;

	else
		return NONE;
}

//returns the paddle hit 
int PhysicsComponent::CheckPaddleCollision()
{
	float BallLeftEdge = m_Program.Ball.Shape.GetPosition().x - m_Program.Ball.Radius;
	float BallRightEdge = m_Program.Ball.Shape.GetPosition().x + m_Program.Ball.Radius;
	float LeftPaddleRightEdge = m_Program.LeftPaddle.GetPosition().x + AbsoluteValue(m_Program.LeftPaddle.GetPointPosition(1).x); //Position + PaddleWidth
	float RightPaddleLeftEdge = m_Program.RightPaddle.GetPosition().x - AbsoluteValue(m_Program.RightPaddle.GetPointPosition(1).x);

	if  (BallLeftEdge < LeftPaddleRightEdge && BallIsNextToPaddle(LEFT))
		return LEFT;

	else if (BallRightEdge > RightPaddleLeftEdge && BallIsNextToPaddle(RIGHT))
		return RIGHT;

	else
		return NONE;
}

bool PhysicsComponent::BallIsNextToPaddle(int Paddle)
{
	if (Paddle == LEFT)
	{
		float BallBottom = m_Program.Ball.Shape.GetPosition().y + m_Program.Ball.Radius;
		float PaddleTop = m_Program.LeftPaddle.GetPosition().y - AbsoluteValue(m_Program.RightPaddle.GetPointPosition(1).y);
		bool BelowTop = BallBottom > PaddleTop;

		float BallTop = m_Program.Ball.Shape.GetPosition().y - m_Program.Ball.Radius;
		float PaddleBottom = m_Program.LeftPaddle.GetPosition().y + AbsoluteValue(m_Program.RightPaddle.GetPointPosition(1).y);
		bool AboveBottom = BallTop < PaddleBottom;

		return AboveBottom && BelowTop;
	}

	else if (Paddle == RIGHT)
	{
		float BallBottom = m_Program.Ball.Shape.GetPosition().y + m_Program.Ball.Radius;
		float PaddleTop = m_Program.RightPaddle.GetPosition().y - AbsoluteValue(m_Program.RightPaddle.GetPointPosition(1).y);
		bool BelowTop = BallBottom > PaddleTop;

		float BallTop = m_Program.Ball.Shape.GetPosition().y - m_Program.Ball.Radius;
		float PaddleBottom = m_Program.RightPaddle.GetPosition().y + AbsoluteValue(m_Program.RightPaddle.GetPointPosition(1).y);
		bool AboveBottom = BallTop < PaddleBottom;

		return AboveBottom && BelowTop;
	}
}