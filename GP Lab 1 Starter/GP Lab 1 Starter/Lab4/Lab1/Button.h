#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "transform.h"
#include "Texture.h"
class Button
{
public:

	Button();
	~Button();


	SDL_Point clickedPoint;
	
	bool isPressed;
	glm::vec2 position;

private:


};

