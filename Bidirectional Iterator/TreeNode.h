/** @file TreeNode.h
@brief This file contains class and member function declarations for TreeNode class, introduced in section 13.2,
which we modify here to provide a binary search tree of integers.

You need one class for the tree, containing a pointer to the root node, and a separate class for the nodes.
*/
#pragma once

#include <iostream>

/** @class TreeNode
@brief Each node contains two pointers and a data field.

*/
class TreeNode {
	friend class BinarySearchTree;
	friend class TreeIterator;
public:
	// Constructors
	//TreeNode();
	// Accessors
	void print_nodes() const;
	bool find(int value) const;
	int get_data() const { return data; };
	// Mutators
	void insert_node(TreeNode* new_node);
	//Destructor
	virtual ~TreeNode();

	//member function for generating id
	int generate_id(){
		static int id_gen = 0;
		return id_gen++;
	}
	//Display text upon creation of TreeNode object
	void creation_text() { std::cout << "created TreeNode object, id " << id << "\n"; };
	//Display text upon destruction of TreeNode object
	void deletion_text() { std::cout << "deleted TreeNode object, id " << id << "\n"; }

private:
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;  //add a pointer to parent node

	int id;  //each object is given a unique id
};

/** @class BinarySearchTree
@brief friend of TreeNode class that contains a root TreeNode
*/
class BinarySearchTree
{
	friend class TreeNode;
	friend class TreeIterator;
public:
	BinarySearchTree();


	//deep copy constructor, and copy-swap idiom
	//needed because it does manage heap memory
	//BinarySearchTree(BinarySearchTree& t);


	// deep copy of BST
	BinarySearchTree deep_copy(const BinarySearchTree& original_tree){ return BinarySearchTree(original_tree); };

	BinarySearchTree(const BinarySearchTree& original_tree){
		root = preorderInsertion(nullptr, original_tree.root);
	};
	// a helper function to recursively copy
	TreeNode* preorderInsertion(TreeNode* temp_parent, TreeNode* original){
		if (original == nullptr){ return nullptr; }

		TreeNode* new_node = new TreeNode();
		new_node->data = original->data;
		new_node->parent = temp_parent;
		new_node->left = preorderInsertion(new_node, original->left);
		new_node->right = preorderInsertion(new_node, original->right);
		return new_node;
	}




	friend void swap(BinarySearchTree& first, BinarySearchTree& second); // nothrow
	BinarySearchTree& operator=(BinarySearchTree other);

	void insert(int data);
	void erase(int data);
	int count(int data) const;
	void print() const;

	TreeIterator begin();  //TreeIterator object points to the node with the smallest value
	TreeIterator end();  //TreeIterator object points to one after the node with the largest value

	//accessor
	TreeNode* get_root() const;

	int smallest() const;  //returns smallest element of tree
	int largest() const;  //returns largest element of tree



	void copy(BinarySearchTree& b_copy, const BinarySearchTree& b);
	void copy(BinarySearchTree& b_copy, TreeNode* node);




	void deallocateTree(TreeNode* root);
	virtual ~BinarySearchTree();  //use left, right, then root traversal

private:
	TreeNode* root;
};

/** @class TreeIterator
@brief contains a pointer to a TreeNode.
*/
class TreeIterator{
	friend class BinarySearchTree;
	friend bool operator==(const TreeIterator& lhs, const TreeIterator& rhs);
	/**To output a TreeIterator */
	friend std::ostream& operator<<(std::ostream& out, const TreeIterator& obj);
public:
	TreeIterator() : position(nullptr), container(nullptr) { };
	TreeIterator(TreeNode* pos, BinarySearchTree* tree) : position(pos), container(tree) { };

	int& operator*();
	const int& operator*() const;
	int* operator->();
	const int* operator->() const;



	TreeIterator& operator++();
	TreeIterator operator++(int);
	TreeIterator& operator--();
	TreeIterator operator--(int);

private:
	TreeNode* position;
	BinarySearchTree* container;
};


//necessary operators for a bidirectional iterator
/** Equals operator
*/
inline bool operator==(const TreeIterator& lhs, const TreeIterator& rhs){
	if (lhs.position == rhs.position)
		return true;
	else
		return false;
}
/** Not equals operator returns negation of ==
*/
inline bool operator!=(const TreeIterator& lhs, const TreeIterator& rhs){ return !operator==(lhs, rhs); }
