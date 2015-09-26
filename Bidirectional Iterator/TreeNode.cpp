/** @file TreeNode.cpp
@brief This file contains function definitions for TreeNode and related classes.
*/

#include "TreeNode.h"


/** TreeNode default constructor*/
//TreeNode::TreeNode() : data(0), left(nullptr), right(nullptr), parent(nullptr) {
//	id = generate_id();
//	creation_text();
//}

/** BinarySearchTree default constructor
*/
BinarySearchTree::BinarySearchTree(){
	root = nullptr;
}


/** This function invokes the TreeNode member function print_nodes().
*/
void BinarySearchTree::print() const{
	if (root != nullptr)
		root->print_nodes();
}

/** This function inserts a new Treenode with the given parameter into the BinarySearchTree.
Modified to properly set parent node.
@param data is the Node's int data field
*/
void BinarySearchTree::insert(int data){
	TreeNode* new_node = new TreeNode;
	new_node->data = data;
	new_node->left = nullptr;
	new_node->right = nullptr;
	new_node->parent = nullptr;  //if new_node is root, parent is nullptr
	if (root == nullptr) root = new_node;
	else root->insert_node(new_node);
}

/** This function inserts a new TreeNode* into the TreeNode, using recursion.
@param new_node is the TreeNode* to insert
*/
void TreeNode::insert_node(TreeNode* new_node){
	if (new_node->data < data){
		if (left == nullptr){
			//            parent = this;
			left = new_node;
			left->parent = this;
		}
		else left->insert_node(new_node);
	}
	else if (new_node->data > data){
		if (right == nullptr){
			//            parent = this;
			right = new_node;
			right->parent = this;
		}
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
Modified to properly set parent node.
@param data is the int value to remove
*/
void BinarySearchTree::erase(int data){
	//Find node to be removed
	TreeNode* to_be_removed = root;
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
		TreeNode* new_child;
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

	TreeNode* largest_child = to_be_removed;
	TreeNode* largest = to_be_removed->left;
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

/** This function returns a TreeIterator object that points to the node with the smallest value.
@returns pointer to node with the smallest value
*/
TreeIterator BinarySearchTree::begin(){
	//traverse left until the next left is nullptr
	TreeNode* smallest = root;
	while (smallest->left){
		smallest = smallest->left;
	}
	TreeIterator position(smallest, this);
	//std::cout << smallest->get_data() << "\n\n\n"<<this;
	//std::cout << position;
	return position;
}

/** This function returns a TreeIterator object that points to one after the node with the largest value.
@returns pointer to one after the node with the largest value
*/
TreeIterator BinarySearchTree::end(){
	//traverse right until the next right is nullptr
	TreeNode* largest = root;
	while (largest->right){
		largest = largest->right;
	}

	//largest->right = new TreeNode* oneAfterLargest;
	//TreeNode* oneAfterLargest;
	TreeNode* oneAfterLargest = largest->right;
	//oneAfterLargest->parent = largest;
	//std::cout<<oneAfterLargest->data;

	//TreeNode* oneAfterLargest = new TreeNode;
	//largest->right = oneAfterLargest;
	TreeIterator iter(oneAfterLargest, this);
	//std::cout << "test test\n" << iter.position->parent->data;

	return iter;
}

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
	while (temp->right != nullptr){
		temp = temp->right;
	}
	return temp->data;
}


/** TreeNode destructor */
TreeNode:: ~TreeNode() {
	//deletion_text();
}


/** Helper function to recursively deallocate all the node pointers.
*/
void BinarySearchTree::deallocateTree(TreeNode* root){
	if (root->left)
		deallocateTree(root->left);
	if (root->right)
		deallocateTree(root->right);
	delete root;

}


/** BinarySearchTree destructor that deallocates the left subtree, then right, then root.
*/
BinarySearchTree::~BinarySearchTree(){
	if (root){
		deallocateTree(root);
		root = nullptr;
	}
}


/** Overloading operator++ allows iterator to be incremented, a property that all
iterator categories must have.
@param postfix version features a dummy int variable
@returns TreeIterator pointing to the next larger TreeNode
*/
TreeIterator& TreeIterator::operator++()
{
	//std::cout<<position;
	//std::cout<<position->parent;
	//std::cout<<position->parent->left;

	if (position->right){

		if (position->right->left){  //if node was right child
			position = position->right;
			while (position->left){
				//std::cout<<"case3";
				position = position->left;
			}
		}

		else if (!position->right->left){
			//std::cout<<"case1";
			position = position->right;
			//if(position->right->left){  //next is the right child's leftest descendent
			//    while (position->right->left){
			//        std::cout<<"fejwatiorapji";
			//        position = position->right->left;
			//    }

		}

	}
	// do actual increment

	else if (position == position->parent->left){  //if node was a left child
		//std::cout<<position->parent->data;
		//std::cout<<"case2";
		//move to the position's parent
		position = position->parent;  //go up one parent; that is the next iterator
	}

	else
		position = nullptr;

	return *this;
}
TreeIterator TreeIterator::operator++(int)
{
	TreeIterator tmp(*this);
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
@returns TreeIterator pointing to the previous smaller TreeNode
*/
TreeIterator& TreeIterator::operator--()
{

	if (position == nullptr){
		//std::cout << "position is nullptr";
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
		//std::cout<<"case1";
		position = position->left;
		while (position->right){
			position = position->right;
		}
	}

	else if (position == position->parent->right){
		//std::cout<<"case2";
		position = position->parent;
		//std::cout<<position->data;
	}
	else if (position == position->parent->left){
		//std::cout<<"case3";
		while (position->parent && position == position->parent->left){
			position = position->parent;
		}
		position = position->parent;
	}
	else position = nullptr;


	return *this;
}
TreeIterator TreeIterator::operator--(int)
{
	TreeIterator tmp(*this);
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


/** Helper functions to create deep copy using preorder traversal*/
void BinarySearchTree::copy(BinarySearchTree& b_copy, const BinarySearchTree& b){
	// iterate recursively on b_copy
	copy(b_copy, b.root);
}
void BinarySearchTree::copy(BinarySearchTree& b_copy, TreeNode* node){
	b_copy.insert(node->data);
	if (node->left){
		b_copy.insert(node->left->data);
	}
	if (node->right){
		b_copy.insert(node->right->data);
	}
}



/**This is the swap function, following the style of the copy-swap idiom.
@param other is the other object with which to swap
*/
void swap(BinarySearchTree& first, BinarySearchTree& second){
	// by swapping the members of two classes,
	// the two classes are effectively swapped
	std::swap(first.root, second.root);
}

/**...*/
BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree other){  //pass by value on purpose
	swap(*this, other);
	return *this;
}


/** Overload operator* for NodeIterator object.
@returns the dereferenced value of data
*/
int& TreeIterator::operator*(){
	return position->data;
}
const int& TreeIterator::operator*() const{
	return position->data;
}

/** Overload operator-> for NodeIterator object.
@returns pointer to value type
*/
int* TreeIterator::operator->(){
	return &(position->data);
}
const int* TreeIterator::operator->() const{
	return &(position->data);
}

/**  ... */
TreeNode* BinarySearchTree::get_root() const{
	return root;
}


/**...*/
std::ostream& operator<<(std::ostream& out, const TreeIterator& obj)
{
	// write obj to stream
	out << obj.position->get_data();
	return out;
}

