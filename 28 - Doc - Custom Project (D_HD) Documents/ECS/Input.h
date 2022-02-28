#pragma once

#include <map>
#include "Vector2.h"
#include "SDL.h"

#include "EventDispatcher.hpp"

class Input {
public:
	enum class InputState
	{
		JustUp,
		Up,
		JustDown,
		Down
	};

	Input();
	~Input();

	void Update();
	bool GetInput(Uint8 inputCode);
	bool GetInputDown(Uint8 inputCode);
	bool GetInputUp(Uint8 inputCode);
	Vector2 GetMousePos();
	static Input* Instance();
	Vector2 mouse_pos{ 0,0 };
	Vector2 last_mouse_pos{ 0,0 };
	Vector2 mouse_velocity{ 0,0 };
private:
	static Input _instance;

	int mouse_x = 0;
	int mouse_y = 0;
	Uint8 GetInputCode();
	SDL_Event _event;
	std::map<Uint8, InputState> _inputStates;
};