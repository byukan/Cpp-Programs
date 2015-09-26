/** @mainpage PIC 10C hw7
@author Justin Wang
@id 604219879
@date 5/14/15

Template the binary search tree class so that it has two template parameters.
*/

/* you must include these three, in this order to use the
visual studio memory leak tool*/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <string>
#include "TreeNode.h"

int main()
{
	//need this to get a memory leak dump at end of code execution
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Create binary search tree, give it values {2,3,5,11,13,17}
	BinarySearchTree<int> bst;
	bst.insert(3); bst.insert(2); bst.insert(11);
	bst.insert(13); bst.insert(5); bst.insert(17);

	// Prints to the console: 2,3,5,11,13,17,
	for (auto x : bst) std::cout << x << ",";
	std::cout << std::endl;

	BinarySearchTree<Point2D, PointOrderx> points_by_x;
	points_by_x.insert(Point2D(1, 2));
	points_by_x.insert(Point2D(7, 3));
	points_by_x.insert(Point2D(2, 1));

	// Prints to the console : (1,2) , (2,1 ),( 7,3 ),
	for (auto x : points_by_x) std::cout << x << ",";
	std::cout << std::endl;

	BinarySearchTree< Point2D, PointOrdery> points_by_y;
	points_by_y.insert(Point2D(1, 2));
	points_by_y.insert(Point2D(7, 3));
	points_by_y.insert(Point2D(2, 1));

	// Prints to the console: (2,1) , (1,2) , (7,3),
	for (auto x : points_by_y) std::cout << x << ",";
	std::cout << std::endl;

	BinarySearchTree<std::string, std::greater<std::string>>names;
	names.insert("Luke");
	names.insert("Kanye");
	names.insert("Pentatonix ");

	// Prints to the console : Pentatonix , Luke ,Kanye
	for (auto x : names) std::cout << x << " , ";
	std::cout << std::endl;

	return 0;
}