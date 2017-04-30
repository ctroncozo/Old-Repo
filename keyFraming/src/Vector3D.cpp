#include "Vector3D.h"

Vector3D::Vector3D():XYZSpace() { }

Vector3D::Vector3D(float x, float y, float z):XYZSpace(x,y,z) { }

Vector3D::Vector3D( float d ) :XYZSpace(d) { }

Vector3D::Vector3D( const Vector3D& v ) : XYZSpace(v.x, v.y, v.z) { }

Vector3D::~Vector3D(){}

Vector3D Vector3D::operator+(const Vector3D& v) const
{
    return Vector3D(x + v.x, y + v.y , z + v.z);
}

Vector3D Vector3D::operator-(const Vector3D& a) const
{
    return Vector3D(x - a.x, y - a.y , z - a.z);
}

Vector3D Vector3D::operator-( void ) const
{
    return Vector3D( -x, -y, -z );
}

Vector3D Vector3D::operator*( const float& c ) const
{
    return Vector3D( x * c, y * c, z * c );
}

Vector3D Vector3D::operator/( const float& c ) const
{
    const float inv = 1.0/c;
    return Vector3D( inv * x, inv * y, inv * z );
}

Vector3D Vector3D::operator/( const Vector3D& v)
{
	return Vector3D( x/v.x, y/v.y, z/v.z);
}

void Vector3D::operator+=( const Vector3D& v )
{
    x += v.x; y += v.y; z += v.z;
}

void Vector3D::operator-=( const Vector3D& v )
{
    x -= v.x; y -= v.y; z -= v.z;
}

void Vector3D::operator*=( const float& c )
{
    x *= c; y *= c; z *= c;
}

void Vector3D::operator/=( const float& c )
{
    (*this) *= ( 1./c );
}

void Vector3D::operator/=( const Vector3D& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;

}

float Vector3D::magnitude( void ) const
{
    return sqrt( x*x + y*y + z*z );
}

float Vector3D::magnitude2( void ) const
{
    return x*x + y*y + z*z;
}

Vector3D Vector3D::unit( void ) const
{
    float rNorm = 1. / sqrt( x*x + y*y + z*z );
    return Vector3D( rNorm*x, rNorm*y, rNorm*z );
}

void Vector3D::normalize( void )
{
    (*this) /= magnitude();
}

float Vector3D::operator *( const Vector3D& v ) const
{
   return x*v.x + y*v.y + z*v.z ;
}

Vector3D Vector3D::operator ^( const Vector3D& v )
{
    return Vector3D( y*v.z - z*v.y,
                     z*v.x - x*v.z,
                     x*v.y - y*v.x );
}

void Vector3D::Set(float x0, float y0, float z0)
{
	x = x0; 
	y = y0; 
	z = z0;
}

void Vector3D::Zero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

void Vector3D::Lerp(float t, const Vector3D a, const Vector3D  b)
{
	*this	 = a;
	*this *= 1.0f - t;
	x		+= b.x * t;
	y		+= b.y * t;
	z		+= b.z * t;
}

float Vector3D::Dist2(const Vector3D a) const
{
	return (x - a.x) * (x - a.x) + (y - a.y) * (y - a.y) - (z - a.z) * (z - a.z);
}

Vector3D Vector3D::XAXIS(1.0f,0.0f,0.0f);
Vector3D Vector3D::YAXIS(0.0f,1.0f,0.0f);
Vector3D Vector3D::ZAXIS(0.0f,0.0f,1.0f);
Vector3D Vector3D::ORIGIN(0.0f,0.0f,0.0f);


