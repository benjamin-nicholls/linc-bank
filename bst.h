#pragma once
#include <cmath>
#include <string>
#include "transaction.h"


struct TreeNode {
public:
    TreeNode();
	TreeNode(Transaction* p_Transaction);
	~TreeNode() {};
	std::string toString() const;
    Transaction* m_p_Transaction;
    TreeNode *m_p_Left;
    TreeNode *m_p_Right;
    
    bool operator <(TreeNode const &obj);
    bool operator >(TreeNode const &obj);
    bool operator ==(TreeNode const &obj);
    bool operator <(Transaction const &obj);
    bool operator >(Transaction const &obj);
    bool operator ==(Transaction const &obj);
    bool operator <(double const Key);
    bool operator >(double const Key);
    bool operator ==(double const Key);
};


class BST {
public:
    static TreeNode* Search(TreeNode* &p_Node, double Key);
    static TreeNode* Insert(TreeNode* &p_Node, Transaction* p_Transaction);
    static void PrintTreeInOrder(TreeNode* p_Node);
};
