#include "Vector4D.h"

Vector4D::Vector4D(): XYZWSpace() { }

Vector4D::Vector4D(float x, float y, float z, float w): XYZWSpace(x,y,z,w){ }

Vector4D::Vector4D( float c ):XYZWSpace(c){ }

Vector4D::Vector4D( const Vector4D& v ): XYZWSpace(v.x, v.y, v.z, v.w) { }

Vector4D::~Vector4D(){}

Vector4D Vector4D::operator+(const Vector4D& a) const
{
    return Vector4D(x + a.x, y + a.y , z + a.z, w + a.w);
}

Vector4D Vector4D::operator-(const Vector4D& a) const
{
    return Vector4D(x - a.x, y - a.y , z - a.z, w - a.w);
}

Vector4D Vector4D::operator-( void ) const
{
    return Vector4D( -x, -y, -z , -w);
}

Vector4D Vector4D::operator*( const float& c ) const
{
    return Vector4D( x * c, y * c, z * c, w * c );
}

Vector4D Vector4D::operator/( const float& c ) const
{
    const float rc = 1.0/c;
    return Vector4D( rc * x, rc * y, rc * z, rc * w );
}

void Vector4D::operator+=( const Vector4D& v )
{
    x += v.x; y += v.y; z += v.z; w += v.w;
}

void Vector4D::operator-=( const Vector4D& v )
{
    x -= v.x; y -= v.y; z -= v.z; w -=v.w;
}

void Vector4D::operator*=( const float& c )
{
    x *= c; y *= c; z *= c; w *= c;
}

void Vector4D::operator/=( const float& c )
{
    (*this) *= ( 1./c );
}

float Vector4D::magnitude( void ) const
{
    return sqrt( x*x + y*y + z*z + w*w);
}

float Vector4D::magnitude2( void ) const
{
    return x*x + y*y + z*z + w*w;
}

Vector4D Vector4D::unit( void ) const
{
    float rNorm = 1. / sqrt( x*x + y*y + z*z + w*w);
    return Vector4D( rNorm*x, rNorm*y, rNorm*z, rNorm*w );
}

void Vector4D::normalize( void )
{
    (*this) /= magnitude();
}

float Vector4D::operator *(const Vector4D& v ) const
{
    return x*v.x + y*v.y + z*v.z + w*v.w ;
}

