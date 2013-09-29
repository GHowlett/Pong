#ifndef INPUT_COMPONENT
#define INPUT_COMPONENT

#include "Common.h"

class Program;

class InputComponent
{public:

	InputComponent(Program& program);

	void HandleInput();

private:

	Program& program;
	const sf::Input& Input;
	float OldMouseY;
};

#endif