#include "DOF.h"
#include <iostream>

DOF::DOF()
{
	phi = 0;
	limit[0] = -1000; limit[1] = 1000;
}

DOF::~DOF(){}

void DOF::setPhi(float p)
{
	phi = p;
	//clampToLimit();
}

float DOF::getPhi()
{
    //clampToLimit();
	return phi;
}
void DOF::setLimit(float min, float max)
{
	limit[0] = min;
	limit[1] = max;
}

void DOF::clampToLimit()
{
	if(phi < limit[0]) phi = limit[0];
	if(phi > limit[1]) phi = limit[1];
}

