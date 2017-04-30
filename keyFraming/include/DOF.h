#ifndef CRISTIAN_TRONCOSO_DOF_H
#define CRISTIAN_TRONCOSO_DOF_H
#include <math.h>
#include "matrix34.h"
#include "vector3D.h"

#define DOF_RX					1
#define DOF_RY					2
#define DOF_RZ					3
#define BALL_AND_SOCKET         4
class DOF
{
	public:

	float phi;
	// Min and Max rotate limimit
	float limit[2];
	
	DOF();
	
	~DOF();	
	void setPhi(float p);
	float getPhi();
	void clampToLimit();
	void setLimit(float min, float max);
};
#endif //CRISTIAN_TRONCOSO_H
