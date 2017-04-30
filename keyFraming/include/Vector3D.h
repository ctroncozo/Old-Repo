//
// Vector3D.hpp
// Cristian Troncoso 2/15/2016
//
#ifndef CRISTIAN_TRONCOSO_VECTOR3D_H
#define CRISTIAN_TRONCOSO_VECTOR3D_H

#include <math.h>
#include "Point.h"
#include "MDSpace.h"

class Vector3D: public XYZSpace
{
	public:
   /*! 
    * \Brief   : Constructor, Initializes vector (0,0,0).
    */
   Vector3D();
   /*!
    * \Brief   : Constructor, Initializes to vector (x,y,z).
    */
   Vector3D(float x, float y, float z);
   /*!
    * \Brief   : Constructor, Initializes to vector (d,d,d).
    */
   Vector3D( float d );
   /*!
    * \Brief   : Constructor, Initializes from another Vector3D.
    */
   Vector3D( const Vector3D& v );
   /*!
    * \Brief   : Destructor
    */
   ~Vector3D();
   /*!
    * \Brief   : Addition.
    */
    Vector3D operator+(const Vector3D& v) const;
   /*!
    * \Brief   : Subtraction.
    */
    Vector3D operator-(const Vector3D& a) const;
   /*!
    * \Brief   : Negation.
    */
    Vector3D operator-( void ) const;
   /*!
    * \Brief   : Right scalar multiplication.
    */
    Vector3D operator*( const float& c ) const;
   /* 
    * \Brief   : scalar division.
    */
    Vector3D operator/( const float& c ) const;
	 /*!/
	  * \Brief 	: Component-wise vector division
	  */
	 Vector3D operator/( const Vector3D& v);
   /*!
    * \Brief   : addition / assignment
    */
    void operator+=( const Vector3D& v );
   /*!
    * \Brief   : subtraction / assignment.
    */
    void operator-=( const Vector3D& v );
   /*!
    * \Brief   : scalar multiplication / assignment.
    */
    void operator*=( const float& c );
   /*!
    * \Brief   : scalar division / assignment.
    */
    void operator/=( const float& c );
	/*!
	 * \Brief 	:  Component-wise vector division-assignment operator.
	 */
	 void operator/= (const Vector3D & v);
   /*!
    * \Brief   : Returns Euclidean length.
    */
    float magnitude( void ) const;
   /*!
    * \Brief   :Returns Euclidean length squared.
    */
    float magnitude2( void ) const;
   /*!
    * \Brief   :Returns unit vector.
    */
    Vector3D unit( void ) const;
   /**
    * \Brief   : Divides by Euclidean length.
    */
    void normalize( void );
   /*!
    * \Brief    : Dot product.
    */
    float operator *( const Vector3D& v ) const;
	/*!
    * \Brief    : Cross product.
    */
    Vector3D operator ^( const Vector3D& v );
	/*!
	 * \Brief	 : Set
	 */
	 void Set(float x0, float y0, float z0);
	/*!
    * \Brief	 : Zero
	 */
	 void Zero();
	 /*!
	  * \Brief		: Linerar interpolation
	  */
	  void Lerp(float t, const Vector3D a, const Vector3D  b);
	 /*!
	  * \Brief 	: Distance to
	  */
	  float Dist2(const Vector3D a) const;
	 // Static vectors
	 static Vector3D XAXIS,YAXIS,ZAXIS;
	 static Vector3D ORIGIN;
	 void Print(char *name=0) const	{if(name) printf("%s=",name); printf("{%f,%f,%f}\n",x,y,z);}

};
#endif //CRISTIAN_TRONCOSO_VECTOR3D_H
