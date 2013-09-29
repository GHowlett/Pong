#include "Common.h"
#include "Program.h"
#include "Input Component.h"

InputComponent::InputComponent(Program& program): program(program), OldMouseY(0), Input(program.Window.GetInput()) {}

void InputComponent::HandleInput()
{
	sf::Event Event;

	while (program.Window.GetEvent(Event))
	{
		if(Event.Type == sf::Event::MouseEntered)
			OldMouseY = Input.GetMouseY();

		else if(Event.Type == sf::Event::MouseMoved){
			float MouseChangeY = Event.MouseMove.Y - OldMouseY;
			program.RightPaddle.Move(0, MouseChangeY); 
			OldMouseY = Event.MouseMove.Y;
		}

		else if(Event.Type== sf::Event::Closed)
			program.Window.Close();
	}
}