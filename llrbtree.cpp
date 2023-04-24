#include "llrbtree.h"

#include <utility>

/*
 * Node Class Functions
*/

LLRBTNode::LLRBTNode(Stock data){
    this->data = std::move(data);
    this->left = nullptr;
    this->right = nullptr;
    this->red = false;
}

Stock *LLRBTNode::getData() {
    return &this->data;
}

LLRBTNode *LLRBTNode::getLeft() {
    return this->left;
}

LLRBTNode *LLRBTNode::getRight() {
    return this->right;
}

LLRBTNode::~LLRBTNode() = default;

/*
 * Tree Class Functions
*/

/*
 * Private Functions
*/

LLRBTNode* LLRBTree::insert(Stock data, LLRBTNode* root){
    if(!root){
        auto* tempNode = new LLRBTNode(data);
        tempNode->red = true;
        return tempNode;
    }

    // Go left if data < data at this Node
    if(data.getTicker() < root->data.getTicker()){
        root->left = insert(data, root->left);
        // Go right otherwise
    }else{
        root->right = insert(data, root->right);
    }

    if (root->right != nullptr) {
        if (root->right->red && root->left == nullptr || root->right->red && !root->left->red)
            root = rotateLeft(root);
    }
    if (root->left != nullptr) {
        if (root->left->left != nullptr) {
            if (root->left->left->red && root->left->red) {
                root = rotateRight(root);
            }
        }
    }
    floopColors(root);


    return root;
}

LLRBTNode* LLRBTree::remove(Stock data, LLRBTNode* root){
    if(!root){
        return nullptr;
    }

    // We found what we're looking for, delete it.
    if(data.getTicker() == root->data.getTicker() ){
        LLRBTNode* temp;
        // This is a leaf node
        if(root->left == root->right){
            delete root;
            return nullptr;
        }

        // This node has 1 child
        if(!root->left != !root->right){
            // Set temp to whichever child exists
            root->left ? temp = root->left : temp = root->right;

            delete root;
            return temp;
        }

        // This node has 2 children
        // Find the in-order successor
        temp = root->right;

        while(temp->left){
            temp = temp->left;
        }

        // Copy the data to this node and delete the original
        root->data = temp->data;
        root->right = remove(temp->data, root->right);
        return root;
    }

    // This is not the Node we're looking for, recursively find the data we want to delete
    if(data.getTicker() < root->data.getTicker() ){
        root->left = remove(data, root->left);
    }else{
        root->right = remove(data, root->right);
    }

    return root;
}

LLRBTNode* LLRBTree::find_ios(LLRBTNode* root, bool& disconnect){
    if(!root->left){
        disconnect = true;
        return root;
    }
    LLRBTNode* temp = find_ios(root->left, disconnect);

    if(disconnect){
        root->left = nullptr;
        disconnect = false;
    }

    return temp;
}

int LLRBTree::height(LLRBTNode* root){
    if(!root){
        return -1;
    }
    int left = height(root->left);
    int right = height(root->right);

    return (left > right ? left + 1 : right + 1);
}

void LLRBTree::preorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    os << root->data.getTicker()  << ":" << root->red << " ";
    this->preorder(root->left, os);
    this->preorder(root->right, os);

    return;
}

void LLRBTree::inorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->inorder(root->left, os);
    os << root->data.getTicker()  << ":" << root->red << " ";
    this->inorder(root->right, os);

    return;
}

void LLRBTree::postorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    os << root->data.getTicker()  << ":" << root->red << " ";

    return;
}

void LLRBTree::destroy(LLRBTNode* root){
    if(!root){
        return;
    }

    this->destroy(root->left);
    this->destroy(root->right);
    delete root->left;
    delete root->right;
}

Stock* LLRBTree::search(std::string data, LLRBTNode* root){
    if(!root){
        return nullptr;
    }

    if(data == root->data.getTicker() ){
        return &root->data;
    }

    if(data < root->data.getTicker() ){
        return this->search(data, root->left);
    }else{
        return this->search(data, root->right);
    }
}

/*
 * Public Functions
*/

LLRBTree::LLRBTree(){
    this->_root = nullptr;
}

LLRBTree::~LLRBTree(){
    delete this->_root;
}

void LLRBTree::insert(Stock data){
    this->_root = this->insert(data, this->_root);
    if(this->_root->red){
        this->_root->red = false;
    }
}

void LLRBTree::remove(Stock data){
    this->_root = this->remove(data, this->_root);
}

int LLRBTree::height(){
    return this->height(this->_root);
}

void LLRBTree::preorder(std::ostream& os){
    this->preorder(this->_root, os);
    os << "\n";
}

void LLRBTree::inorder(std::ostream& os){
    this->inorder(this->_root, os);
    os << "\n";
}

void LLRBTree::postorder(std::ostream& os){
    this->postorder(this->_root, os);
    os << "\n";
}

Stock* LLRBTree::search(std::string data){
    return this->search(data, this->_root);
}

void LLRBTree::floopColors(LLRBTNode *root) {
    if(!root->red && root->left != nullptr && root->right != nullptr){
        if(root->left->red && root->right->red){
            root->red = true;
            root->left->red = false;
            root->right->red = false;
        }
    }
}

LLRBTNode* LLRBTree::rotateLeft(LLRBTNode* root){
    LLRBTNode* p = root->right;
    root->right = root->right->left;
    p->left = root;
    p->red = root->red;
    root->red = true;
    return p;
}

LLRBTNode *LLRBTree::rotateRight(LLRBTNode *root) {
    LLRBTNode* p = root->left;
    root->left = root->left->right;
    p->right = root;
    p->red = root->red;
    root->red = true;
    return p;
}

LLRBTNode *LLRBTree::getRoot() {
    return this->_root;
}
