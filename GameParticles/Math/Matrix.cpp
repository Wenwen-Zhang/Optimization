//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <Math.h>
//#include <assert.h>
//#include "Vect4d.h"
#include "Matrix.h"

Matrix::Matrix()
{	
}


Matrix::Matrix( const Matrix& t )
{ // copy constructor
	this->v0._m = t.v0._m;
	this->v1._m = t.v1._m;
	this->v2._m = t.v2._m;
	this->v3._m = t.v3._m;
}


Matrix::~Matrix()
{
	// nothign to delete
}

Matrix & Matrix::operator = (const Matrix& t)
{
	this->v0._m = t.v0._m;
	this->v1._m = t.v1._m;
	this->v2._m = t.v2._m;
	this->v3._m = t.v3._m;

	return *this;
}

void Matrix::setIdentMatrix() 
{ // initialize to the identity matrix
	
	this->v0._m = _mm_setr_ps(1.0f, 0.0f, 0.0f, 0.0f);
	this->v1._m = _mm_setr_ps(0.0f, 1.0f, 0.0f, 0.0f);
	this->v2._m = _mm_setr_ps(0.0f, 0.0f, 1.0f, 0.0f);
	this->v3._m = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
}


void Matrix::setTransMatrix(const float tx, const float ty, const float tz)
{
	this->v0._m = _mm_setr_ps(1.0f, 0.0f, 0.0f, 0.0f);
	this->v1._m = _mm_setr_ps(0.0f, 1.0f, 0.0f, 0.0f);
	this->v2._m = _mm_setr_ps(0.0f, 0.0f, 1.0f, 0.0f);
	this->v3._m = _mm_setr_ps(tx, ty, tz, 1.0f);
}

Matrix::Matrix(const Vect4D &tV0, const Vect4D &tV1, const Vect4D &tV2, const Vect4D &tV3)
{
	this->v0._m = tV0._m;
	this->v1._m = tV1._m;
	this->v2._m = tV2._m;
	this->v3._m = tV3._m;
}

Matrix Matrix::operator*(const Matrix & rhs) const
{ // matrix multiplications
	return Matrix(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->v0.x), rhs.v0._m), _mm_mul_ps(_mm_set1_ps(this->v0.y), rhs.v1._m)),
		_mm_mul_ps(_mm_set1_ps(this->v0.z), rhs.v2._m)),
		_mm_mul_ps(_mm_set1_ps(this->v0.w), rhs.v3._m)),
		_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->v1.x), rhs.v0._m), _mm_mul_ps(_mm_set1_ps(this->v1.y), rhs.v1._m)),
			_mm_mul_ps(_mm_set1_ps(this->v1.z), rhs.v2._m)),
			_mm_mul_ps(_mm_set1_ps(this->v1.w), rhs.v3._m)),
		_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->v2.x), rhs.v0._m), _mm_mul_ps(_mm_set1_ps(this->v2.y), rhs.v1._m)),
			_mm_mul_ps(_mm_set1_ps(this->v2.z), rhs.v2._m)),
			_mm_mul_ps(_mm_set1_ps(this->v2.w), rhs.v3._m)),
		_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->v3.x), rhs.v0._m), _mm_mul_ps(_mm_set1_ps(this->v3.y), rhs.v1._m)),
			_mm_mul_ps(_mm_set1_ps(this->v3.z), rhs.v2._m)),
			_mm_mul_ps(_mm_set1_ps(this->v3.w), rhs.v3._m)));
}


float Matrix::Determinant() const
{
	// A = { a,b,c,d / e,f,g,h / j,k,l,m / n,o,p,q }
	// A = { 0,1,2,3 / 4,5,6,7 / 8,9,10,11 / 12,13,14,15 }
	
	// det(A) = a*det( { f,g,h / k,l,m / o,p,q } )
	//			- b*det( { e,g,h / j,l,m / n,p,q } )
	//			+ c*det( { e,f,h / j,k,m / n,o,q } )
	//			- d*det( { e,f,g / j,k,l / n,o,p } )
	
	// det(A) = (a (f (lq - mp) - g (kq - mo) + h (kp - lo) ) )
	//			- (b (e (lq - mp) - g (jq - mn) + h (jp - ln) ) )
	//			+ (c (e (kq - mo) - f (jq - mn) + h (jo - kn) ) )
	//			- (d (e (kp - lo) - f (jp - ln) + g (jo - kn) ) )
	
	// ta = (lq - mp)
	float ta = (m10 * m15) - (m11 * m14);
	// tb = (kq - mo)
	float tb = (m9 * m15) - (m11 * m13);
	// tc = (kp - lo)
	float tc = (m9 * m14) - (m10 * m13);
	// td = (jq - mn)
	float td = (m8 * m15) - (m11 * m12);
	// te = (jo - kn)
	float te = (m8 * m13) - (m9 *  m12);
	// tf = (jp - ln)
	float tf = (m8 * m14) - (m10 * m12);
	
	// det(A) = (a (f*ta  - g*tb + h*tc) )
	//			- (b (e*ta - g*td + h*tf) )
	//			+ (c (e*tb - f*td + h*te) )
	//			- (d (e*tc - f*tf + g*te) )
	return ((m0 * ((m5 * ta) - (m6 * tb) + (m7 * tc)))
			- (m1 * ((m4 * ta) - (m6 * td) + (m7 * tf)))
			+ (m2 * ((m4 * tb) - (m5 * td) + (m7 * te)))
			- (m3 * ((m4 * tc) - (m5 * tf) + (m6 * te))));
	
}

