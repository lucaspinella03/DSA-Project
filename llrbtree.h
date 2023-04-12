#include <iostream>
#ifndef LAB09_LLRBTREE_H
#define LAB09_LLRBTREE_H
class LLRBTNode{
private:
    //remember that every node can be thought of as its own subtree

    //integer inside the node
    int node_data;
    //pointer to left child
    LLRBTNode* left_node;
    //to right child
    LLRBTNode* right_node;

    bool is_red;
    //connects this class to the BSTree

public:
    LLRBTNode(int node_data, bool is_red);
    ~LLRBTNode();

    friend class LLRBTree;
};

class LLRBTree{
private:
    LLRBTNode* root_node;

    //insert
    LLRBTNode* insert(LLRBTNode* current, int node_data, bool is_red);
    //for destructor
    void clear(LLRBTNode* current);
    void flipColors(LLRBTNode* current);
    LLRBTNode* rotateLeft(LLRBTNode* current);
    LLRBTNode* rotateRight(LLRBTNode* current);
    //for height function
    int height(LLRBTNode* current);

    //LLRBTNode* remove( LLRBTNode* root, int node_data);
    //traversal recursion
    void preorder(LLRBTNode* root, std::ostream& os);
    void inorder(LLRBTNode* root, std::ostream& os);
    void postorder(LLRBTNode* root, std::ostream& os);

    bool search(int data, LLRBTNode* root_node);

public:
    //constructor
    LLRBTree();
    //destructor
    ~LLRBTree();
    //functions

    //insert
    void insert(int node_data);
    //remove
    //void remove(int node_data);
    //height
    int height();

    //traversals
    void preorder(std::ostream& os = std::cout);
    void inorder(std::ostream& os = std::cout);
    void postorder(std::ostream& os = std::cout);

    bool search(int node_data);

};

#endif //LAB09_LLRBTREE_H
