#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

class State;
class StateManager {
	public:
		StateManager(State* startState);
		void Start();
		void Stop();
		bool IsRunning();

		void SetState(State* state);
		std::string GetInput();
		void Update(std::string input);
		void Render();
	private:
		State *_state;
		bool _running;
};