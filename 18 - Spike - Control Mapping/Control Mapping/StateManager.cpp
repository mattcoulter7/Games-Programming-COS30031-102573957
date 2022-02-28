#include "StateManager.h"

#include "MainMenu.h"

StateManager::StateManager() {
	SetState(new MainMenu()); // default state
}
StateManager::~StateManager() {
	delete _state;
}
void StateManager::SetState(BaseState* state) {
	delete _state;
	_state = state;
}
BaseState* StateManager::GetState() {
	return _state;
};
void StateManager::Update(SDL_Event& event) {
	_state->Update(*this, event);
}
void StateManager::Render() {
	_state->Render();
}