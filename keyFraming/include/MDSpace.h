//
// MDSpace.hpp
// Cristian Troncoso 03/27/2016
//

#ifndef CRISTIAN_TRONCOSO_MDSPACE_H
#define CRISTIAN_TRONCOSO_MDSPACE_H

#include <iostream>
#include <string>
class XYZSpace
{
	public:
	float x,y,z;
	
	public:	
	XYZSpace();
	XYZSpace(float xIn, float yIn, float zIn);
	XYZSpace(float d);
	~XYZSpace();
	float *ptr();
	float *xyz();
	void set(int idx, float value);
	float& operator [](const int& idx);
	const float& operator [](const int& idx)const;
	/*!
 	 * \Brief    : Print out Vector.
 	 */
	void print(std::string comment);

};

class XYZWSpace: public XYZSpace
{
	public:
	float w;
	XYZWSpace();
	XYZWSpace(float xIn, float yIn, float zIn, float wIn);
	XYZWSpace(float c);
	~XYZWSpace();
	void print(std::string comment);
};
#endif //CRISTIAN_TRONCOSO_MDSPACE_H
