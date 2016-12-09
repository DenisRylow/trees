/*
 * red_black_tree.cpp
 *
 *  Created on: 9 апр. 2013 г.
 *      Author: Dexiz
 */
#include "binary_tree.hpp"

#include<iostream>

using namespace std;

void TreeNode::SetParent(TreeNode* p)
{
	parent = p;
};

void TreeNode::SetLeft(TreeNode* l)
{
	left = l;
};

void TreeNode::SetRight(TreeNode* r)
{
	right = r;
};

void  TreeNode::SetValue(int v)
{
	value = v;
};

int  TreeNode::GetValue()
{
	return value;
};

TreeNode* TreeNode::GetParent()
{
	return parent;
};

TreeNode* TreeNode::GetLeft()
{
	return left;
};

TreeNode* TreeNode::GetRight()
{
	return right;
};

Tree::Tree()
{
	EmptyTree = true;

	root = new TreeNode;
	root->SetRight(NULL);
	root->SetParent(NULL);
	root->SetLeft(NULL);
	root->SetValue(NULL);

};

bool Tree::IsTreeEmpty()
{
	return EmptyTree;
};

TreeNode* Tree::SearchMin(TreeNode* SubTree)
{
	// Method takes the left child and checks if it has one, if no then the current node is minimal, otherwise repeats the action with the left child
	while (SubTree->GetLeft() != NULL)
	{
		SubTree = SubTree->GetLeft();
	};

	return SubTree;
};

TreeNode* Tree::SearchMax(TreeNode* SubTree)
{
	// Almost the same as SearchMin, but works with right children
	while (SubTree->GetLeft() != NULL)
	{
		SubTree = SubTree->GetRight();
	};

	return SubTree;
};


TreeNode* Tree::FindParent(TreeNode* SubTree, int value)
{

	//Searches for parent, if the value already exists - returns that node (the one with collision I mean)
	if (value > SubTree->GetValue())
	{
		if (SubTree->GetRight() != NULL)
		{
			return FindParent(SubTree->GetRight(), value);
		}
		else
		{
			return SubTree;
		}
	}
	else
	{
		if ((SubTree->GetValue() > value) & (SubTree->GetLeft() != NULL))
		{
			return FindParent(SubTree->GetLeft(), value);
		}
		else
		{
			return SubTree;
		};
	};

};

void Tree::Add(int value)
{
	if (IsTreeEmpty())
	{
		//Adds root
		root->SetValue(value);
		EmptyTree = false;
	}
	else
	{
		TreeNode* parent = FindParent(root,value);

		if (value != parent->GetValue())
		{
			TreeNode* temp = new TreeNode;
			temp->SetParent(parent);
			temp->SetLeft(NULL);
			temp->SetRight(NULL);
			temp->SetValue(value);

			//Adds link to the child to the parent
			if (temp->GetParent()->GetValue() < value )
			{
				temp->GetParent()->SetRight(temp);
			}
			else
			{
				temp->GetParent()->SetLeft(temp);
			};
		};
	};

};

