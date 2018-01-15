//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Math\Matrix.h"
#include "Math\Vect4D.h"
#include "Particle.h"
#include "Settings.h"

// forward declare
class particle;
class Matrix;
class Vect4D;

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	ParticleEmitter(const ParticleEmitter & e);
	ParticleEmitter & operator = (const ParticleEmitter & e);

	void update();
	void draw();
	void Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc);
	void CreateLinkedList();

private:
	
	Matrix *		matrixList;
	Particle *		headParticle;
	const int		max_particles = NUM_PARTICLES;
	const float		max_life = MAX_LIFE;
	float			life;
	float			rotation;
	float			last_loop;
	char			pad0;
	char			pad1;
	char			pad2;
	char			pad3;

};

#endif // PARTICLEEMITTER_H
