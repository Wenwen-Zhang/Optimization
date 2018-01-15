//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include "DO_NOT_MODIFY\Timer.h"
#include "DO_NOT_MODIFY\GlobalTimer.h"
#include "DO_NOT_MODIFY\OpenGLInterface.h"

#define UNUSED_VAR(v) ((void *)v)
#include "ParticleEmitter.h"
#include "Settings.h"


ParticleEmitter::ParticleEmitter()
	: life(0.0f),
	  rotation(0.0f),
	  last_loop(globalTimer::getTimerInSec())
{
	// nothing to do
	CreateLinkedList();
	//memcpy(this->drawBuffer, this->headParticle, NUM_PARTICLES * sizeof(Particle));
	this->matrixList = new Matrix[(unsigned int)NUM_PARTICLES]();
}


ParticleEmitter::~ParticleEmitter()
{
	// do nothing
}

void ParticleEmitter::update()
{
	// get current time
	float current_time = globalTimer::getTimerInSec();
	
	// total elapsed
	float time_elapsed = current_time - last_loop;


	life += time_elapsed;

	rotation += 0.5f * time_elapsed * 2.01f;

	Particle *p = this->headParticle;

		if (this->life < max_life)
		{
			for(int i = 0; i < max_particles; i++)
			{
				p->position.updatePosition(p->velocity, time_elapsed, life);
				p++;
			}

		}

		else 
		{
			this->life = 0.0f;
			this->rotation = 0.0f;

			for (int i = 0; i < max_particles; i++)
			{
				p->position.set(0.0f, 0.0f, 0.0f);// = start_position;
				p->velocity.set(0.0f, 1.0f, 0.0f);// = start_velocity;
				p->scale.set(1.0f, 1.0f, 1.0f);
				this->Execute(p->position, p->velocity, p->scale);
				p++;
			}

		}

	last_loop = current_time;
}
	 
void ParticleEmitter::draw()
{

	Particle * pTmp = this->headParticle;
	
	Matrix *tmp = this->matrixList;

	for (int i = 0; i < max_particles; i++)
	{		
		tmp->TotalTransform(pTmp->position, this->rotation, pTmp->scale);

		// set the transformation matrix
		glLoadMatrixf(reinterpret_cast<float*>(&(*tmp)));

		// draw the trangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// clears or flushes some internal setting, used in debug, but is need for performance reasons
		// magic...  really it's magic.
		GLenum glError = glGetError();
		UNUSED_VAR(glError);
	
		//pTmp = pTmp->next;
		pTmp++;
		tmp++;		
	}

}

void ParticleEmitter::Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc)
{
	// Add some randomness...

	// Ses it's ugly - I didn't write this so don't bitch at me
	// Sometimes code like this is inside real commerical code ( so now you know how it feels )
	
	// x - variance
	float var = static_cast<float>(rand() % 1000) * 0.001f;
	float sign = static_cast<float>(rand() % 2);
	if(sign == 0)
	{
		var *= -1.0;
	}
	//var *= pos_variance.x;
	pos.x += var;


	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	if(sign == 0)
	{
		var *= -1.0;
	}
	//var *= pos_variance.y;
	pos.y += var;
	
	// z - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	if(sign == 0)
	{
		var *= -1.0;
	}
	//var *= pos_variance.z;
	pos.z += var;
	
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	
	// x  - add velocity
	if(sign == 0)
	{
		var *= -1.0;
	}

	//var *= vel_variance.x;
	vel.x += var;

	// y - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	if(sign == 0)
	{
		var *= -1.0;
	}

	//var *= vel_variance.y;
	var *= 4.0f;
	vel.y += var;
	
	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	if(sign == 0)
	{
		var *= -1.0;
	}

	var *= 0.4f;
	vel.z += var;
	
	// correct the sign
	var = 2.0f * static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	
	if(sign == 0)
	{
		var *= -1.0;
	}
	sc *= var;
}

void ParticleEmitter::CreateLinkedList() 
{

	this->headParticle = new Particle[(unsigned int)NUM_PARTICLES]();

	Particle *p = this->headParticle;

	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		this->Execute(p->position, p->velocity, p->scale);
		p++;
	}


}

ParticleEmitter::ParticleEmitter(const ParticleEmitter & e)
{
	this->matrixList = e.matrixList;
	this->headParticle = e.headParticle;
	this->life = e.life;
	this->rotation = e.rotation;
	this->last_loop = e.last_loop;
}

ParticleEmitter & ParticleEmitter::operator = (const ParticleEmitter & e)
{
	this->matrixList = e.matrixList;
	this->headParticle = e.headParticle;
	this->life = e.life;
	this->rotation = e.rotation;
	this->last_loop = e.last_loop;

	return *this;
}


// End of file