void Tree::Delete(int value)
{
	TreeNode* temp;
	temp = root;

	//Searches for node that is to be deleted using value(key)
	while ((temp->GetValue() != value) & ( (temp->GetRight() != NULL) || (temp->GetLeft() != NULL) ))
	{
		if (temp->GetValue() < value)
		{
			temp = temp->GetRight();
		}
		else
		{
			temp = temp->GetLeft();
		};

	};

	//deletion
	if ((temp != NULL) & (temp != root))
	{
		if ((temp->GetRight() != NULL ) & (temp->GetLeft() != NULL))
		{
			//If there are 2 children
			TreeNode* successor;
			successor = SearchMin(temp->GetRight());

			//Saving succesor's value
			int c;
			c = successor->GetValue();


			//Deletes parent's link to the child(successor) and the child(successor) itself
			if (successor->GetRight() != NULL)
			{
				if (successor->GetParent()->GetValue() > successor->GetValue())
				{
				    //successor is the left child
					successor->GetParent()->SetLeft(successor->GetRight());
					successor->GetRight()->SetParent(successor->GetParent());
				}
				else
				{
					//successor is the right child
					successor->GetParent()->SetRight(successor->GetRight());
					successor->GetRight()->SetParent(successor->GetParent());
				};

			}
			else
			{
				if (successor->GetParent()->GetValue() < successor->GetValue())
				{
					successor->GetParent()->SetRight(NULL);
				}
				else
				{
					successor->GetParent()->SetLeft(NULL);
				};

			};

			delete(successor);

			//Copying successor's value
			temp->SetValue(c);

		}
		else
		{
			if ((temp->GetRight() == NULL ) & (temp->GetLeft() == NULL))
			{
				//If there are no children

				//Deletes parent's link to the child and the child
				if (temp->GetParent()->GetValue() > temp->GetValue())
				{
					temp->GetParent()->SetLeft(NULL);
					delete(temp);
				}
				else
				{
					temp->GetParent()->SetRight(NULL);
					delete(temp);
				};
			}
			else
			{
				// If we've got 1 child
				if (temp->GetParent()->GetValue() > temp->GetValue())
				{
					//temp is the left child
					if (temp->GetLeft() != NULL)
					{
						temp->GetParent()->SetLeft(temp->GetLeft());
						temp->GetLeft()->SetParent(temp->GetParent());

						delete(temp);
					}
					else
					{
						temp->GetParent()->SetLeft(temp->GetRight());
						temp->GetRight()->SetParent(temp->GetParent());

						delete(temp);
					};
				}
				else
				{
					//temp is the right child
					if (temp->GetLeft() != NULL)
					{
						temp->GetParent()->SetRight(temp->GetLeft());
						temp->GetLeft()->SetParent(temp->GetParent());

						delete(temp);
					}
					else
					{
						temp->GetParent()->SetRight(temp->GetRight());
						temp->GetLeft()->SetParent(temp->GetParent());

						delete(temp);

					};
				};
			};

		};
	}
	else
	{
		//If we are deleting root
		if (temp == root)
		{
			EmptyTree = true;

			root->SetRight(NULL);
			root->SetParent(NULL);
			root->SetLeft(NULL);
			root->SetValue(NULL);
		};
	};
};

void Tree::DeleteSubTree(TreeNode* SubTree)
{
	//Deletes node and all children including children's children and so on
	//DO NOT USE if you need to delete the whole tree ( DeleteSubTree(root) )
	if (SubTree->GetLeft() != NULL)
	{
		DeleteSubTree(SubTree->GetLeft());
	};

	if (SubTree->GetRight() != NULL)
	{
		DeleteSubTree(SubTree->GetRight());
	};


	delete(SubTree);

};

void Tree::DeleteTree()
{
	//If you wish to delete the whole tree ( DeleteSubTree(root) ), use this method because DeleteSubTree WILL physically delete the root, resulting in error

	if (root->GetLeft() != NULL)
	{
		DeleteSubTree(root->GetLeft());
	};

	if (root->GetRight() != NULL)
	{
		DeleteSubTree(root->GetRight());
	};

	EmptyTree = true;
	root->SetRight(NULL);
	root->SetParent(NULL);
	root->SetLeft(NULL);
	root->SetValue(NULL);
};

void Tree::ShowFromMinToMax(TreeNode* SubTree)
{
	//The idea of algorithm is based on the fact that the value of current node must be printed after values of its' left children and before values of its' right children
	if (SubTree->GetLeft()!= NULL)
	{
		ShowFromMinToMax(SubTree->GetLeft());
	};

	cout<<SubTree->GetValue()<<'|';

	if (SubTree->GetRight()!= NULL)
	{
		ShowFromMinToMax(SubTree->GetRight());
	};
};

TreeNode* Tree::GetRoot()
{
	return root;
};

TreeNode* Tree::CopyChildren( TreeNode** ParentFromTree, TreeNode* NodeToCopy)
{
	TreeNode* temp = new TreeNode;

	temp->SetParent(*ParentFromTree);
	temp->SetValue(NodeToCopy->GetValue());

	if (NodeToCopy->GetLeft()!= NULL)
	{
		temp->SetLeft( CopyChildren(&temp, NodeToCopy->GetLeft()) );
	}
	else
	{
		temp->SetLeft(NULL);
	};

	if (NodeToCopy->GetRight()!= NULL)
	{
		temp->SetRight( CopyChildren(&temp, NodeToCopy->GetRight()) );
	}
	else
	{
		temp->SetRight(NULL);
	};

	return temp;
};

