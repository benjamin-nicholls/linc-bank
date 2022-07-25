#include "bst.h"
#include <cmath>
#include <iostream>  // remove


TreeNode::TreeNode() {
    m_p_Transaction = nullptr;
    m_p_Left = nullptr;
    m_p_Right = nullptr;
}


TreeNode::TreeNode(Transaction* p_Transaction) {
    m_p_Transaction = p_Transaction;
    m_p_Left = nullptr;
    m_p_Right = nullptr;
}


TreeNode::~TreeNode() {
    delete m_p_Left;
    delete m_p_Right;
    for (auto transaction : m_TransactionOverflow) { delete transaction; }
    delete m_p_Transaction;
}


std::string TreeNode::toString() const {
	return m_p_Transaction->toString();
}


bool TreeNode::operator <(TreeNode const &obj) {
    if (*m_p_Transaction < *obj.m_p_Transaction) { return true; }
    return false;
}
bool TreeNode::operator >(TreeNode const &obj) {
    if (*m_p_Transaction > *obj.m_p_Transaction) { return true; }
    return false;
}
bool TreeNode::operator ==(TreeNode const &obj) {
    if (*m_p_Transaction == *obj.m_p_Transaction) { return true; }
    return false;
}
bool TreeNode::operator <(Transaction const &obj) {
    if (*m_p_Transaction < obj) { return true; }
    return false;
}
bool TreeNode::operator >(Transaction const &obj) {
    if (*m_p_Transaction > obj) { return true; }
    return false;
}
bool TreeNode::operator ==(Transaction const &obj) {
    if (*m_p_Transaction == obj) { return true; }
    return false;
}
bool TreeNode::operator <(double const Key) {
    if (*m_p_Transaction < Key) { return true; }
    return false;
}
bool TreeNode::operator >(double const Key) {
    if (*m_p_Transaction > Key) { return true; }
    return false;
}
bool TreeNode::operator ==(double const Key) {
    if (*m_p_Transaction == Key) { return true; }
    return false;
}


// BST

TreeNode* BST::Search(TreeNode* &p_Node, double Key) {
    if (p_Node == nullptr) { return nullptr; }
    if (*p_Node == Key) { return p_Node; }  // Need to check for ALL instances of this value.
    if (*p_Node > Key) { return Search(p_Node->m_p_Left, Key); }
    //if (*p_Node < Key) {
    return Search(p_Node->m_p_Right, Key);
}


TreeNode* BST::Insert(TreeNode* &p_Node, Transaction* p_Transaction) {
    BST::InsertTransaction(p_Node, p_Transaction);
    int heightDifference = abs(BST::Height(p_Node->m_p_Left) - BST::Height(p_Node->m_p_Right));
    std::cout << "insert" << "\n";
    BST::FixImbalance(p_Node);
    //if (heightDifference > 3) { p_Node = BST::Rebalance(p_Node); }
    return p_Node;
}

TreeNode* BST::InsertTransaction(TreeNode* &p_Node, Transaction* p_Transaction) {
    if (p_Node == nullptr) { p_Node = new TreeNode(p_Transaction); return p_Node; }
    if (*p_Node == *p_Transaction) { p_Node->m_TransactionOverflow.push_back(p_Transaction); }
    if (*p_Node > *p_Transaction) { BST::InsertTransaction(p_Node->m_p_Left, p_Transaction); }
    if (*p_Node < *p_Transaction) { BST::InsertTransaction(p_Node->m_p_Right, p_Transaction); }
    return p_Node;
}


TreeNode* BST::InsertNode(TreeNode* &p_Node, TreeNode* p_NewNode) {
    // Adding a whole node during insert is only used during rebalancing.
    // No need to check for == as this will never occur.
    if (p_Node == nullptr) { p_Node = p_NewNode; return p_Node; }
    if (*p_Node > *p_NewNode) { BST::InsertNode(p_Node->m_p_Left, p_NewNode); }
    if (*p_Node < *p_NewNode) { BST::InsertNode(p_Node->m_p_Right, p_NewNode); }
    return p_Node;
}


int BST::Height(TreeNode* &p_Node) {
    // If you use root node, you get maximum height of the tree.
    // If you use left or right of root node, you can check for an imbalance.
    if (p_Node == nullptr) { return 0; }
    int leftHeight = BST::Height(p_Node->m_p_Left);
    int rightHeight = BST::Height(p_Node->m_p_Right);
    if (leftHeight > rightHeight) { return leftHeight + 1; };
    return rightHeight + 1;
}


