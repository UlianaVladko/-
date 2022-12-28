#pragma once

#include "node.h"


template<class Node>

class Tree abstract {
private:
	Node* root;

public:
	
	virtual Node* LeftRotate(Node*) = 0;
	virtual Node* RightRotate(Node*) = 0;
	virtual void RemoveNode(Node* parent, Node* curr, int stuff)=0;	
	virtual void InsertNode(int data) = 0;

};
