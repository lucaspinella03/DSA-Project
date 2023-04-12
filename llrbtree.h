#include <iostream>
#ifndef LAB09_LLRBTREE_H
#define LAB09_LLRBTREE_H
class StockNode{
private:
    //remember that every node can be thought of as its own subtree

    StockNode(std::string ticker, int stock_price, int volatility, bool is_red);

//integer inside the node
    std::string ticker;

    int stock_price;

    int volatility;
    //pointer to left child
    StockNode* left_node;
    //to right child
    StockNode* right_node;

    bool is_red;
    //connects this class to the BSTree

public:
    StockNode(std::string ticker, double stock_price, double volatility, bool is_red);
    ~StockNode();

    friend class LLRBTree;
};

class LLRBTree{
private:
    StockNode* root_node;

    //insert
    //StockNode* current, std::string new_ticker, int new_stock_price, int new_volatility, bool is_red
    StockNode* insert(StockNode* current, std::string new_ticker, double new_stock_price, double new_volatility, bool is_red);
    //for destructor
    void clear(StockNode* current);
    void flipColors(StockNode* current);
    StockNode* rotateLeft(StockNode* current);
    StockNode* rotateRight(StockNode* current);
    //for height function
    int height(StockNode* current);

    //LLRBTNode* remove( LLRBTNode* root, int node_data);
    //traversal recursion
    void preorder(StockNode* root, std::ostream& os);
    void inorder(StockNode* root, std::ostream& os);
    void postorder(StockNode* root, std::ostream& os);

    bool search(std::string ticker, StockNode* root_node);

public:
    //constructor
    LLRBTree();
    //destructor
    ~LLRBTree();
    //functions

    //insert
    void insert(std::string ticker, double stock_price, double volatility);
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
