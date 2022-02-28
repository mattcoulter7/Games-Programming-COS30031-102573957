#pragma once

#include "BaseComponent.h"

// added to entity to make it collide with screen 
struct ScreenCollider : public BaseComponent {
	ScreenCollider() : BaseComponent() {}
	ScreenCollider(const ScreenCollider& obj) : BaseComponent(obj) {};
	ScreenCollider(json obj) : BaseComponent(obj) {}
	~ScreenCollider() {}
	BaseComponent* Clone() {
		return new ScreenCollider(*this);
	};
};