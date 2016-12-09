/*
 * red_black_tree.hpp
 *
 *  Created on: 9 апр. 2013 г.
 *      Author: Dexiz
 */

#ifndef BINARY_TREE_HPP_
#define BINARY_TREE_HPP_

class TreeNode
{
protected:
	int value;
	TreeNode* parent;
	TreeNode* left;
	TreeNode* right;

public:
	void SetParent(TreeNode* p);
	void SetRight(TreeNode* r);
	void SetLeft(TreeNode* l);
	void SetValue(int v);

	TreeNode* GetParent();
	TreeNode* GetRight();
	TreeNode* GetLeft();
	int GetValue();
};

class Tree
{
	TreeNode* root;
	bool EmptyTree;

public:
	Tree();
	Tree(const Tree &newTree);
	Tree& operator=(const Tree& newTree);
	Tree& operator+(const Tree& newTree) const;
	Tree& operator-(const Tree& newTree) const;

	bool IsTreeEmpty();
	void Add(int value);
	TreeNode* FindParent(TreeNode* SubTree, int value);
	TreeNode* SearchMin(TreeNode* SubTree);
	TreeNode* SearchMax(TreeNode* SubTree);
	void Delete(int value);
	void DeleteSubTree(TreeNode* SubTree);
	void DeleteTree();
	void ShowFromMinToMax(TreeNode* SubTree);
	TreeNode* GetRoot();
	TreeNode* CopyChildren(TreeNode** ParentFromTree, TreeNode* NodeToCopy);
	void AddAllElementsFromOtherTree(Tree* tree, TreeNode* node);
	void DeleteAllElementsFromOtherTree(Tree* tree, TreeNode* minuend, Tree* deduction);
	bool DoesNotExist(int v);
};



#endif /* BINARY_TREE_HPP_ */
