#include "Material.h"

Material::Material()
{
	float param[13];
	Color::Mat(0,param);
		
	specular = Color(param);
	ambient  = Color(param + 4);
	diffuse  = Color(param + 8);
	shininess[0] =  param[12];
}

Material::~Material(){}

void Material::apply()
{
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular.ptr());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.ptr());
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.ptr());
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
