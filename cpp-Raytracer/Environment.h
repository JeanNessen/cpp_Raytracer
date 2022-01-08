#pragma once
#include "Math.h"

class Environment
{
public:
	Environment(Tuple grav, Tuple wind);
	Tuple gravity;	//vector
	Tuple wind;		//vector
};

