#include "Tracer.h"
#include <iostream>

Tracer::Tracer():
	proj(Projectile(Point(0, 1, 0), Vector(1, 1.8, 0).normalized()*11.25)),
	env(Environment(Vector(0, -0.1, 0), Vector(-0.01, 0, 0)))
{

}

Projectile Tracer::tick()
{
	proj.position = proj.position + proj.velocity;
	proj.velocity = proj.velocity + env.gravity + env.wind;
	std::cout << "projectile position: (" << proj.position.x << ", " << proj.position.y << ", " << proj.position.z << ")" << std::endl;
	return proj;
}
