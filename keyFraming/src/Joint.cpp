#include "Joint.h"

Joint::Joint(){}
Joint::Joint(char temp[256]):parent(0)
{
	std::string str(temp);
	jname = str;
	id = counter;
	
	offset = Vector3D(0,0,0);
	boxmin = Vector3D(0,0,0);
	boxmax = Vector3D(0,0,0);
	L = Matrix34::IDENTITY;  
	W = Matrix34::IDENTITY;
	
	++counter;
}

Joint::~Joint(){ --counter; }

void Joint::setOffset(Vector3D of)
{
    offset.x = of.x;
    offset.y = of.y;
    offset.z = of.z;
}
void Joint::setPose(Vector3D poseIn)
{
	pose.x = poseIn.x;
	pose.y = poseIn.y;
	pose.z = poseIn.z;
    dofx.setPhi(pose.x);
    dofy.setPhi(pose.y);
    dofz.setPhi(pose.z);

}

Vector3D Joint::getPose()
{
    dofx.clampToLimit();
    dofy.clampToLimit();
    dofz.clampToLimit();
    pose.x = dofx.getPhi();
    pose.y = dofy.getPhi();
    pose.z = dofz.getPhi();
	return pose;
}
void Joint::update()
{	
	// Compute World matrix W
	computeWorldMatrix();
    //std::cout<<jname;
	//W.Print("update world: ");
	// Recursively call update() on the children

}

void Joint::draw()
{
	// Do some OpenGL.
    
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(W);

	// Recursively call draw() on children.
	drawWireBox(boxmin.x, boxmin.y, boxmin.z, boxmax.x, boxmax.y, boxmax.z);
}

int Joint::getId()
{
	return id;
}

void Joint::addChild(Joint *node)
{
	node->parent = this;
	children.push_back(node);
}

bool Joint::load(Tokenizer &token)
{
	token.FindToken("{");
	while(1)
	{
		char temp[256];
		token.GetToken(temp);
		if(strcmp(temp,"offset") == 0)
		{
			offset.x = token.GetFloat();
			offset.y = token.GetFloat();
			offset.z = token.GetFloat();
		}
		else if(strcmp(temp,"boxmin") == 0)
		{
			boxmin.x = token.GetFloat();
			boxmin.y = token.GetFloat();
			boxmin.z = token.GetFloat();
		}
		else if(strcmp(temp,"boxmax") == 0)
		{
			boxmax.x = token.GetFloat();
			boxmax.y = token.GetFloat();
			boxmax.z = token.GetFloat();
		}
		else if(strcmp(temp,"rotxlimit") == 0)
		{
			//dof.rotxlimit[0] = token.GetFloat(); dof.rotxlimit[1] = token.GetFloat();
			float min = token.GetFloat(); 
			float max = token.GetFloat();
			dofx.setLimit(min,max);
		}
		else if(strcmp(temp,"rotylimit") == 0)
		{
			//dof.rotylimit[0] = token.GetFloat(); dof.rotylimit[1] = token.GetFloat();
			float min = token.GetFloat();
			float max = token.GetFloat();
			dofy.setLimit(min, max);
		}
		else if(strcmp(temp, "rotzlimit") == 0)
		{
			//dof.rotzlimit[0] = token.GetFloat(); dof.rotzlimit[1] = token.GetFloat();
			float min = token.GetFloat();
			float max = token.GetFloat();
			dofz.setLimit(min,max);
		}
		else if(strcmp(temp, "pose") == 0)
		{
			pose.x = token.GetFloat();
			pose.y = token.GetFloat();
			pose.z = token.GetFloat();
		
			dofx.setPhi(pose.x);
			dofy.setPhi(pose.y);
			dofz.setPhi(pose.z);	
		}
		else if(strcmp(temp, "balljoint") == 0)
		{
			token.GetToken(temp);
			Joint *jnt = new Joint(temp);
			jnt->load(token);
			jnt->computeWorldMatrix();
			addChild(jnt);
		}
		else if(strcmp(temp, "}") == 0)
		{
			return true;
		}
		else
		{
			token.SkipLine();// Unrecognized token
		}
	}
}

void Joint::computeLocalMatrix()
{
	float cx = cos(dofx.getPhi());
	float sx = sin(dofx.getPhi());
	float cy = cos(dofy.getPhi());
	float sy = sin(dofy.getPhi());
	float cz = cos(dofz.getPhi());
	float sz = sin(dofz.getPhi());

	L.a.Set(cy*cz, cy*sz, -1*sy);
	L.b.Set(sx*sy*cz - cx*sz, sx*sy*sz + cx*cz, sx*cy);
	L.c.Set(cx*sy*cz + sx*sz, cx*sy*sz - sx*cz, cx*cy);
	L.d.Set(offset.x, offset.y, offset.z);
}

void Joint::computeWorldMatrix()
{
	Matrix34 parentMatrix;
	
	// Compute Local matrix L
	computeLocalMatrix();
	//L.Print("update local: ");

	if(parent != 0)
	{
		parentMatrix = parent->getWorldMatrix();
	}
	W.Dot(parentMatrix, L);

}

Matrix34 Joint::getWorldMatrix()
{
	return W;
}
