//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Math\Matrix.h"
#include "Math\Vect4D.h"
#include "Math\Align16.h"

// forward declare
class Vect4D;


class Particle : public Align16
{
public:
	
	Particle();	
	~Particle();
	Particle(const Particle &p);
	Particle & operator = (const Particle &p);

	Vect4D	position;
	Vect4D	velocity;
	Vect4D	scale;
};


#endif //PARTICLE_H
