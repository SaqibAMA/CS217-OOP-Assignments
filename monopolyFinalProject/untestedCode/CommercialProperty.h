#pragma once
#include "Property.h"
#include "Space.h"
#include <cstring>
using namespace std;
class CommercialProperty :public Property
{
public:
	//CONSTRUCTOS
	CommercialProperty();
	CommercialProperty(char* spaceType, int*, int, char*, char*, int, int, bool, int, int, int);
	CommercialProperty(CommercialProperty&);
	~CommercialProperty();
};

