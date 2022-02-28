#pragma once

#include <stdlib.h>

class rand_extension {
public:
	static int between(int min, int max) {
		return rand() % (max - min + 1) + min;
	}
};