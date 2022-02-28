#pragma once

#include "BaseComponent.h"

// update the transform to be at the position of the cursor
struct Cursor : public BaseComponent {
    Cursor() : BaseComponent() {}
    Cursor(const Cursor& obj) : BaseComponent(obj) {}
	Cursor(json obj) : BaseComponent(obj) {}
    ~Cursor() {}
	BaseComponent* Clone() {
		return new Cursor(*this);
	};
};