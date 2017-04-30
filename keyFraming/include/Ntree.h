#ifndef CRISTIAN_TRONCOSO_NTREE_H
#define CRISTIAN_TRONCOSO_NTREE_H
#include <vector>
#include "Joint.h"

#define UPDATE 0
#define DRAW	1
#define NONE	2
class Ntree
{
	Joint *root;
	int sizeOFtree;
	void visit(Joint *node, bool visited[], int command);
	std::vector<Joint*> joints;
	public:
	Ntree(Joint *node);
	~Ntree();
	int getTreeSize();
	void setTreeSize(int s);
	//void DFS(Joint *node, int command);
	std::vector<Joint*> DFS(Joint *node, int command);
	Matrix34 getWorlMatrix(int i);
};
#endif //CRISTIAN_TRONCOSO_NTREE_H
