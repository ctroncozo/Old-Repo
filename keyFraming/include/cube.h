////////////////////////////////////////
// cube.h
////////////////////////////////////////

#ifndef CSE169_CUBE_H
#define CSE169_CUBE_H

#include "core.h"
#include "vector3D.h"
#include "matrix34.h"

////////////////////////////////////////////////////////////////////////////////

class SpinningCube {
public:
	SpinningCube();

	void Update();
	void Reset();
	void Draw();

private:
	// Constants
	float Size;
	Vector3D Position;
	Vector3D Axis;

	// Variables
	float Angle;
	Matrix34 WorldMtx;
};

////////////////////////////////////////////////////////////////////////////////

/*
SpinningCube is an example of a basic animating object. It can be used as a
pattern for creating more complex objects.
*/

#endif
