#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Input.h"
#include "Vector2.h"

#include "json.hpp"
using json = nlohmann::json;

class System {
public:
	System() {}
	System(json obj) {}
	virtual ~System() {};
	virtual void Update(double dt) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
private:
	virtual void AddEventListeners() = 0;
};