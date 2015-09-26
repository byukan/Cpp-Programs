/** @file TreeNode.h
@brief This file contains class and member function declarations and definitions for TreeNode and related classes, introduced in section 13.2,
which we modify here to provide a templated binary search tree.

You need one class for the tree, containing a pointer to the root node, and a separate class for the nodes.
*/
#pragma once

#include <iostream>
#include <functional>
#include <string>



/** ... */
class Point2D {
	friend std::ostream& operator<<(std::ostream& out, const Point2D& obj);
public:
	//default constructor
	Point2D() { };
	/** ... */
	Point2D(double initial_x, double initial_y) : x(initial_x), y(initial_y) {
		//std::cout << "Point2D("<<x<<","<<y<<") Created"<<std::endl;
	};
	double getx() const { return x; };
	double gety() const { return y; };

	void print() const{ std::cout << "(" << x << "," << y << ")"; return; };

	/** ... */
	virtual ~Point2D() {
		//std::cout << "Point2D("<<x<<","<<y<<") deleted"<<std::endl;
	};
private:
	double x;
	double y;
};

/**...*/
std::ostream& operator<<(std::ostream& out, const Point2D& obj)
{
	// write obj to stream
	out << "(" << obj.x << "," << obj.y << ")";
	return out;
};


/** Order class for Point2D objects using x-values. */
class PointOrderx {
public:
	bool operator()(const Point2D& a, const Point2D& b) {
		return a.getx() < b.getx();
	}
};

/** Order class for Point2D objects using y-values. */
class PointOrdery {
public:
	bool operator()(const Point2D& a, const Point2D& b) {
		return a.gety() < b.gety();
	}
};


template<typename T, typename CMP>
class BinarySearchTree;

template<typename T, typename CMP>
class TreeIterator;

/** @class TreeNode
@brief Each node contains two pointers and a data field.

Dependencies: Requires the < and > operators for the template parameter to be defined.
*/
template<typename T, typename CMP = std::less<T>>
class TreeNode {
	friend BinarySearchTree<T, CMP>;
	friend TreeIterator<T, CMP>;
public:
	// Constructors
	TreeNode();
	TreeNode(T data_);
	// Mutators
	void insert_node(TreeNode<T, CMP>* new_node);
	// Accessors
	void print_nodes() const;
	bool find(T value) const;
	T get_data() const { return data; };
	//Destructor
	virtual ~TreeNode();

private:
	T data;
	CMP lessThan;  //different comparison function
	TreeNode<T, CMP>* left;
	TreeNode<T, CMP>* right;
	TreeNode<T, CMP>* parent;  //add a pointer to parent node

};


/** TreeNode default constructor*/
template<typename T, typename CMP>
TreeNode<T, CMP>::TreeNode() : data(), left(nullptr), right(nullptr), parent(nullptr) {
	//id = generate_id();
	//creation_text();
}


/** TreeNode constructor with parameter*/
template<typename T, typename CMP>
TreeNode<T, CMP>::TreeNode(T data_) : data(data_), left(nullptr), right(nullptr), parent(nullptr) {
	//id = generate_id();
	//creation_text();
}

/** This function inserts a new TreeNode* into the TreeNode, using recursion.
@param new_node is the TreeNode* to insert
*/
template<typename T, typename CMP>
void TreeNode<T, CMP>::insert_node(TreeNode<T, CMP>* new_node){
	if (lessThan(new_node->data, data)){  // check left
		if (left == nullptr){
			left = new_node;
			left->parent = this;
		}
		else left->insert_node(new_node);
	}
	else if (lessThan(data, new_node->data)){  // check right
		if (right == nullptr){
			right = new_node;
			right->parent = this;
		}
		else right->insert_node(new_node);
	}
}

/** This function prints all the nodes of the tree, in order.
*/
template<typename T, typename CMP>
void TreeNode<T, CMP>::print_nodes() const{
	if (left != nullptr)
		left->print_nodes();
	std::cout << data << "\n";
	if (right != nullptr)
		right->print_nodes();
}

