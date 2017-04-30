#ifndef CRISTIAN_TRONCOSO_JOINT_H
#define CRISTIAN_TRONCOSO_JOINT_H

#include "vector3D.h"
#include "Node.h"
#include "DOF.h"
#include "token.h"
#include "core.h"
#include <string>
class Joint
{

	private:
	static int counter;
	Vector3D offset;
	Vector3D boxmin;
	Vector3D boxmax;
	Vector3D pose;
	
	Matrix34 W;
	Matrix34 L;
	
	public:
    DOF dofx;
    DOF dofy;
    DOF dofz;
    
	int id;
	Joint *parent;
	std::vector<Joint*> children;
	std::vector<Joint*> siblings;
	std::string jname;
    Joint();
	Joint(char temp[256]);
	~Joint();

	int getId();
	bool load(Tokenizer &token);
	void addChild(Joint *n);
	void update();
	void draw();
    void setOffset(Vector3D of);
	void setPose(Vector3D poseIn);
	Vector3D getPose();
	void computeLocalMatrix();// Get the local matrix from Joint.DOF onject
	Matrix34 getWorldMatrix();// Return the joint world matrix. used by children
	void computeWorldMatrix();// comput and set the joint's world matrix
	static int getCounter(){ return counter; };
};

#endif //CRISTIAN_TRONCOSO_JOINT_H
