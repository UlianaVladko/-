#pragma once

#include <iostream>
#include "node.h"
using namespace std;


class RBNode:public Node {
public:

    int data=0;
    RBNode* left = nullptr;
    RBNode* right = nullptr;
    RBNode* parent = nullptr;
    string color;

    RBNode();
};