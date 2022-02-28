#include "StateManager.h"

#include "State.h"

StateManager::StateManager(State *startState) {
    _running = false;
    _state = startState;
};
void StateManager::Start() {
    _running = true;
};
void StateManager::Stop() {
    _running = false;
};
bool StateManager::IsRunning() {
    return _running;
};

void StateManager::SetState(State* state) {
    _state = state;
};
std::string StateManager::GetInput() {
    return _state->GetInput();
};
void StateManager::Update(std::string input) {
    _state->Update(this, input);
};
void StateManager::Render() {
    _state->Render();
};
