#ifndef CRISTIAN_TRONCOSO_LIGHT_H
#define CRISTIAN_TRONCOSO_LIGHT_H

#ifdef __APPLE__
	#include<GLUT/glut.h>
#else
	#include<GL/glut.h>
#endif

#include "Color.h"
#include "Vector3D.h"
#include "Vector4D.h"

#define POINT_LIGHT 0
#define DIRECTIONAL_LIGHT 1

class Light
{
	int type;
	int bindingId;
	Color ambient;
	Color diffuse;
	Color specular;
	Vector4D position;
	Vector4D direction;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	public:
	Light();
    Light(int ID, Vector4D pos);
	Light(Color *color, int cSize, Vector4D pos, Vector4D dir, float * attenuation);
	~Light();	
	void setProperties(Color *color, int cSize, Vector3D pos, Vector3D dir, float *attenuation);
	void bind(int id);
	void unbind();
};
#endif // CRISTIAN_TRONCOSO_LIGHT_H


