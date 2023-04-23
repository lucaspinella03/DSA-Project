#pragma once

#include <iostream>
#include <ostream>
#include "stock.h"

// Defines MAX
// When used, MAX(a,b) will be replaced with ((a > b) ? a : b)
#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

// Underlying class which will be used to implement the BSTree class.
// I.E. BSTree is made up of BSTNode
class LLRBTNode
{
private:
    Stock data;
    LLRBTNode* left;
    LLRBTNode* right;
    bool red;

public:
    explicit LLRBTNode(Stock data);
    ~LLRBTNode();

    Stock* getData();
    LLRBTNode* getLeft();
    LLRBTNode* getRight();

    friend class LLRBTree;
    friend class Stock;
};

// Public versions: accept a single parameter so the usage of the class is neat.
// Private version: implement the functions recursively
class LLRBTree
{
private:
    LLRBTNode* _root;

    LLRBTNode* insert(Stock data, LLRBTNode* root);
    LLRBTNode* remove(Stock data, LLRBTNode* root);
    LLRBTNode* find_ios(LLRBTNode* root, bool& disconnect);
    int height(LLRBTNode* root);

    void floopColors(LLRBTNode* root);
    LLRBTNode* rotateLeft(LLRBTNode* root);
    LLRBTNode* rotateRight(LLRBTNode* root);

    void preorder(LLRBTNode* root, std::ostream& os);
    void inorder(LLRBTNode* root, std::ostream& os);
    void postorder(LLRBTNode* root, std::ostream& os);

    void destroy(LLRBTNode* root);
    Stock* search(std::string data, LLRBTNode* root);

public:
    LLRBTree();
    ~LLRBTree();

    void insert(Stock data);
    void remove(Stock data);
    int height();

    LLRBTNode* getRoot();

    void preorder(std::ostream& os = std::cout);
    void inorder(std::ostream& os = std::cout);
    void postorder(std::ostream& os = std::cout);

    Stock* search(std::string data);


};