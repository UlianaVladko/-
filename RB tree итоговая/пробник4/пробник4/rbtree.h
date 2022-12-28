#pragma once

#include "rbnode.h"
#include "tree.h"

typedef RBNode* RBNodepoint;

class RBTree : public Tree< RBNode> {
private:

	RBNodepoint root;       
        
    void RB_Insert_Fixup(RBNodepoint z);

    void RemoveNode(RBNodepoint parent, RBNodepoint curr, int stuff) override;

    void RB_Delete_Fixup(RBNodepoint x);
                  
    RBNodepoint LeftRotate(RBNodepoint x) override;
        
    RBNodepoint RightRotate(RBNodepoint x)override;    
        
    public:               

        void InsertNode(int stuff) override;

        void Remove(int stuff);

        RBNodepoint TreeSearch(int stuff);

        void PrePrint();

        void PostPrint();

        void PreorderTraversal(RBNodepoint temp);        

        void PostorderTraversal(RBNodepoint temp);
        
};