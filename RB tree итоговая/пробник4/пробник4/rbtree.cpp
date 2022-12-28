#include "rbtree.h"
#include <iostream>
using namespace std;

    void RBTree::InsertNode(int stuff) {
        if (root == nullptr) {
            root = new RBNode();
            root->data = stuff;
            root->parent = nullptr;
            root->color = "BLACK";
            cout << "Element inserted.\n";
        }
        else {
            auto linker = root;
            RBNodepoint newnode = new RBNode();
            newnode->data = stuff;

            while (linker != nullptr) {
                if (linker->data > stuff) {
                    if (linker->left == nullptr) {
                        linker->left = newnode;
                        newnode->color = "RED";
                        newnode->parent = linker;
                        cout << "Element inserted.\n"; break;
                    }
                    else { linker = linker->left; }
                }
                else {
                    if (linker->right == nullptr) {
                        linker->right = newnode;
                        newnode->color = "RED";
                        newnode->parent = linker;
                        cout << "Element inserted.\n"; break;
                    }
                    else { linker = linker->right; }
                }
            }
            RB_Insert_Fixup(newnode);
        }
    }

    void RBTree::RB_Insert_Fixup(RBNodepoint z) {
        while (z->parent->color == "RED") {
            auto grandparent = z->parent->parent;
            auto uncle = root;
            if (z->parent == grandparent->left) {
                if (grandparent->right) { uncle = grandparent->right; }
                if (uncle->color == "RED") {
                    z->parent->color = "BLACK";
                    uncle->color = "BLACK";
                    grandparent->color = "RED";
                    if (grandparent->data != root->data) { z = grandparent; }
                    else { break; }
                }
                else if (z == grandparent->left->right) {
                    LeftRotate(z->parent);
                }
                else {
                    z->parent->color = "BLACK";
                    grandparent->color = "RED";
                    RightRotate(grandparent);
                    if (grandparent->data != root->data) { z = grandparent; }
                    else { break; }
                }
            }
            else {
                if (grandparent->left) { uncle = grandparent->left; }
                if (uncle->color == "RED") {
                    z->parent->color = "BLACK";
                    uncle->color = "BLACK";
                    grandparent->color = "RED";
                    if (grandparent->data != root->data) { z = grandparent; }
                    else { break; }
                }
                else if (z == grandparent->right->left) {
                    RightRotate(z->parent);
                }
                else {
                    z->parent->color = "BLACK";
                    grandparent->color = "RED";
                    LeftRotate(grandparent);
                    if (grandparent->data != root->data) { z = grandparent; }
                    else { break; }
                }
            }
        }
        root->color = "BLACK";
    }


    void RBTree::RemoveNode(RBNodepoint parent, RBNodepoint curr, int stuff) {
        if (curr == nullptr) { return; }
        if (curr->data == stuff) {
            //CASE -- 1
            if (curr->left == nullptr && curr->right == nullptr) {
                if (parent->data == curr->data) { root = nullptr; }
                else if (parent->right == curr) {
                    RB_Delete_Fixup(curr);
                    parent->right = nullptr;
                }
                else {
                    RB_Delete_Fixup(curr);
                    parent->left = nullptr;
                }
            }
            //CASE -- 2
            else if (curr->left != nullptr && curr->right == nullptr) {
                int swap = curr->data;
                curr->data = curr->left->data;
                curr->left->data = swap;
                RemoveNode(curr, curr->right, stuff);
            }
            else if (curr->left == nullptr && curr->right != nullptr) {
                int swap = curr->data;
                curr->data = curr->right->data;
                curr->right->data = swap;
                RemoveNode(curr, curr->right, stuff);
            }
            //CASE -- 3
            else {
                bool flag = false;
                RBNodepoint temp = curr->right;
                while (temp->left) { flag = true; parent = temp; temp = temp->left; }
                if (!flag) { parent = curr; }
                int swap = curr->data;
                curr->data = temp->data;
                temp->data = swap;
                RemoveNode(parent, temp, swap);
            }
        }
    }

    void RBTree::Remove(int stuff) {
        auto temp = root;
        auto parent = temp;
        bool flag = false;
        if (!temp) { RemoveNode(nullptr, nullptr, stuff); }

        while (temp) {
            if (stuff == temp->data) { flag = true; RemoveNode(parent, temp, stuff); break; }
            else if (stuff < temp->data) { parent = temp; temp = temp->left; }
            else { parent = temp; temp = temp->right; }
        }

        if (!flag) { cout << "\nElement doesn't exist in the table"; }
    }

    void RBTree::RB_Delete_Fixup(RBNodepoint z) {
        while (z->data != root->data && z->color == "BLACK") {
            auto sibling = root;
            if (z->parent->left == z) {
                if (z->parent->right) { sibling = z->parent->right; }
                if (sibling) {
                    //CASE -- 1
                    if (sibling->color == "RED") {
                        sibling->color = "BLACK";
                        z->parent->color = "RED";
                        LeftRotate(z->parent);
                        sibling = z->parent->right;
                    }
                    //CASE -- 2
                    if (sibling->left == nullptr && sibling->right == nullptr) {
                        sibling->color = "RED";
                        z = z->parent;
                    }
                    else if (sibling->left->color == "BLACK" && sibling->right->color == "BLACK") {
                        sibling->color = "RED";
                        z = z->parent;
                    }
                    //CASE -- 3
                    else if (sibling->right->color == "BLACK") {
                        sibling->left->color = "BLACK";
                        sibling->color = "RED";
                        RightRotate(sibling);
                        sibling = z->parent->right;
                    }
                    else {
                        sibling->color = z->parent->color;
                        z->parent->color = "BLACK";
                        if (sibling->right) { sibling->right->color = "BLACK"; }
                        LeftRotate(z->parent);
                        z = root;
                    }
                }
            }
            else {
                if (z->parent->right == z) {
                    if (z->parent->left) { sibling = z->parent->left; }
                    if (sibling) {
                        //CASE -- 1
                        if (sibling->color == "RED") {
                            sibling->color = "BLACK";
                            z->parent->color = "RED";
                            RightRotate(z->parent);
                            sibling = z->parent->left;
                        }
                        //CASE -- 2
                        if (sibling->left == nullptr && sibling->right == nullptr) {
                            sibling->color = "RED";
                            z = z->parent;
                        }
                        else if (sibling->left->color == "BLACK" && sibling->right->color == "BLACK") {
                            sibling->color = "RED";
                            z = z->parent;
                        }
                        //CASE -- 3 
                        else if (sibling->left->color == "BLACK") {
                            sibling->right->color = "BLACK";
                            sibling->color = "RED";
                            RightRotate(sibling);
                            sibling = z->parent->left;
                        }
                        else {
                            sibling->color = z->parent->color;
                            z->parent->color = "BLACK";
                            if (sibling->left) { sibling->left->color = "BLACK"; }
                            LeftRotate(z->parent);
                            z = root;
                        }
                    }
                }

            }
        }
        z->color = "BLACK";
    }

    RBNodepoint RBTree::TreeSearch(int stuff) {
        auto temp = root;
        if (temp == nullptr) { return nullptr; }

        while (temp) {
            if (stuff == temp->data) { return temp; }
            else if (stuff < temp->data) { temp = temp->left; }
            else { temp = temp->right; }
        }
        return nullptr;
    }

    RBNodepoint RBTree::LeftRotate(RBNodepoint x) {
        RBNodepoint nw_node = new RBNode();
        nw_node = new RBNode();
        if (x->right->left) { nw_node->right = x->right->left; }
        nw_node->left = x->left;
        nw_node->data = x->data;
        nw_node->color = x->color;
        x->data = x->right->data;

        x->left = nw_node;
        if (nw_node->left) { nw_node->left->parent = nw_node; }
        if (nw_node->right) { nw_node->right->parent = nw_node; }
        nw_node->parent = x;

        if (x->right->right) { x->right = x->right->right; }
        else { x->right = nullptr; }

        if (x->right) { x->right->parent = x; }

        return x;
    }

    RBNodepoint RBTree::RightRotate(RBNodepoint x) {
        RBNodepoint nw_node = new RBNode();
        if (x->left->right) { nw_node->left = x->left->right; }
        nw_node->right = x->right;
        nw_node->data = x->data;
        nw_node->color = x->color;

        x->data = x->left->data;
        x->color = x->left->color;

        x->right = nw_node;
        if (nw_node->left) { nw_node->left->parent = nw_node; }
        if (nw_node->right) { nw_node->right->parent = nw_node; }
        nw_node->parent = x;

        if (x->left->left) { x->left = x->left->left; }
        else { x->left = nullptr; }

        if (x->left) { x->left->parent = x; }

        return x;
    }

    void RBTree::PreorderTraversal(RBNodepoint temp) {
        if (!temp) { return; }        
        cout << "--> " << temp->data << "<" << temp->color << ">";
        PreorderTraversal(temp->left);
        PreorderTraversal(temp->right);
    }

    void RBTree::PostorderTraversal(RBNodepoint temp) {
        if (!temp) { return; }        
        PostorderTraversal(temp->left);
        PostorderTraversal(temp->right);
        cout << "--> " << temp->data << "<" << temp->color << ">";
    }

    void RBTree::PrePrint() { 
        PreorderTraversal(this ->root);        
    }

    void RBTree::PostPrint() {        
        PostorderTraversal(this->root);        
    }
       