void Matrix::getInverse()
{
	float det = Determinant();
	if (fabsf(det) < 0.0001f)
	{
		// do nothing, Matrix is not invertable
	}
	else
	{
		Matrix tmp;

		// load		ABC		(3)		ABC--
		float t1 = (m10*m15) - (m11*m14);
		float t2 = (m9*m15) - (m11*m13);
		float t3 = (m9*m14) - (m10*m13);

		// a = f(ta) - g(tb) + h(tc)
		tmp.m0 = (m5*t1) - (m6*t2) + (m7*t3);
		// b = -( b(ta) - c(tb) + d(tc))
		tmp.m1 = -((m1*t1) - (m2*t2) + (m3*t3));

		// load		JK		(5)		ABCJK
		float t4 = (m8*m15) - (m11*m12);
		float t5 = (m8*m14) - (m10*m12);
		// e = - ( e(ta) - g(tj) + h(tk))
		tmp.m4 = -((m4*t1) - (m6*t4) + (m7*t5));
		// f = a(ta) - c(tj) + d(tk)
		tmp.m5 = (m0*t1) - (m2*t4) + (m3*t5);

		// unload	AJ		(3)		-BC-K
		// load		P		(4)		PBC-K
		t1 = (m8*m13) - (m9*m12);
		// n = -( e(tc) - f(tk) + g(tp))
		tmp.m12 = -((m4*t3) - (m5*t5) + (m6*t1));
		// o = a(tc) - b(tk) + c(tp)
		tmp.m13 = (m0*t3) - (m1*t5) + (m2*t1);

		// unload	KC		(2)		PB---
		// load		J		(3)		PBJ--
		t3 = (m8*m15) - (m11*m12);

		// j = e(tb) - f(tj) + h(tp)
		tmp.m8 = (m4*t2) - (m5*t3) + (m7*t1);
		// k = - ( a(tb) - b(tj) + d(tp))
		tmp.m9 = -((m0*t2) - (m1*t3) + (m3*t1));

		// unload	BPJ		(0)		-----
		// load		DLM		(3)		DLM--
		t1 = (m6*m15) - (m7*m14);
		t2 = (m4*m15) - (m7*m12);
		t3 = (m4*m14) - (m6*m12);

		// g = - ( a(td) - c(tl) + d(tm))
		tmp.m6 = -((m0*t1) - (m2*t2) + (m3*t3));

		// load		FR		(5)		DLMFR
		t4 = (m5*m14) - (m6*m13);
		t5 = (m4*m13) - (m5*m12);

		// p = - ( a(tf) - b(tm) + c(tr))
		tmp.m14 = -((m0*t4) - (m1*t3) + (m3*t5));

		// unload	M		(4)		DL-FR
		// load		E		(5)		DLEFR
		t3 = (m5*m15) - (m7*m13);

		// l = a(te) - b(tl) + d(tr)
		tmp.m10 = (m0*t3) - (m1*t2) + (m3*t5);

		// unload	LR		(3)		D-EF-
		// c = b(td) - c(te) + d(tf)
		tmp.m2 = (m1*t1) - (m2*t3) + (m3*t4);

		// unload	DEF		(0)		-----
		// load		GHI		(3)		GHI--
		t1 = (m6*m11) - (m7*m10);
		t2 = (m5*m11) - (m7*m9);
		t3 = (m5*m10) - (m6*m9);

		// d = -( b(tg) - c(th) + d(ti) )
		tmp.m3 = -((m1*t1) - (m2*t2) + (m3*t3));

		// load		NO		(5)		GHINO
		t4 = (m4*m11) - (m7*m8);
		t5 = (m4*m10) - (m6*m8);

		// h = a(tg) - c(tn) + d(to)
		tmp.m7 = (m0*t1) - (m2*t4) + (m3*t5);

		// unload	G		(4)		-HINO
		// load		Q		(5)		QHINO
		t1 = (m4*m9) - (m5*m8);

		// m = -( a(th) - b(tn) + d(tq))
		tmp.m11 = -((m0*t2) - (m1*t4) + (m3*t1));

		// unload	HN		(3)		Q-I-O
		// q = a(ti) - b(to) + c(tq)
		tmp.m15 = (m0*t3) - (m1*t5) + (m2*t1);

		this->v0._m = _mm_mul_ps(_mm_set1_ps(1.0f / det), tmp.v0._m);
		this->v1._m = _mm_mul_ps(_mm_set1_ps(1.0f / det), tmp.v1._m);
		this->v2._m = _mm_mul_ps(_mm_set1_ps(1.0f / det), tmp.v2._m);
		this->v3._m = _mm_mul_ps(_mm_set1_ps(1.0f / det), tmp.v3._m);
	}
}


