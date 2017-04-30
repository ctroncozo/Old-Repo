#ifndef CRISTIAN_TRONCOSO_MATERIAL_H
#define CRISTIAN_TRONCOSO_MATERIAL_H

#ifdef __APPLE__
	#include<GLUT/glut.h>
#else
	#include<GL/glut.h>
#endif

#include "Color.h"

class Material
{
	Color ambient;
	Color diffuse;
	Color specular;

	float shininess[];

	public:
	Material();
	~Material();
	void apply();
};
#endif //CRISTIAN_TRONCOSO_MATERIAL_H
