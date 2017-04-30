#ifndef CRISTIAN_TRONCOSO_POINT_H
#define CRISTIAN_TRONCOSO_POINT_H 
#if defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "MDSpace.h"
#include "Vector3D.h"
class Vector3D;
/*!
 * \brief	: 	The following class, Point2D defines some basic functions of handling 
 * 				a point on 2D graphics,Specially those than can be represented as an (x,y).
 */
class Point2D
{	
	private:
	float x2,y2;
	public:
	// Default constructor
	Point2D();
	//	Constructor that set x and y to used defined values
	Point2D(float xIn, float yIn);
	// draw
	void draw(float *color);
};

/*!
 * \brief	: 	The following class, Point3D defines some basic functions of handling 
 *					a point on 3D graphics,Specially those than can be represented as an (x,y).
 */
class Point3D: public XYZSpace
{
	// Default constructor
 	Point3D();
	// Constructor that set x and y to user defined values.
	Point3D(float xIn, float yIn, float zIn);
	// Point + Vector return a Point
	inline Point3D operator+(const Vector3D& v) const;
	// Point - Vector return a Point
	inline Point3D operator-(const Vector3D& v) const;
 	// Draw point into frame buffer
	void draw(float *color);
};

#endif //CRISTIAN_TRONCOSO_POINT_H
