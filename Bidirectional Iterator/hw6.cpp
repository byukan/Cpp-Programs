/** @mainpage PIC 10C hw6
@author Justin Wang
@id 604219879
@date 5/6/15

In this assignment, we extend the textbook's binary search tree data strucutre and our own bidirectional iterator
for that strucutre.  TreeNode and BinarySearchTree classes are modified to hold ints instead of strings.
*/

/* you must include these three, in this order to use the
visual studio memory leak tool*/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "TreeNode.h"

int main()
{
	//need this to get a memory leak dump at end of code execution
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Create binary search tree, give it values {2,3,5,11,13,17}
	BinarySearchTree bst;
	bst.insert(3); bst.insert(2); bst.insert(11);
	bst.insert(13); bst.insert(5); bst.insert(17);


	// Prints to the console: 2,3,5,11,13,17,
	for (auto x : bst) std::cout << x << ",";
	std::cout << std::endl;

	bst.erase(6);  // {2,3,5,11,13,17}, no effect
	bst.erase(11);  // {2,3,5,13,17}

	auto start = std::begin(bst);
	auto stop = std::end(bst);

	int value = 17;

	bool keep_looking = true;

	// find a 17 in the list
	while (start != stop && keep_looking){
		if (*start++ == value){
			keep_looking = false;
		}
	}
	--start;

	//// Prints "17 is in the list."
	if (start != stop)
		std::cout << *start << " is in the list." << std::endl;

	//Construct a deep copy of bst.

	//std::cout << "0.\n";
	//bst.print();
	//std::cout << "1.\n";
	BinarySearchTree deep_copy(bst);
	//std::cout << "2.\n";



	deep_copy.insert(11); deep_copy.insert(7);


	// Prints to the console: 2,3,5,7,11, 13, 17,
	for (auto x : deep_copy) std::cout << x << ",";
	std::cout << std::endl;


	//std::cout << "\n\n\n\n\n";


	//bst.print();
	//deep_copy.print();
	
	return 0;
}
