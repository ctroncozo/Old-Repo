//
// Face.hpp
// Cristian Troncoso 2/15/2016
//
#include "Face.h"

Face::Face(){}

Face::Face (int *fVertexes, Vector4D inColor)
{
	faceVertexes[0] = fVertexes[0];
   faceVertexes[1] = fVertexes[1];
	faceVertexes[2] = fVertexes[2];
	color           = Vector4D(inColor);
}

Face::Face(Vector3D *vertices, Vector3D normal, Vector4D color)
{
	vertexes[0] = vertices[0];
	vertexes[1] = vertices[1];
	vertexes[2] = vertices[2];
	  
	normal      = Vector3D(normal);
	color       = Vector4D(color);
}
 
Face::Face(Vector3D *vertices, Vector3D normal)
{
	vertexes[0] = vertices[0];
	vertexes[1] = vertices[1];
	vertexes[2] = vertices[2];
	normal      = Vector3D(normal);
}

Face::Face(Vector3D *vertices)
{
	vertexes[0] = vertices[0];
   vertexes[1] = vertices[1];
	vertexes[2] = vertices[2];
	color       = Vector4D(0.5,0.5,0.5,1);
	normal      = Vector3D(0);
}

Face::~Face(){}

void Face::setVertexes(Vertex A, Vertex B, Vertex C)
{
	vertexes[0] = A;
	vertexes[1] = B;
	vertexes[2] = C;
}

void Face::setNormalAvg(Vector3D n0, Vector3D n1, Vector3D n2)
{
	Vector3D n_tot = n0 + n1 + n2;
	normal = n_tot * (1.0f/3.0f);
	normal.normalize();
}

void Face::setNormal()
{
	Vector3D AB = vertexes[1].getPosition() - vertexes[0].getPosition();
	Vector3D AC = vertexes[2].getPosition() - vertexes[0].getPosition();
	  
	normal = AB ^ AC;

	//TODO : Normalize.
	//normal = normal->normalize();
}

void Face::setFaceColor(float *inColor)
{
	color[0] = inColor[0];
	color[1] = inColor[1];
	color[2] = inColor[2];
	color[3] = 1;
}

Vector3D Face::getNormal()
{
	return normal;
}

Vector4D Face::getColor()
{
	return color;
}

