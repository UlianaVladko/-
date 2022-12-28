#pragma once


class Node abstract {
public:

    int data=0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    
    Node();
};