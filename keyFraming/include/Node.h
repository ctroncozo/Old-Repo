#ifndef CRISTIAN_TRONCOSO_NODE_H
#define CRISTIAN_TRONCOSO_NODE_H
#include <iostream>
#include <vector>
class Node
{
	public:
	int id;
	Node *parent;
	std::vector<Node*> children;
	std::vector<Node*> siblings;

	Node();
	~Node();

	int getId();
	void addChild(Node *n);	
	virtual void draw();
	virtual void update();

};
#endif //CRISTIAN_TRONCOSO_NODE_H
