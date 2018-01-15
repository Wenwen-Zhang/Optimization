//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include "Particle.h"

Particle::Particle()
	: position(0.0f, 0.0f, 0.0f),
	  velocity(0.0f, 1.0f, 0.0f),
	  scale(1.0f, 1.0f, 1.0f)
{

}

Particle::~Particle()
{
	// nothing to do
}

Particle::Particle(const Particle &p)
{
	this->position = p.position;
	this->velocity = p.velocity;
	this->scale = p.scale;
}

Particle & Particle::operator = (const Particle &p)
{
	this->position = p.position;
	this->velocity = p.velocity;
	this->scale = p.scale;
	return *this;
}

// End of file


