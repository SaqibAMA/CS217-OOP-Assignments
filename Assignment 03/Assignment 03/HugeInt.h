#pragma once

#include <iostream>
#

class HugeInt
{
private:
	int* ptr;
	int length;
	int maxLen;

public:
	// Constructors
	HugeInt();

	// Destructors
	~HugeInt();
};

