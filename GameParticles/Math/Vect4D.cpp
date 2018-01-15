//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <math.h>
//#include <assert.h>
#include "Vect4D.h"

Vect4D::Vect4D()
	: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
}

Vect4D::Vect4D(const float tx, const float ty, const float tz)
{
	this->_m = _mm_setr_ps(tx, ty, tz, 1.0f);
}

void Vect4D::set(const float tx, const float ty, const float tz)
{
	this->_m = _mm_setr_ps(tx, ty, tz, 1.0f);
}

Vect4D::~Vect4D()
{
	// nothing to delete
}

Vect4D::Vect4D(const Vect4D &t)
{
	this->_m = t._m;
}

Vect4D::Vect4D(const __m128 m)
	: _m(m)
{
}

Vect4D & Vect4D::operator = (const Vect4D &t)
{
	this->_m = t._m;
	return *this;
}

Vect4D & Vect4D::operator *= (const float scale)
{
	this->_m = _mm_mul_ps(this->_m, _mm_set1_ps(scale));
	this->w = 1.0f;
	return *this;
}

//void Vect4D::updatePosition(const float life)
void Vect4D::updatePosition(const Vect4D & v, const float time_elapsed, const float life)
{

	this->_m = _mm_add_ps(this->_m, _mm_mul_ps(v._m, _mm_set1_ps(time_elapsed)));

	//float tx = this->y + this->z*0.25f;
	float tx = 0.25f;
	tx *= this->z;
	tx += this->y;

	float ty = (-this->x);

	//float tz = this->x*(-0.25f);
	float tz = (-0.25f);
	tz *= this->x;

	float mag = sqrtf(tx * tx + ty * ty + tz * tz);

	if (mag > 0.0f)
	{

		this->_m = _mm_add_ps(this->_m, _mm_mul_ps((_mm_mul_ps(_mm_setr_ps(tx, ty, tz, 1.0f),
															   _mm_set1_ps(1 / mag))),
													_mm_set1_ps(0.05f * life)));
		//this->w = 1.0f;
	}
	//this->_m = _mm_add_ps(this->_m, _mm_mul_ps((_mm_mul_ps(_mm_setr_ps(tx, ty, tz, 1.0f), _mm_setr_ps(1 / mag, 1 / mag, 1 / mag, 1.0f))), _mm_setr_ps(0.05f * life, 0.05f * life, 0.05f * life, 1.0f)));

}

// End of file