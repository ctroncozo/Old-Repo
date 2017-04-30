#include "Skeleton.h"


Skeleton::Skeleton(){}
Skeleton::~Skeleton(){}

//void Skeleton::load(const char *filename)
void Skeleton::load(const char *filename)
{
	Tokenizer token;
	token.Open(filename);
	token.FindToken("balljoint");
	char temp[256];
	token.GetToken(temp);

	// parse tree
	root = new Joint(temp);
	nt = new Ntree(root);
	root->load(token);

	nt->setTreeSize(Joint::getCounter());
    jointsArr = nt->DFS(root, NONE);
	// Finish
	token.Close();
}

Matrix34 Skeleton::getWorldMatrix(int i)
{
	std::vector<Joint*>J = nt->DFS(root, NONE);
	Matrix34 W = J.at(i)->getWorldMatrix();
	return W;
}

void Skeleton::draw()
{
	nt->DFS(root, DRAW);
}

/*
void Skeleton::update(int joint, Vector3D pose, Joint &j)
{
    
	int size = nt->getTreeSize();
	if(joint < 0) joint = 0;
	if(joint > size) joint = size;
	 
	jointsArr = nt->DFS(root, NONE);
    j = *jointsArr.at(joint);
	
    
    Vector3D originalPose = j.getPose();
    
    if(pose.x == 0) pose.x = originalPose.x;
    else pose.x += originalPose.x;
    
    if(pose.y == 0) pose.y = originalPose.y;
    else pose.x += originalPose.x;
    
    if(pose.z == 0) pose.z = originalPose.z;
    else pose.x += originalPose.x;
    
    if(pose.x != 0 || pose.y != 0 || pose.z!=0)
        jointsArr.at(joint)->setPose(pose);
	
    //jointsArr.at(joint)->getPose().Print("pose");
	//jointsArr.at(joint)->getWorldMatrix().Print("to World");

    j.getPose().Print();
    
	
}
 */
void Skeleton::update2()
{
    nt->DFS(root, UPDATE);
}
void Skeleton::reset()
{
    jointsArr = nt->DFS(root, NONE);
    for(int i = 0; i < nt->getTreeSize(); i++)
        jointsArr.at(i)->setPose(Vector3D(0,0,0));
}
	
