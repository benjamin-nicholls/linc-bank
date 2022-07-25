#pragma once
#include <cmath>
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
    static void PrintTreeInOrder(TreeNode* p_Node);
private:
    static TreeNode* InsertTransaction(TreeNode* &p_Node, Transaction* p_Transaction);
    static TreeNode* InsertNode(TreeNode* &p_Node, TreeNode* p_NewNode);
    static TreeNode* Rebalance(TreeNode* &p_Node);
    static TreeNode* FixImbalance(TreeNode* &p_Node);
    static TreeNode* RotateRight(TreeNode* &p_Node);
    static TreeNode* RotateLeft(TreeNode* &p_Node);
    static int Height(TreeNode* &_p_Node);
    static void ListNodesInOrder(TreeNode* &p_Node, std::vector<TreeNode*> *nodeList);
    static void RebalanceInsert(TreeNode* &p_Node, std::vector<TreeNode*> *nodeList);
    
};
