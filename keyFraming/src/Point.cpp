#include "Point.h"

Point2D::Point2D():x2(0.0f), y2(0.0f)
{
	glPointSize(4.0);
}

Point2D::Point2D(float xIn, float yIn): x2(xIn), y2(yIn)
{
	glPointSize(4.0);
}

void Point2D::draw(float *color)
{
	glBegin(GL_POINTS);
	glColor3f(color[0], color[1], color[2]);
	glVertex2f((GLfloat)x2, (GLfloat)y2);
	glEnd();
}

Point3D::Point3D():XYZSpace(){}

Point3D::Point3D(float xIn, float yIn, float zIn):XYZSpace(xIn, yIn, zIn){}

inline Point3D Point3D::operator+(const Vector3D& v) const{return Point3D(x + v[0], y + v[1], z + v[2]);}

inline Point3D Point3D::operator-(const Vector3D& v) const
{
	Vector3D v3(v);
	return Point3D(x - v3.x, y - v3.y, z - v3.z);
} 

void Point3D::draw(float *color)
{
	glBegin(GL_POINTS);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f((GLfloat)x, (GLfloat)y, (GLfloat)z);
	glEnd(); 
}
