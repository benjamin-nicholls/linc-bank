#include "bst.h"


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
    if (*p_Node == Key) { return p_Node; }
    if (*p_Node > Key) { return Search(p_Node->m_p_Left, Key); }
    return Search(p_Node->m_p_Right, Key);
}


TreeNode* BST::Insert(TreeNode* &p_Node, Transaction* p_Transaction) {
    BST::insertTransaction(p_Node, p_Transaction);
    BST::rebalance(p_Node);
    return p_Node;
}


TreeNode* BST::insertTransaction(TreeNode* &p_Node, Transaction* p_Transaction) {
    if (p_Node == nullptr) { p_Node = new TreeNode(p_Transaction); return p_Node; }
    if (*p_Node == *p_Transaction) { p_Node->m_TransactionOverflow.push_back(p_Transaction); }
    if (*p_Node > *p_Transaction) { BST::insertTransaction(p_Node->m_p_Left, p_Transaction); }
    if (*p_Node < *p_Transaction) { BST::insertTransaction(p_Node->m_p_Right, p_Transaction); }
    return p_Node;
}


int BST::height(TreeNode* &p_Node) {
    if (p_Node == nullptr) { return 0; }
    int leftHeight = BST::height(p_Node->m_p_Left);
    int rightHeight = BST::height(p_Node->m_p_Right);
    if (leftHeight > rightHeight) { return leftHeight + 1; };
    return rightHeight + 1;
}


TreeNode* BST::rebalance(TreeNode* &p_Node) {
    if (p_Node == nullptr) { return p_Node; }
    int leftHeight = BST::height(p_Node->m_p_Left);
    int rightHeight = BST::height(p_Node->m_p_Right);
    if (leftHeight - rightHeight > 1) { 
        p_Node = BST::rotateRight(p_Node);
    } else if (leftHeight - rightHeight < -1) {
        p_Node = BST::rotateLeft(p_Node);
    }
    BST::rebalance(p_Node->m_p_Left);
    BST::rebalance(p_Node->m_p_Right);
    return p_Node;
}


TreeNode* BST::rotateRight(TreeNode* &p_Node) {
    TreeNode* p_A = p_Node;
    TreeNode* p_B = p_Node->m_p_Left;
    p_A->m_p_Left = p_B->m_p_Right;
    p_B->m_p_Right = p_A;
    return p_B;
}


TreeNode* BST::rotateLeft(TreeNode* &p_Node) {
    TreeNode* p_A = p_Node;
    TreeNode* p_B = p_Node->m_p_Right;
    p_A->m_p_Right = p_B->m_p_Left;
    p_B->m_p_Left = p_A;
    return p_B;
}