/** This function finds a given data value in the tree.
@param value is the data for which to search
@returns true if value is in the BinarySearchTree, false otherwise.
*/
template<typename T, typename CMP>
bool TreeNode<T, CMP>::find(T value) const{
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

/** TreeNode destructor */
template<typename T, typename CMP>
TreeNode<T, CMP>:: ~TreeNode() { }




/** @class BinarySearchTree
@brief friend of TreeNode class that contains a root TreeNode.

Dependencies: Requires the < and > operators for the template parameter to be defined.
*/
template<typename T, typename CMP = std::less<T>>
class BinarySearchTree
{
	//friend class TreeNode<T,CMP>;
	//friend class TreeIterator<T,CMP>;
public:
	BinarySearchTree<T, CMP>();

	// deep copy of BST
	//BinarySearchTree<T, CMP> deep_copy(const BinarySearchTree<T, CMP>& original_tree){
	//	return BinarySearchTree<T, CMP>(original_tree);
	//};

	BinarySearchTree(const BinarySearchTree<T, CMP>& original_tree){
		std::cout << "Copy made" << std::endl;
		root = preorderInsertion(nullptr, original_tree.root);
	};

	// a helper function to recursively copy
	TreeNode<T, CMP>* preorderInsertion(TreeNode<T, CMP>* temp_parent, TreeNode<T, CMP>* original){
		if (original == nullptr){ return nullptr; }
		TreeNode<T, CMP>* new_node = new TreeNode<T, CMP>();
		new_node->data = original->data;
		new_node->parent = temp_parent;
		new_node->left = preorderInsertion(new_node, original->left);
		new_node->right = preorderInsertion(new_node, original->right);
		return new_node;
	};


	// add move constructor
	BinarySearchTree(BinarySearchTree&& t) : root(t.root){ 
		std::cout << "Move performed" << std::endl;
		t.root = nullptr; 
	};



	void swap(BinarySearchTree<T, CMP>& first){
		// by swapping the members of two classes,
		// the two classes are effectively swapped
		std::swap(root, first.root);
	};

	BinarySearchTree<T, CMP>& operator=(BinarySearchTree<T, CMP> other);

	void insert(T data);
	void erase(T data);
	int count(T data) const;
	void print() const;

	TreeIterator<T, CMP> begin();  //TreeIterator<T,CMP> object points to the node with the smallest value
	TreeIterator<T, CMP> end();  //TreeIterator<T,CMP> object points to one after the node with the largest value

	//accessor
	TreeNode<T, CMP>* get_root() const;

	T smallest() const;  //returns smallest element of tree
	T largest() const;  //returns largest element of tree



	void copy(BinarySearchTree<T, CMP>& b_copy, const BinarySearchTree<T, CMP>& b);
	void copy(BinarySearchTree<T, CMP>& b_copy, TreeNode<T, CMP>* node);




	void deallocateTree(TreeNode<T, CMP>* root);
	virtual ~BinarySearchTree<T, CMP>();  //use left, right, then root traversal

private:
	TreeNode<T, CMP>* root;
};


/** BinarySearchTree default constructor
*/
template<typename T, typename CMP>
BinarySearchTree<T, CMP>::BinarySearchTree(){
	root = nullptr;
}

/**This is the swap function, following the style of the copy-swap idiom.
@param other is the other object with which to swap
*/
//template<typename T, typename CMP>
//void BinarySearchTree<T, CMP>::swap(BinarySearchTree<T, CMP>& first){
//	// by swapping the members of two classes,
//	// the two classes are effectively swapped
//	std::swap(root, first.root);
//}
/** Overload operator= .
*/
template<typename T, typename CMP>
BinarySearchTree<T, CMP>& BinarySearchTree<T, CMP>::operator=(BinarySearchTree<T, CMP> other){  //pass by value on purpose
	this->swap(other);
	return *this;
}

/** This function inserts a new Treenode with the given parameter into the BinarySearchTree.
Modified to properly set parent node.
@param data is the Node's int data field
*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::insert(T data){
	TreeNode<T, CMP>* new_node = new TreeNode<T, CMP>(data);
	new_node->data = data;
	new_node->left = nullptr;
	new_node->right = nullptr;
	new_node->parent = nullptr;  //if new_node is root, parent is nullptr
	if (root == nullptr) root = new_node;
	else root->insert_node(new_node);
}

/** This function erases a given data value from the BinarySearchTree.
Modified so that a node with two children is replaced by the largest child of the left subtree.
Modified to properly set parent node.
@param data is the T value to remove
*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::erase(T data){
	//Find node to be removed
	TreeNode<T, CMP>* to_be_removed = root;
	to_be_removed->parent = nullptr;
	bool found = false;
	while (!found && to_be_removed != nullptr){
		if (to_be_removed->data < data){
			to_be_removed->parent = to_be_removed;
			to_be_removed = to_be_removed->right;
		}
		else if (data < to_be_removed->data){
			to_be_removed->parent = to_be_removed;
			to_be_removed = to_be_removed->left;
		}
		else found = true;
	}

	if (!found) return;
	//to_be_removed contains data

	//If one of the children is empty, use the other
	if (to_be_removed->left == nullptr || to_be_removed->right == nullptr){
		TreeNode<T, CMP>* new_child;
		if (to_be_removed->left == nullptr)
			new_child = to_be_removed->right;
		else
			new_child = to_be_removed->left;
		if (to_be_removed->parent == nullptr)  // Found in root
			root = new_child;
		else if (to_be_removed->parent->left == to_be_removed)
			to_be_removed->parent->left = new_child;
		else
			to_be_removed->parent->right = new_child;
		return;
	}

	//Neither subtree is empty
	//*Modified: Find largest element of the left subtree

	TreeNode<T, CMP>* largest_child = to_be_removed;
	TreeNode<T, CMP>* largest = to_be_removed->left;
	while (largest->right != nullptr){
		largest_child = largest;
		largest = largest->right;
	}

	//largest contains largest child in left subtree
	//move contents, unlink child
	to_be_removed->data = largest->data;
	if (largest_child == to_be_removed)
		largest_child->left = largest->left;
	else
		largest_child->right = largest->left;
}


/** This function determines wheter a value is in the set.
@param data is the int to look for in the BinarySearchTree
@returns 1 if the value is in the set, 0 otherwise.
*/
template<typename T, typename CMP>
int BinarySearchTree<T, CMP>::count(T data) const{
	if (root == nullptr) return 0;
	else if (root->find(data)) return 1;
	else return 0;
}


/** This function invokes the TreeNode member function print_nodes().
*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::print() const{
	if (root != nullptr)
		root->print_nodes();
}




/** This function returns a TreeIterator<T,CMP> object that points to the node with the smallest value.
@returns pointer to node with the smallest value
*/
template<typename T, typename CMP>
TreeIterator<T, CMP> BinarySearchTree<T, CMP>::begin(){
	//traverse left until the next left is nullptr
	TreeNode<T, CMP>* smallest = root;
	while (smallest->left){
		smallest = smallest->left;
	}
	TreeIterator<T, CMP> position(smallest, this);
	//std::cout << smallest->get_data() << "\n\n\n"<<this;
	//std::cout << position;
	return position;
}

/** This function returns a TreeIterator<T,CMP> object that points to one after the node with the largest value.
@returns pointer to one after the node with the largest value
*/
template<typename T, typename CMP>
TreeIterator<T, CMP> BinarySearchTree<T, CMP>::end(){
	//traverse right until the next right is nullptr
	TreeNode<T, CMP>* largest = root;
	while (largest->right){
		largest = largest->right;
	}

	//largest->right = new TreeNode<T,CMP>* oneAfterLargest;
	//TreeNode<T,CMP>* oneAfterLargest;
	TreeNode<T, CMP>* oneAfterLargest = largest->right;
	//oneAfterLargest->parent = largest;
	//std::cout<<oneAfterLargest->data;

	//TreeNode<T,CMP>* oneAfterLargest = new TreeNode<T,CMP>;
	//largest->right = oneAfterLargest;
	TreeIterator<T, CMP> iter(oneAfterLargest, this);
	//std::cout << "test test\n" << iter.position->parent->data;

	return iter;
}


/**  ... */
template<typename T, typename CMP>
TreeNode<T, CMP>* BinarySearchTree<T, CMP>::get_root() const{
	return root;
}


/** This function returns the smallest element of a tree.
@returns the smallest element
*/
template<typename T, typename CMP>
T BinarySearchTree<T, CMP>::smallest() const{
	TreeNode<T, CMP>* temp = root;
	while (temp->left != nullptr)
		temp = temp->left;
	return temp->data;
}

/** This function returns the largest element of a tree.
@returns the largest element
*/
template<typename T, typename CMP>
T BinarySearchTree<T, CMP>::largest() const{
	TreeNode<T, CMP>* temp = root;
	while (temp->right != nullptr){
		temp = temp->right;
	}
	return temp->data;
}

/** Helper functions to create deep copy using preorder traversal*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::copy(BinarySearchTree<T, CMP>& b_copy, const BinarySearchTree<T, CMP>& b){
	// iterate recursively on b_copy
	copy(b_copy, b.root);
}
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::copy(BinarySearchTree<T, CMP>& b_copy, TreeNode<T, CMP>* node){
	b_copy.insert(node->data);
	if (node->left){
		b_copy.insert(node->left->data);
	}
	if (node->right){
		b_copy.insert(node->right->data);
	}
}


/** Helper function to recursively deallocate all the node pointers.
*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::deallocateTree(TreeNode<T, CMP>* root){
	if (root->left)
		deallocateTree(root->left);
	if (root->right)
		deallocateTree(root->right);
	delete root;

}


/** BinarySearchTree destructor that deallocates the left subtree, then right, then root.
*/
template<typename T, typename CMP>
BinarySearchTree<T, CMP>::~BinarySearchTree(){
	if (root){
		deallocateTree(root);
		root = nullptr;
	}
}


/** @class TreeIterator
@brief contains a pointer to a TreeNode.
*/
template<typename T, typename CMP = std::less<T>>
class TreeIterator{
	friend class BinarySearchTree<T, CMP>;
	template<typename T, typename CMP>
	friend bool operator==(const TreeIterator<T, CMP>& lhs, const TreeIterator<T, CMP>& rhs);
	template<typename T, typename CMP>
	friend bool operator!=(const TreeIterator<T, CMP>& lhs, const TreeIterator<T, CMP>& rhs);
	/**To output a TreeIterator<T,CMP> */
	template<typename T, typename CMP>
	friend std::ostream& operator<<(std::ostream& out, const TreeIterator<T, CMP>& obj);
public:

	TreeIterator<T, CMP>() : position(nullptr), container(nullptr) { };
	TreeIterator<T, CMP>(TreeNode<T, CMP>* pos, BinarySearchTree<T, CMP>* tree) : position(pos), container(tree) { };

	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;



	TreeIterator<T, CMP>& operator++();
	TreeIterator<T, CMP> operator++(int);
	TreeIterator<T, CMP>& operator--();
	TreeIterator<T, CMP> operator--(int);

private:
	TreeNode<T, CMP>* position;
	BinarySearchTree<T, CMP>* container;
};


//necessary operators for a bidirectional iterator
/** Equals operator
*/
template<typename T, typename CMP>
bool operator==(const TreeIterator<T, CMP>& lhs, const TreeIterator<T, CMP>& rhs){
	if (lhs.position == rhs.position)
		return true;
	else
		return false;
}
/** Not equals operator returns negation of ==
*/
template<typename T, typename CMP>
bool operator!=(const TreeIterator<T, CMP>& lhs, const TreeIterator<T, CMP>& rhs){ return !operator==(lhs, rhs); }

/**...*/
template<typename T, typename CMP>
std::ostream& operator<<(std::ostream& out, const TreeIterator<T, CMP>& obj)
{
	// write obj to stream
	out << obj.position->get_data();
	return out;
}


/** Overload operator* for NodeIterator object.
@returns the dereferenced value of data
*/
template<typename T, typename CMP>
T& TreeIterator<T, CMP>::operator*(){
	return position->data;
}
template<typename T, typename CMP>
const T& TreeIterator<T, CMP>::operator*() const{
	return position->data;
}

/** Overload operator-> for NodeIterator object.
@returns pointer to value type
*/
template<typename T, typename CMP>
T* TreeIterator<T, CMP>::operator->(){
	return &(position->data);
}
template<typename T, typename CMP>
const T* TreeIterator<T, CMP>::operator->() const{
	return &(position->data);
}



/** Overloading operator++ allows iterator to be incremented, a property that all
iterator categories must have.
@param postfix version features a dummy int variable
@returns TreeIterator<T,CMP> pointing to the next larger TreeNode
*/
template<typename T, typename CMP>
TreeIterator<T, CMP>& TreeIterator<T, CMP>::operator++()
{
	if (position->right){
		if (position->right->left){  //if node was right child
			position = position->right;
			while (position->left){
				position = position->left;
			}
		}
		else if (!position->right->left){
			position = position->right;

		}

	}
	// do actual increment
	else if (position == position->parent->left){  //if node was a left child
		position = position->parent;  //go up one parent; that is the next iterator
	}
	else
		position = nullptr;

	return *this;
}
template<typename T, typename CMP>
TreeIterator<T, CMP> TreeIterator<T, CMP>::operator++(int)
{
	TreeIterator<T, CMP> tmp(*this);
	operator++();
	return tmp;
}

/** Overloading operator-- allows iterator to be decremented, a necessary property of
bidirectional iterators

want to get largest smaller value
1. is there a left child, if so there is a left subtree, and largest value of left subtree
is all the way to the right one to the left, all the way on the right
if not, then we are at the beginning of a subtree

@param postfix version features a dummy int variable
@returns TreeIterator<T,CMP> pointing to the previous smaller TreeNode
*/
template<typename T, typename CMP>
TreeIterator<T, CMP>& TreeIterator<T, CMP>::operator--()
{

	if (position == nullptr){
		//return the largest
		TreeNode* temp = container->root;
		while (temp->right != nullptr){
			temp = temp->right;
		}
		position = temp;
		return *this;
	}

	//do actual decrement
	if (position->left){  //if position has a left child, the previous is the left child's rightest descendent
		position = position->left;
		while (position->right){
			position = position->right;
		}
	}

	else if (position == position->parent->right){
		position = position->parent;
		//std::cout<<position->data;
	}
	else if (position == position->parent->left){
		while (position->parent && position == position->parent->left){
			position = position->parent;
		}
		position = position->parent;
	}
	else position = nullptr;


	return *this;
}
template<typename T, typename CMP>
TreeIterator<T, CMP> TreeIterator<T, CMP>::operator--(int)
{
	TreeIterator<T, CMP> tmp(*this);
	operator--();
	return tmp;
}


/**This function is the copy constructor for BinarySearchTree class that creates a deep copy.
@param t is the object to be copied
*/
//BinarySearchTree::BinarySearchTree(BinarySearchTree& t) : root(nullptr){  //nullptr in case of crash




//try{
//	root = new TreeNode;
//	std::cout << "inside the try statement"<<root->data;
//}
//catch (std::exception& e){
//	std::cerr << "Failed to allocate new TreeNode in BinarySearchTree(copy)." << "\n";
//}
//if (root){  //copy values to new contents of memory

//	for (TreeIterator i = t.begin(); i != t.end(); ++i){
//		int data = *i;
//		insert(data);
//	}

//	//BinarySearchTree& bst = *this;
//	//copy(bst, t);
//}




//root = copy.root;
//insert(copy.root->data);
//}

