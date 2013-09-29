#include "Program.h"
#include <sstream>



Program::Program() : PhysicsComponent(*this), InputComponent(*this){ Initialize(); }

void Program::Initialize()
{
	BackroundColor = sf::Color::Black;
	PlayerScore= 0; OpponentScore= 0;

	InitializeWindow();
	InitializeGamePieces();
};

void Program::Begin(){

	Window.SetFramerateLimit(1.f/60.f);
	Window.UseVerticalSync(true);

	Draw();

	while (true)
	{	
		InputComponent.HandleInput();
		PhysicsComponent.Update(Window.GetFrameTime());
		Draw();
	}
}

void Program::InitializeWindow()
{
	Window.Create(sf::VideoMode(800,600), "Pong", sf::Style::Close | sf::Style::Resize);
	View.SetFromRect(sf::FloatRect(-400,-300,400,300));
	Window.SetView(View);
}

void Program::InitializeGamePieces()
{
	Ball.SetRandomVelocity(NONE);

	LeftPaddle = sf::Shape::Rectangle(sf::Vector2f(-20, 100), sf::Vector2f(20, -100), sf::Color::Red);
	LeftPaddle.SetPosition(-400 + 30, 0);
	RightPaddle = sf::Shape::Rectangle(sf::Vector2f(-20, 100), sf::Vector2f(20, -100), sf::Color::Blue);
	RightPaddle.SetPosition(400 - 30, 0);

	aDrawList += LeftPaddle;
	aDrawList += RightPaddle;
	aDrawList += Ball.Shape;	//TODO: make this recurssive / chain like
}

sf::String Framerate;
std::stringstream StringStream;

void Program::Draw()
{
	Window.Clear(BackroundColor);

	Window.Draw(aDrawList);

	//Framerate.SetText("Framerate: " + std::to_string((long long)(1 / Window.GetFrameTime())));
	//Window.Draw(Framerate);

	Window.Display();
}
