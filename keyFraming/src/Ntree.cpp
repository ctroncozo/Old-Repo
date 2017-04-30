#include "Ntree.h"

Ntree::Ntree(Joint *node) : root(node), sizeOFtree(0){}
Ntree::~Ntree(){}

int Ntree::getTreeSize()
{
	return sizeOFtree;
}

void Ntree::setTreeSize(int s)
{
	sizeOFtree = s;
}

void Ntree::visit(Joint *node, bool visited[], int command)
{
	int id = node->id;
	// Mark current node as visited
	visited[id] = true;
	
	if( command == UPDATE)
		node->update();
	else if(command == DRAW)
		node->draw();
	else if(command == NONE)
		joints.push_back(node);

	// Use recursion to visit all Childrens of this node
	if(node->children.size() > 0 )
	{
		for(std::vector<Joint*>::iterator  i = node->children.begin(); i != node->children.end(); ++i)
		{		
			if(!visited[(*i)->id])
			{
				visit(*i, visited, command);
			}
		}
	}
	else
	{
		// No children
		//std::cout<<"( no children )"<<std::endl
	}
}

//void Ntree::DFS(Joint *node, int command)
std::vector<Joint*>Ntree::DFS(Joint *node, int command)
{
	bool *visited = new bool[sizeOFtree];
	for(int i = 0; i < sizeOFtree; i++)
	{
		visited[i] = false;
	}

	// Start DFS recursion
	if(joints.size() > 0)
		joints.clear();
	visit(node, visited, command);
	return joints;
}


