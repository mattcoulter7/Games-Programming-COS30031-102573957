#pragma once

class Entity;
class Vector2;

class Instantiator {
public:
	Instantiator();
	Entity* Instantiate(size_t prefabid);
	Entity* Instantiate(size_t prefabid,Vector2 pos);
	void Destroy(size_t entityid);
};