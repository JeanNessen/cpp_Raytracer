#pragma once

#include "Math.h"
#include "Environment.h"
#include "Projectile.h"

class Tracer
{
private:
	Projectile proj;
	Environment env;


public:
	Tracer();
	Tuple GetProjectilePosition() { return proj.position; }

	Projectile tick();

};

