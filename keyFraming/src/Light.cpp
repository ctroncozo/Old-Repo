#include "Light.h"
	
Light::Light()
{
	float param[12];
	Color::Light(2, param);

	specular 				= Color(param);
	ambient 				= Color(param + 4);
	diffuse  				= Color(param + 8);
	position 				= Vector4D(1.0f, 1.0f,1.0f, 0.0f);	// Last zero indicates it is a directional light.
	constantAttenuation 	= 1.0f;
	linearAttenuation       = 0.0f;
	quadraticAttenuation	= 0.5f;
	type 					= DIRECTIONAL_LIGHT;	
}



Light::Light(int ID, Vector4D pos)
{
	float param[12];
	Color::Light(ID, param);

	specular 				= Color(param);
	ambient 			    = Color(param + 4);
	diffuse  				= Color(param + 8);
	position 				= pos;	// Last zero indicates it is a directional light.
	constantAttenuation 	= 1.0f;
	linearAttenuation  	    = 0.0f;
	quadraticAttenuation	= 0.5f;
	type 						= DIRECTIONAL_LIGHT;	
}

Light::Light(Color *color, int cSize, Vector4D pos, Vector4D dir, float *attenuation)
{
	// TODO; Take care when size is less than 3

	ambient 					= color[0];
	diffuse 					= color[1];
	specular					= color[2];
	position					= pos;
	direction				    = dir;
	constantAttenuation         = attenuation[0];
	linearAttenuation           = attenuation[1];
	quadraticAttenuation        = attenuation[2];
}

Light::~Light(){}

/*!
 * \Brief		:	Light sources have a number of properties, such as color, position, and direction.
 */
void Light::setProperties(Color *color, int cSize, Vector3D pos, Vector3D dir, float *attenuation)
{
	
}

void Light::bind(int id)
{
	if(id < 0 || id > 7)
	{
		std::cout<<"ERROR: Binding Id is not valid"<<std::endl;
		return;
	}
	bindingId = id;		

	GLfloat light0[] = {1.0, 1.0, 1.0};	
	glLightfv(GL_LIGHT0 + id, GL_POSITION, position.ptr());
	glLightfv(GL_LIGHT0 + id, GL_AMBIENT,ambient.ptr());
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, diffuse.ptr());
	glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular.ptr());
	//glLightf(GL_LIGHT0 + id, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
	
	glEnable(GL_LIGHT0 + id);
}

void Light::unbind()
{
	glDisable(GL_LIGHT0 + bindingId);
	bindingId = -1;
   
}
