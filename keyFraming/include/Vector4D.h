//
// Vector4D.hpp
// Cristian Troncoso 2/15/2016
//
#ifndef CRISTIAN_TRONCOSO_VECTOR4D_H
#define CRISTIAN_TRONCOSO_VECTOR4D_H

#include <math.h>
#include "Point.h"
#include "MDSpace.h"

class Vector4D: public XYZWSpace
{
	public:
   /*! 
    * \Brief   : Constructor, Initializes vector (0,0,0).
    */
   Vector4D();
   /*!
    * \Brief   : Constructor, Initializes to vector (x,y,z).
    */
   Vector4D(float x, float y, float z, float w);
   /*!
    * \Brief   : Constructor, Initializes to vector (c,c,c).
    */
   Vector4D( float c );
   /*!
    * \Brief   : Constructor, Initializes from another Vector4D.
    */
   Vector4D( const Vector4D& v );
   /*!
    * \Brief   : Destructor
    */
   ~Vector4D();
   /*!
    * \Brief   : Addition.
    */
    Vector4D operator+(const Vector4D& v) const;
   /*!
    * \Brief   : Subtraction.
    */
    Vector4D operator-(const Vector4D& v) const;
   /*!
    * \Brief   : Negation.
    */
    Vector4D operator-( void ) const;
   /*!
    * \Brief   : Right scalar multiplication.
    */
    Vector4D operator*( const float& c ) const;
   /* 
    * \Brief   : scalar division.
    */
    Vector4D operator/( const float& c ) const;
   /*!
    * \Brief   : addition / assignment
    */
    void operator+=( const Vector4D& v );
   /*!
    * \Brief   : subtraction / assignment.
    */
    void operator-=( const Vector4D& v );
   /*!
    * \Brief   : scalar multiplication / assignment.
    */
    void operator*=( const float& c );
   /*!
    * \Brief   : scalar division / assignment.
    */
    void operator/=( const float& c );
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
    Vector4D unit( void ) const;
   /**
    * \Brief   : Divides by Euclidean length.
    */
    void normalize( void );
   /*!
    * \Brief    : Dot product.
    */
    float operator *( const Vector4D& v ) const;
      
};
#endif //CRISTIAN_TRONCOSO_VECTOR4D_H
