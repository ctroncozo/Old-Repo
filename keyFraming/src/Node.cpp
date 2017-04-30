#include "Node.h"

Node::Node(): parent(0){}
Node::~Node(){}

int Node::getId()
{
	return id;
}
void Node::addChild(Node *node)
{
	node->parent = this;
	children.push_back(node);
}

void Node::draw()
{
	std::cout << "Warming : Node->draw is not implemented yet " << std::endl;
}

void Node::update()
{
	std::cout << "Warming : Node->update is not implemented yet " << std::endl;
}
