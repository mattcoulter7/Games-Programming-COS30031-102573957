#include "Input.h"
#include "ECS.h"
#include "EventDispatcher.hpp"

Input::Input() {
}
Input::~Input() {
}

void Input::Update() {
	ECS* ecs = ECS::ECS_ENGINE();

	// capture mouse position
	SDL_GetMouseState(&mouse_x, &mouse_y);
	last_mouse_pos = mouse_pos;
	mouse_pos.x = mouse_x;
	mouse_pos.y = mouse_y;
	mouse_velocity = last_mouse_pos.To(mouse_pos);
	if (mouse_pos != last_mouse_pos) {
		EventDispatcher::Dispatch("MouseMove", mouse_pos, mouse_velocity);
	}


	// update existing inputs
	for (auto& pair : _inputStates) {
		// sets just down -> down or Just up to up
		if (pair.second == InputState::JustDown || pair.second == InputState::Down) {
			_inputStates[pair.first] = InputState::Down;
			EventDispatcher::Dispatch("Input", pair.first,true);
		}
		else if (pair.second == InputState::JustUp || pair.second == InputState::Up) {
			_inputStates[pair.first] = InputState::Up;
			EventDispatcher::Dispatch("Input", pair.first, false);
		}
	}

	// handle new inputs
	while (SDL_PollEvent(&_event)) {
		Uint8 code = -1;
		switch (_event.type) {
		case SDL_MOUSEBUTTONDOWN: case SDL_KEYDOWN:
			code = GetInputCode();
			_inputStates[code] = InputState::JustDown;
			EventDispatcher::Dispatch("InputDown", GetInputCode());
			break;
		case SDL_MOUSEBUTTONUP: case SDL_KEYUP:
			code = GetInputCode();
			_inputStates[code] = InputState::JustUp;
			EventDispatcher::Dispatch("InputUp", GetInputCode());
			break;
		case SDL_QUIT:
			ecs->Stop();
			break;
		default:
			break;
		}
	}
}
bool Input::GetInput(Uint8 inputCode) {
	//Returns true while the user holds down the input identified by name.
	if (!_inputStates.count(inputCode)) {
		return false; // asume it is already up
	}
	return _inputStates[inputCode] == InputState::Down || _inputStates[inputCode] == InputState::JustDown;
}
bool Input::GetInputDown(Uint8 inputCode) {
	//Returns true during the frame the user starts pressing down the input identified by name.
	if (!_inputStates.count(inputCode)) {
		return false;
	}
	return _inputStates[inputCode] == InputState::JustDown;
}
bool Input::GetInputUp(Uint8 inputCode) {
	//Returns true during the frame the user releases the input identified by name.
	if (!_inputStates.count(inputCode)) {
		return false;
	}
	return _inputStates[inputCode] == InputState::JustUp;
}
Vector2 Input::GetMousePos() {
	return Vector2{(float)mouse_x,(float)mouse_y};
};
Input* Input::Instance() {
	return &_instance;
}

Uint8 Input::GetInputCode() {
	switch (_event.type) {
	case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
		return _event.button.button;
	case SDL_KEYDOWN: case SDL_KEYUP:
		return _event.key.keysym.sym;
	default:
		return -1;
	}
	return -1;
};
Input Input::_instance;