//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef MATRIX_H
#define MATRIX_H

// includes
//#include "Enum.h"
#include "Align16.h"
#include <xmmintrin.h>
#include <smmintrin.h>
#include <Vect4D.h>

#pragma warning(disable: 4201)
#pragma warning(disable: 4587)
#pragma warning(disable: 4588)

// forward declare
class Vect4D;

// class
class Matrix: public Align16
{
public:

	Matrix();	
	Matrix(const Matrix& t);	
	~Matrix();
	Matrix & operator = (const Matrix& t);

	Matrix(const Vect4D &tV0, const Vect4D &tV1, const Vect4D &tV2, const Vect4D &tV3);

	void setIdentMatrix();

	void setTransMatrix(const float tx, const float ty, const float tz);

	//void TotalTransform(const Vect4D & camera, const Vect4D & pos, const float rot, const Vect4D & scale) ;
	
	void TotalTransform(const Vect4D & pos, const float rot, const Vect4D & scale);

	Matrix operator*(const Matrix &t ) const;

	float Determinant() const;

	void getInverse();

	union
	{
		struct
		{
			Vect4D v0;
			Vect4D v1;
			Vect4D v2;
			Vect4D v3;
		};

		struct
		{
			// ROW 0
			float m0;
			float m1;
			float m2;
			float m3;

			// ROW 1
			float m4;
			float m5;
			float m6;
			float m7;

			// ROW 2
			float m8;
			float m9;
			float m10;
			float m11;

			// ROW 3
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};

};

#endif  // Matrix.h