TreeNode* BST::FixImbalance(TreeNode* &p_Node) {
    if (p_Node == nullptr) { return p_Node; }
    int leftHeight = BST::Height(p_Node->m_p_Left);
    int rightHeight = BST::Height(p_Node->m_p_Right);
    std::cout << "root is: " << p_Node->toString() << "\n";
    std::cout << "height: " << BST::Height(p_Node) << "\n";
    std::cout << "height L: " << BST::Height(p_Node->m_p_Left) << "\n";
    std::cout << "height R: " << BST::Height(p_Node->m_p_Right) << "\n";

    // If imbalance, fix.
    if (abs(leftHeight - rightHeight) > 1) {
        if (leftHeight > rightHeight) {
            std::cout << "ROTATING RIGHT" << "\n";
            p_Node = BST::RotateRight(p_Node);
        } else {
            std::cout << "ROTATING LEFT" << "\n";
            p_Node = BST::RotateLeft(p_Node);

        }
    } else {
        std::cout << "NO ROTATION" << "\n";
    }
    std::cout << "height: " << BST::Height(p_Node) << "\n";
    std::cout << "height L: " << BST::Height(p_Node->m_p_Left) << "\n";
    std::cout << "height R: " << BST::Height(p_Node->m_p_Right) << "\n";

    FixImbalance(p_Node->m_p_Left);
    FixImbalance(p_Node->m_p_Right);
    return p_Node;
}


TreeNode* BST::RotateRight(TreeNode* &p_Node) {
    TreeNode* p_A = p_Node;
    TreeNode* p_B = p_Node->m_p_Left;
    p_A->m_p_Left = p_B->m_p_Right;
    p_B->m_p_Right = p_A;
    return p_B;
}


TreeNode* BST::RotateLeft(TreeNode* &p_Node) {
    TreeNode* p_A = p_Node;
    TreeNode* p_B = p_Node->m_p_Right;
    p_A->m_p_Right = p_B->m_p_Left;
    p_B->m_p_Left = p_A;
    return p_B;
}





TreeNode* BST::Rebalance(TreeNode* &p_Node) {
    std::vector<TreeNode*> *nodeList = new std::vector<TreeNode*>;
    BST::ListNodesInOrder(p_Node, nodeList);
    int size = nodeList->size();
    auto mid = nodeList->begin() + size / 2;
    TreeNode* newRoot;
    BST::RebalanceInsert(newRoot, nodeList);
    nodeList->clear();
    return newRoot;
}


void BST::RebalanceInsert(TreeNode* &p_Node, std::vector<TreeNode*> *nodeList) {
    auto mid = nodeList->begin() + nodeList->size() / 2;
    // Find specific index, not memory address.
    int midIndex = 0;
    for (int i = 0; i < nodeList->size(); i++) {
        if (nodeList->at(i) == *mid) {
            midIndex = i;
            break;
        }
    }
    BST::InsertNode(p_Node, *mid);
    TreeNode* temp = *mid;
    if (nodeList->size() == 1) { return; }
    std::vector<TreeNode*> *leftNodes = new std::vector<TreeNode*>;
    for (auto it = 0; it != midIndex; it++) { leftNodes->push_back(nodeList->at(it)); }
    if (!leftNodes->empty()) { RebalanceInsert(p_Node, leftNodes); }
    std::vector<TreeNode*> *rightNodes = new std::vector<TreeNode*>;
    for (auto it = midIndex; it != nodeList->size(); it++) { rightNodes->push_back(nodeList->at(it)); }
    if (!rightNodes->empty()) { RebalanceInsert(p_Node, rightNodes); }
    leftNodes->clear();
    rightNodes->clear();
    return;
}

void BST::ListNodesInOrder(TreeNode* &p_Node, std::vector<TreeNode*> *nodeList) {
    // nodeList pointer is used to update vector.
    if (p_Node->m_p_Left == nullptr) {
        nodeList->push_back(p_Node);
    } else {
        ListNodesInOrder(p_Node->m_p_Left, nodeList);
        nodeList->push_back(p_Node);
    }
    if (p_Node->m_p_Right == nullptr) { return; }
    ListNodesInOrder(p_Node->m_p_Right, nodeList);
    return;
}


// Not used functionally within the bank program.
void BST::PrintTreeInOrder(TreeNode* p_Node) {
    if (p_Node == nullptr) { return; }
    PrintTreeInOrder(p_Node->m_p_Left);
    std::cout << p_Node->m_p_Transaction->toString();  // No endl needed.
    PrintTreeInOrder(p_Node->m_p_Right);
}