//scaleMatrix * transCamera * transParticle * rotParticle * scaleMatrix;

//	scaleMatrix								transCamera
//	{	sx		0		0		0	}		{	1		0		0		0	}
//	{	0		sy		0		0	}		{	0		1		0		0	}
//	{	0		0		sz		0	}		{	0		0		1		0	}
//	{	0		0		0		1	}		{	cx		cy		sz		1	}

//	transParticle							rotParticle
//	{	1		0		0		0	}		{	cos(az)		-sin(az)	0		0	}
//	{	0		1		0		0	}		{	sin(az)		 cos(az)	0		0	}
//	{	0		0		1		0	}		{	  0				0		1		0	}
//	{	tx		ty		tz		1	}		{	  0				0		0		1	}

//	scaleMatrix * transCamera
//	{	sx		0		0		0	}
//	{	0		sy		0		0	}
//	{	0		0		sz		0	}
//	{	cx		cy		cz		1	}

//	scaleMatrix * transCamera * transParticle
//	{	sx		 0		  0			0	}
//	{	0		 sy		  0			0	}
//	{	0		 0		  sz		0	}
//	{  cx+tx    cy+ty    cz+tz		1	}

//	scaleMatrix * transCamera * transParticle * rotParticle
//	{   sx*cos(az)			sx*(-sin(az))			 0			0	}
//	{   sy*sin(az)			 sy*cos(az)				 0			0	}
//	{		0					0					 sz			0	}
//	{(cx+tx)*cos(az) 	  (cx+tx)*(-sin(az))		cz+tz		1	}
//	 +(cy+ty)*sin(az)	  +(cy+ty)*cos(az)

//	scaleMatrix * transCamera * transParticle * rotParticle * scaleMatrix;
//	{ sx*sx*cos(az)		        sx*sy*(-sin(az))			 0			0	}
//	{ sx*sy*sin(az)		        sy*sy*cos(az)			     0			0	}
//	{		0					      0					   sz*sz		0	}
//	{sx*((cx+tx)*cos(az)     sy*((cx+tx)*(-sin(az))	     sz(cz+tz)		1	}
//	     +(cy+ty)*sin(az))	     +(cy+ty)*cos(az))

void Matrix::TotalTransform(const Vect4D & pos, const float rot, const Vect4D & scale)
{
	Vect4D scaleTmp(_mm_mul_ps(scale._m, scale._m));
	//Vect4D transTmp(_mm_add_ps(camera._m, pos._m));


	const float cosRot = cosf(rot);
	const float sinRot = sinf(rot);

	float scaleXYSin = scale.x;
	scaleXYSin *= scale.y;
	scaleXYSin *= sinRot;

	this->v0._m = _mm_setr_ps(scaleTmp.x * cosRot, -scaleXYSin, 0.0f, 0.0f);
	this->v1._m = _mm_setr_ps(scaleXYSin, scaleTmp.y * cosRot, 0.0f, 0.0f);
	this->v2._m = _mm_setr_ps(0.0f, 0.0f, scaleTmp.z, 0.0f);
	//this->v3._m = _mm_setr_ps(scale.x * (cosRot * transTmp.x + sinRot * transTmp.y), 
	//						  scale.y * (cosRot * transTmp.y - sinRot * transTmp.x), 
	//						  scale.z * transTmp.z, 1.0f);

	this->v3._m = _mm_setr_ps(scale.x * (cosRot * pos.x + sinRot * (pos.y - 3.0f)),
		scale.y * (cosRot * (pos.y - 3.0f) - sinRot * pos.x),
		scale.z * (pos.z - 10.0f), 1.0f);
}

// End of file