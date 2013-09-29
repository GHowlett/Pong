#ifndef COMMON
#define COMMON

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum {NONE= 0, TOP, RIGHT, BOTTOM, LEFT};

const float GoalWidth = 500;

class DrawList : public sf::Drawable
{public:
	
	void AddItem(sf::Drawable& Item) { 
		List.push_back(&Item); }

	DrawList operator += (sf::Drawable& Item) { 
		AddItem(Item); return *this; }

	virtual void Render(sf::RenderTarget& target) const {
		for(int i= 0; i< List.size(); i++)
			target.Draw(*List[i]);
	}

private:
	
	std::vector<sf::Drawable*> List;
};

extern DrawList aDrawList;

class GraphicsComponent : private sf::Drawable
{
	GraphicsComponent()
	{
		aDrawList += *this;
	}
};

template <typename T>
T AbsoluteValue(T Value)
{
	if (Value < 0) Value *= -1;
	return Value;
};

#endif