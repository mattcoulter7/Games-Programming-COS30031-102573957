#pragma once

#include "BaseComponent.h"

// added to entity to make it collide with screen 
struct ScreenCollider : public BaseComponent {
	ScreenCollider(size_t entityid) : BaseComponent(entityid) {}
};