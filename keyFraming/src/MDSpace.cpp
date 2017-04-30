#include "MDSpace.h"

XYZSpace::XYZSpace():x(0.0f), y(0.0f), z(0.0f){}

XYZSpace::XYZSpace(float xIn, float yIn, float zIn):x(xIn), y(yIn), z(zIn){}

XYZSpace::XYZSpace(float d):x(d), y(d), z(d){}

XYZSpace::~XYZSpace(){}

float *XYZSpace::ptr(){ return (&x); }

float *XYZSpace::xyz(){ return (&x); }

void XYZSpace::set(int idx, float value){ (&x) [idx] = value; }

float& XYZSpace::operator [] (const int& idx){ return (&x)[idx]; }

const float& XYZSpace::operator [] (const int& idx) const {	return (&x)[idx]; }

void XYZSpace::print(std::string comment)
{
    std::cout << comment << "<x:" << x <<  ", y:" << y << ", z:" << z << ">" << std::endl;
}

XYZWSpace::XYZWSpace():XYZSpace(),w(0.0f){}

XYZWSpace::XYZWSpace(float xIn, float yIn, float zIn, float wIn):XYZSpace(xIn, yIn, zIn), w(wIn){}

XYZWSpace::XYZWSpace(float c):XYZSpace(c), w(c){}

XYZWSpace::~XYZWSpace(){}

void XYZWSpace::print(std::string comment)
{
	std::cout << comment << "<x:" <<x<< ", y:" <<y<< ", z:" <<z<< ", w:" <<w<<">"<< std::endl;
}


