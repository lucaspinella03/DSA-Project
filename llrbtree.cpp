
#include "llrbtree.h"
//constructors

//node constructor

LLRBTNode::LLRBTNode(int node_data, bool is_red){
    this->node_data = node_data;
    this->left_node = nullptr;
    this->right_node = nullptr;
    this->is_red = is_red;
}
//node destructor
LLRBTNode::~LLRBTNode() {
    //before the node deletes we delete the right and left nodes
}
//bst constructors
LLRBTree::LLRBTree(){
    this->root_node = nullptr;
}
//destructor
LLRBTree::~LLRBTree() {
    clear(this->root_node);
}

//functions---------------------------------------

//recursive insert function
LLRBTNode* LLRBTree::insert(LLRBTNode* current, int num, bool is_red){
    //todo add condition handling for left rotate, right rotate and color flip
    if(current == nullptr){
        return new LLRBTNode(num, is_red);
    }
    else if (num < current->node_data){
        current->left_node = insert(current->left_node, num, is_red);
    }
    else {
        current->right_node = insert(current->right_node, num, is_red);
    }

    //If a node has a BLACK LEFT child and a RED RIGHT child, left-rotate the Node & swap colors
    if (current->right_node != nullptr && current->right_node->is_red == 1){
        if (current->left_node == nullptr || current->left_node->is_red == 0){
            current = rotateLeft(current);
        }
    }
    //if you need to right rotate
    if (current->left_node != nullptr && current->left_node->left_node != nullptr){
        if (current->left_node->is_red == 1 && current->left_node->left_node->is_red == 1){
            current = rotateRight(current);
        }
    }
    //if you need to color flip
    if (current->is_red == 0 && current->right_node != nullptr && current->left_node != nullptr){
        if (current->left_node->is_red == 1 && current->right_node->is_red == 1){
            flipColors(current);
        }
    }
    return current;
}

//public insert function
void LLRBTree::insert(int num){

    this->root_node = this->insert(this->root_node, num, 1);
    this->root_node->is_red = 0;
}

//recursive destroy function
void LLRBTree::clear(LLRBTNode* current){
    if (current != nullptr) {
        clear(current->left_node);
        clear(current->right_node);
        delete current;
    }
}

LLRBTNode* LLRBTree::rotateLeft(LLRBTNode* current){
    //make current new root, and black
    //make right red and make it the new current
    LLRBTNode* temp = current->right_node;
    current->right_node = current->right_node->left_node;
    temp->left_node = current;
    temp->is_red = current->is_red;
    current->is_red = 1;
    return temp;
}

LLRBTNode* LLRBTree::rotateRight(LLRBTNode *current) {
    LLRBTNode* temp = current->left_node;
    current->left_node = current->left_node->right_node;
    temp->right_node = current;
    temp->is_red = current->is_red;
    current->is_red = 1;
    return temp;
}
//recursively changes colors
void LLRBTree::flipColors(LLRBTNode *current) {
    current->is_red = 1;
    current->left_node->is_red = 0;
    current->right_node->is_red = 0;
}

//private traversal functions

void LLRBTree::preorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    os << root->node_data << ":" << root->is_red << " ";
    this->preorder(root->left_node, os);
    this->preorder(root->right_node, os);

    return;
}

void LLRBTree::inorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->inorder(root->left_node, os);
    os << root->node_data << ":" << root->is_red << " ";
    this->inorder(root->right_node, os);

    return;
}

void LLRBTree::postorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->postorder(root->left_node, os);
    this->postorder(root->right_node, os);
    os << root->node_data << ":" << root->is_red << " ";

    return;
}

//public traversal functions
void LLRBTree::preorder(std::ostream& os){
    this->preorder(this->root_node, os);
    os << "\n";
}

void LLRBTree::inorder(std::ostream& os){
    this->inorder(this->root_node, os);
    os << "\n";
}

void LLRBTree::postorder(std::ostream& os){
    this->postorder(this->root_node, os);
    os << "\n";
}

//height function
int LLRBTree::height(LLRBTNode* current){
    if(!current){
        return -1;
    }
    int left = height(current->left_node);
    int right = height(current->right_node);

    return (left > right ? left + 1 : right + 1);
}

int LLRBTree::height() {
    return height(this->root_node);
}
