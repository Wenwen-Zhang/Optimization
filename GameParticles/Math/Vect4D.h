//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

// Vect4D.h
//
// This is a 4 dimensional Vect4D class
#ifndef Vect4D_H
#define Vect4D_H

// includes
//#include "Enum.h"
#include "Align16.h"
#include <xmmintrin.h>
#include <smmintrin.h>  


#pragma warning(disable: 4201)
#pragma warning(disable: 4587)
#pragma warning(disable: 4588)


// Foward Declarations
class Matrix;

// class
class Vect4D : public Align16
{
public:

	Vect4D();	
	Vect4D( const float tx, const float ty, const float tz);
	~Vect4D();
	Vect4D & operator = (const Vect4D &t);
	Vect4D(const Vect4D &t);

	Vect4D(const __m128 m);

	void set(const float tx, const float ty, const float tz);
	
	Vect4D & operator *= (const float scale);

	void updatePosition(const Vect4D &v, const float times, const float life);

	union
	{
		__m128	_m;

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};

#endif  //Vect4D.h
