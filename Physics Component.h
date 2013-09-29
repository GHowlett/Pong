#ifndef PHYSICS_COMPONENT
#define PHYSICS_COMPONENT

class Program;

class PhysicsComponent
{public:
	Program& m_Program;

	PhysicsComponent(Program& program);
	
	void Update(float TimeElapsed);

	//returns the side the ball went in
	int CheckIfGoal();

	//returns # of the wall hit or '0'
	int CheckWallCollision();

	//returns # of the paddle hit or '0'
	int CheckPaddleCollision();

	bool BallIsNextToPaddle(int Paddle);
};

#endif