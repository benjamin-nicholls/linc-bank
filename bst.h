#pragma once
#include <string>
#include <vector>
#include "transaction.h"

struct TreeNode {
public:
    TreeNode();
	TreeNode(Transaction* p_Transaction);
	~TreeNode();
	std::string toString() const;
    Transaction* m_p_Transaction;
    std::vector <Transaction*> m_TransactionOverflow; 
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
private:
    static TreeNode* insertTransaction(TreeNode* &p_Node, Transaction* p_Transaction);
    static TreeNode* rebalance(TreeNode* &p_Node);
    static TreeNode* rotateRight(TreeNode* &p_Node);
    static TreeNode* rotateLeft(TreeNode* &p_Node);
    static int height(TreeNode* &_p_Node);
    
};
