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
    if (*p_Node == Key) { return p_Node; }  // Need to check for ALL instances of this value.
    if (*p_Node > Key) { return Search(p_Node->m_p_Left, Key); }
    //if (*p_Node < Key) {
    return Search(p_Node->m_p_Right, Key);
}


TreeNode* BST::Insert(TreeNode* &p_Node, Transaction* p_Transaction) {
    if (p_Node == nullptr) { p_Node = new TreeNode(p_Transaction); return p_Node; }
    if (*p_Node == *p_Transaction) { p_Node->m_TransactionOverflow.push_back(p_Transaction); }
    if (*p_Node > *p_Transaction) { BST::Insert(p_Node->m_p_Left, p_Transaction); }
    if (*p_Node < *p_Transaction) { BST::Insert(p_Node->m_p_Right, p_Transaction); }
    return p_Node;
}


// Not used functionally within the bank program.
/*
void BST::PrintTreeInOrder(TreeNode* p_Node) {
    if (p_Node == nullptr) { return; }
    PrintTreeInOrder(p_Node->m_p_Left);
    std::cout << p_Node->m_p_Transaction->toString();  // No endl needed.
    PrintTreeInOrder(p_Node->m_p_Right);
}
*/