Tree::Tree(const Tree &newTree)
{
	this->EmptyTree = newTree.EmptyTree;

	this->root = new TreeNode;
	this->root->SetParent(NULL);
	this->root->SetValue(newTree.root->GetValue());

	if (newTree.root->GetLeft() != NULL)
	{
		this->root->SetLeft( CopyChildren( &this->root, newTree.root->GetLeft()) );
	}
	else
	{
		this->root->SetLeft(NULL);
	};


	if (newTree.root->GetRight() != NULL)
	{
		this->root->SetRight( CopyChildren( &this->root, newTree.root->GetRight()) );
	}
	else
	{
		this->root->SetRight(NULL);
	};

};

Tree& Tree::operator=(const Tree& newTree)
{

	this->DeleteTree();

	//delete this->root;
	Tree::EmptyTree = newTree.EmptyTree;

	//Tree::root = new TreeNode;
	Tree::root->SetParent(NULL);
	Tree::root->SetValue(newTree.root->GetValue());

	if (newTree.root->GetLeft() != NULL)
	{
		Tree::root->SetLeft( CopyChildren( &root, newTree.root->GetLeft()) );
	}
	else
	{
		Tree::root->SetLeft(NULL);
	}


	if (newTree.root->GetRight() != NULL)
	{
		Tree::root->SetRight( CopyChildren( &this->root, newTree.root->GetRight()) );
	}
	else
	{
		Tree::root->SetRight(NULL);
	};


	//Tree* tr= new Tree (newTree);
   // this = tr;
//	tr = new Tree;

	return *this;

};

void Tree::AddAllElementsFromOtherTree(Tree* tree, TreeNode* node)
{
	tree->Add(node->GetValue());

	if (node->GetLeft() != NULL)
	{
		tree->AddAllElementsFromOtherTree(tree, node->GetLeft());
	};

	if (node->GetRight() != NULL)
	{
		tree->AddAllElementsFromOtherTree(tree, node->GetRight());
	};
};

Tree& Tree::operator+(const Tree& newTree) const
{
	Tree* tr = new Tree;

	if ( !newTree.EmptyTree )
	{
		tr->AddAllElementsFromOtherTree(tr,newTree.root);
	};

	if ( !Tree::EmptyTree)
	{
		tr->AddAllElementsFromOtherTree(tr,Tree::root);
	}

	return *tr;
};

bool Tree::DoesNotExist(int v)
{
	TreeNode* temp = root;
	bool EmptyBranch = false;

	while  (( !EmptyBranch ) & (temp->GetValue() != v))
	{
		if (temp->GetValue() > v)
		{
			if (temp->GetLeft() != NULL)
			{
				temp = temp->GetLeft();
			}
			else
			{
				EmptyBranch = true;
			};
		}
		else
		{
			if (temp->GetRight() != NULL)
			{
				temp = temp->GetRight();
			}
			else
			{
				EmptyBranch = true;
			};

		};
	};

	if (v == temp->GetValue())
	{
		return false;
	}
	else
	{
		return true;
	};
};

void Tree::DeleteAllElementsFromOtherTree(Tree* tree, TreeNode* minuend, Tree* deduction)
{

	if ( deduction->DoesNotExist(minuend->GetValue()) )
	{
		tree->Add(minuend->GetValue());
	};

	if (minuend->GetLeft() != NULL)
	{
		tree->DeleteAllElementsFromOtherTree(tree, minuend->GetLeft(), deduction);
	};

	if (minuend->GetRight() != NULL)
	{
		tree->DeleteAllElementsFromOtherTree(tree, minuend->GetRight(), deduction);
	};
};

Tree& Tree::operator-(const Tree& newTree) const
{
	Tree* tr = new Tree;
	Tree copyTree = newTree;
	//нужна ссылка на то, на что указывает указатель
	Tree* deduction = &copyTree;

	if (newTree.EmptyTree == false)
	{
		tr->DeleteAllElementsFromOtherTree(tr, Tree::root, deduction);
	};

	return *tr;
};

