/** @mainpage PIC 10C hw2
	@author Justin Wang
	@id 604219879
	@date 4/9/15

	Fixes all of the memory leaks in Homework 1.  Also, gives each Particle a unique id.
	Write code in main to demonstrate that all particles allocated on the heap eventually get deleted.
	This assignment models particles on a line.  Every particle will have a position.
*/

/* you must include these three, in this order to use the 
visual studio memory leak tool*/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Thing.h"

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::vector;


int main()
{
	//need this to get a memory leak dump at end of code execution
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );


	Board Z;
	Z.AddAParticle(0, "red");
	Z.AddBParticle(9, 2.71828);
	Z.AddAParticle(7, "yellow");
	//ThingA a = ThingA(0, "red");
	//a.print(cout);
	ThingB* B = new ThingB(-1, 9, &Z);
	
	
	cout<<"Does the particle at position 5 change?(true)   "<< B->propose_new_position(5)<<"\n\n";
	//cout << "Did the propose_new_position function replace the current position with the input value?(5)   ";
	//cout << Z.get_things()[5];
	cout << "Does the particle at position 7 change?(false)   " << B->propose_new_position(7) << "\n\n";



	cout << Z << endl << endl;
	cout << "Is there a particle at 9?(true)   " << Z[9]<<"\n\n";  //should return a 1
	cout << "Is there a particle at 3?(false)   " << Z[3]<<"\n\n";  //should return 0

	cout <<"Do any particles share the same position?(false)   "<< Z()<<"\n\n";
	Z.AddAParticle(0, "lavender");
	cout << "Two particles should now share the same position.(true)   " << Z() << "\n\n";

	ThingB* B1 = new ThingB(-1, 5, &Z);
	ThingB* B2 = new ThingB(-2, 4, &Z);

	B1->propose_new_position(9);  //checks to see if B1 object changed and if placed on board
	Z.AddThingBParticlePtr(B1);  //add B1 to the board, Z

	cout<<"B1 object:  ";
	B1->print(cout);
	cout << "\nGood, B1 did not change its position to 9 because there's already a Thing there." << Z;


	cout << endl << endl;
	B2->propose_new_position(2);
	Z.AddThingBParticlePtr(B2);  //add B2 to the board, Z
	cout<<"B2 object:  ";
	B2->print(cout);
	cout << "\nAs expected, B2 changed its position to 2.";
	cout <<"\n\n"<< Z <<"\n\n";
	
	/*  These pointers get deleted after they get added to the board, whose deconstructor automatically deallocates all
		thing pointers on it, in the vector, thing, of thing pointers.
	*/
	//delete B;
	//delete B1;
	//delete B2;

	cout << "\n\n";

	return 0;

	//_CrtDumpMemoryLeaks();
}


