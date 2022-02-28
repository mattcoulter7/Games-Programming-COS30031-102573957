#include <iostream>

#include "Adventure.h"

int main()
{
	Adventure adventure = Adventure();
	adventure.LoadFile();
	adventure.PlayWorld(0);

	return 0;
}
