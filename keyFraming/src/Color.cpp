/**
 * @file Color.cpp
 * @author  Cristian Troncoso <troncoso.cristian.e@gmail.com>
 * @version 1.0
 *
 */
#include "Color.h"

Color::Color():r(0.0f),g(0.0f),b(0.0f),a(1.0){}
Color::Color(float ir,float ig,float ib):r(ir),g(ig),b(ib),a(1.0f){}
Color::Color(float ir,float ig,float ib,float ia):r(ir),g(ig),b(ib),a(ia){}
Color::Color(float ptr[4]):r(ptr[0]),g(ptr[1]),b(ptr[2]),a(ptr[3]){}
Color::~Color(){}

float *Color::ptr(){return (&r);}

float& Color::operator[](const int& idx)
{
	assert((idx > 0 && idx < 3) && "Error: idx out of scope");
	return (&r) [idx];
}

const float& Color::operator[](const int& idx) const 
{
	assert((idx > 0 && idx < 3) && "Error: idx out of scope");
	return (&r) [idx];		
}
	
Color Color::interpolate(Color& c1, float t)
{
	 t = clampf(0.0, 1.0, t);
	 return Color((1.0 - t) * r + t * c1.r,
			        (1.0 - t) * g + t * c1.g,
					  (1.0 - t) * b + t * c1.b,
					  (1.0 - t) * a + t * c1.a);
}

void Color::print(std::string comment)
{
	std::cout<<comment<<"< r: "<<r<<", g: "<<g<<", b: "<<b<<",a: "<<a<<std::endl;
}

Color Color::LightYellow()		{return Color(1.000f, 1.000f, 0.878f, 1.0f);}
Color Color::Violet()				{return Color(0.933f, 0.510f, 0.933f, 1.0f);}
Color Color::Lime()					{return Color(0.000f, 1.000f, 0.000f, 1.0f);}
Color Color::Green()				{return Color(0.000f, 0.502f, 0.000f, 1.0f);}
Color Color::Cyan()					{return Color(0.000f, 1.000f, 1.000f, 1.0f);}
Color Color::SkyBlue()				{return Color(0.529f, 0.808f, 0.922f, 1.0f);}
Color Color::Blue()					{return Color(0.000f, 0.000f, 1.000f, 1.0f);}
Color Color::Brown()				{return Color(0.647f, 0.165f, 0.165f, 1.0f);}
Color Color::White()				{return Color(1.000f, 1.000f, 1.000f, 1.0f);}
Color Color::Gray()					{return Color(0.502f, 0.502f, 0.502f, 1.0f);}
Color Color::Black()				{return Color(0.000f, 0.000f, 0.000f, 1.0f);}
Color Color::Red()					{return Color(1.000f, 0.000f, 0.000f, 1.0f);}
void  Color::Mat(int ID, float *param)
{ 
	float properties[2][13] =	{	{	1.0f, 1.0f, 0.0f, 1.0f, // specular
                                        0.0f, 0.0f, 0.0f, 1.0f, // ambient
                                        0.0f, 0.0f, 0.0f, 1.0f, // diffuse
                                        0.0f,                    // shininess
                                    },
                                    {	0.6f, 0.8f, 1.0f, 1.0f,
                                        0.1f, 0.1f, 0.1f, 1.0f,
                                        0.6f, 0.4f, 0.2f, 1.0f,
                                        20.0f
                                    }
												
                                };
                                param[0] = properties[ID][0];
                                param[1] = properties[ID][1];
                                param[2] = properties[ID][2];
                                param[3] = properties[ID][3];
                                param[4] = properties[ID][4];
                                param[5] = properties[ID][5];
                                param[6] = properties[ID][6];
                                param[7] = properties[ID][7];
                                param[8] = properties[ID][8];
                                param[9] = properties[ID][9];
                                param[10] = properties[ID][10];
                                param[11] = properties[ID][11];
                                param[12] = properties[ID][12];


}
void  Color::Light(int ID, float *param)
{ 
	float properties[5][12] =	{	{	1.0f, 0.0f, 0.0f, 1.0f, // specular
                                        1.0f, 0.0f, 0.0f, 1.0f, // ambient
                                        1.0f, 0.0f, 0.0f, 1.0f, // diffuse
                                    },
                                    {	0.0f, 0.0f, 1.0f, 1.0f,
                                        0.0f, 0.0f, 1.0f, 1.0f,
                                        0.0f, 0.0f, 1.0f, 1.0f,
                                    },
												{	1.0f, 1.0f, 1.f, 1.0f,
													0.78f, 0.57f, 0.11f, 1.0f,
													1.9f, 0.01f, 1.0f, 1.0f,
												},
												{ 0.0215f, 0.1745f, 0.0215f,1.0f,
												 0.07568f, 0.61424f, 0.07568f,1.0f,
												 0.633f, 0.727811f, 0.633f,1.0f,
												},
												{ 1.0, 1.0, 1.0,1.0,
												  0.5, 0.0, 0.0,1.0,
												  0.7, 0.6, 0.6, 1.0,
												}
                                };
                                param[0] = properties[ID][0];
                                param[1] = properties[ID][1];
                                param[2] = properties[ID][2];
                                param[3] = properties[ID][3];
                                param[4] = properties[ID][4];
                                param[5] = properties[ID][5];
                                param[6] = properties[ID][6];
                                param[7] = properties[ID][7];
                                param[8] = properties[ID][8];
                                param[9] = properties[ID][9];
                                param[10] = properties[ID][10];
                                param[11] = properties[ID][11];
}
																	


