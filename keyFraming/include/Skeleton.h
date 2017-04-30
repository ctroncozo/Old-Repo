#ifndef CRISTIAN_TRONCOSO_SKELETON_H
#define CRISTIAN_TRONCOSO_SKELETON_H

#include "vector3D.h"
#include "Ntree.h"
#include "Joint.h"

class Skeleton
{
	Ntree *nt;
	Joint *root;
	
	public:
	Skeleton();
	~Skeleton();
	//void load(const char *fname);
	void load(const char *filename);
	void draw();
	void update(int joint, Vector3D pose, Joint &j);
   void update2();
	void reset();
	Matrix34 getWorldMatrix(int i);
    
   std::vector<Joint*> jointsArr;
	
		
};
#endif// CRISTIAN_TRONCOSO_SKELETON_H
