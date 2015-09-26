/** @file TreeNode.cpp
@brief This file contains function definitions for TreeNode and related classes.
*/

#include <iostream>
#include "TreeNode.h"

/** TreeNode default constructor*/
TreeNode::TreeNode() : data(0), left(nullptr), right(nullptr) {
	id = generate_id();
	creation_text();
}

/** TreeNode destructor */
TreeNode:: ~TreeNode() {
	deletion_text();
}

/** BinarySearchTree default constructor
*/
BinarySearchTree::BinarySearchTree(){
	root=nullptr;
}


/** This function invokes the TreeNode member function print_nodes().
*/
void BinarySearchTree::print() const{
	if (root != nullptr)
		root->print_nodes();
}

/** This function inserts a new Treenode with the given parameter into the BinarySearchTree.
@param data is the Node's int data field
*/
void BinarySearchTree::insert(int data){
	TreeNode* new_node = new TreeNode;
	new_node->data = data;
	new_node->left = nullptr;
	new_node->right = nullptr;
	if (root == nullptr) root = new_node;
	else root->insert_node(new_node);
}

/** This function inserts a new TreeNode* into the TreeNode, using recursion.
@param new_node is the TreeNode* to insert
*/
void TreeNode::insert_node(TreeNode* new_node){
	if (new_node->data < data){
		if (left == nullptr) left = new_node;
		else left->insert_node(new_node);
	}
	else if (data < new_node->data){
		if (right == nullptr) right = new_node;
		else right->insert_node(new_node);
	}
}

/** This function determines wheter a value is in the set.
@param data is the int to look for in the BinarySearchTree
@returns 1 if hte value is in the set, 0 otherwise.
*/
int BinarySearchTree::count(int data) const{
	if (root == nullptr) return 0;
	else if (root->find(data)) return 1;
	else return 0;
}

/** This function erases a given data value from the BinarySearchTree.
	Modified so that a node with two children is replaced by the largest child of the left subtree.
	@param data is the int value to remove
*/
void BinarySearchTree::erase(int data){
	//Find node to be removed
	TreeNode* to_be_removed = root;
	TreeNode* parent = nullptr;
	bool found = false;
	while (!found && to_be_removed != nullptr){
		if (to_be_removed->data < data){
			parent = to_be_removed;
			to_be_removed - to_be_removed->right;
		}
		else if (data < to_be_removed->data){
			parent = to_be_removed;
			to_be_removed - to_be_removed->left;
		}
		else found = true;
	}

	if (!found) return;
	//to_be_removed contains data
	
	//If one of the children is empty, use the other
	if (to_be_removed->left == nullptr || to_be_removed->right == nullptr){
		TreeNode* new_child;
		if (to_be_removed->left == nullptr)
			new_child = to_be_removed->right;
		else
			new_child = to_be_removed->left;
		if (parent == nullptr)  // Found in root
			root = new_child;
		else if (parent->left == to_be_removed)
			parent->left = new_child;
		else
			parent->right = new_child;
		return;
	}

	//Neither subtree is empty
	//Find smallest element of the right subtree

	TreeNode* smallest_parent = to_be_removed;
	TreeNode* smallest = to_be_removed->right;
	while (smallest->left != nullptr){
		smallest_parent = smallest;
		smallest = smallest->left;
	}

	//smallest contains smallest child in right subtree
	//move contents, unlink child
	to_be_removed->data = smallest->data;
	if (smallest_parent == to_be_removed)
		smallest_parent->right = smallest->right;
	else
		smallest_parent->left = smallest->right;

}

/** This function finds a given data value in the tree.
@param value is the data for which to search
@returns true if value is in the BinarySearchTree, false otherwise.
*/
bool TreeNode::find(int value) const{
	if (value < data){
		if (left == nullptr) return false;
		else return left->find(value);
	}
	else if (data < value){
		if (right == nullptr) return false;
		else return right->find(value);
	}
	else
		return true;
}

/** This function prints all the nodes of the tree, in order.
*/
void TreeNode::print_nodes() const{
	if (left != nullptr)
		left->print_nodes();
	std::cout << data << "\n";
	if (right != nullptr)
		right->print_nodes();
}


/** This function 
*/
//TreeIterator* TreeIterator::begin(){
//	return;
//}

/** This function returns the smallest element of a tree.
	@returns the smallest element
*/
int BinarySearchTree::smallest() const{
	TreeNode* temp = root;
	while (temp->left != nullptr)
		temp = temp->left;
	return temp->data;
}

/** This function returns the largest element of a tree.
@returns the largest element
*/
int BinarySearchTree::largest() const{
	TreeNode* temp = root;
	while (temp->left != nullptr)
		temp = temp->left;
	return temp->data;
}