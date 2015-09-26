/** @file Thing.cpp
	@brief This file contains function definitions for Thing and classes derived from it.

	This file contains function definitions for Board class.
*/

#include <iostream>
#include <vector>
#include <string>
#include "Thing.h"

using std::cout;
using std::endl;

/** Thing destructor */
Thing:: ~Thing() {
	deletion_text();
}


/** Board destructor */
Board:: ~Board() {
	for(auto x: things){
		delete x;
	}
	cout<< "deleted things vector of thing pointers\n";
}


/** This function overloads the non-member operator<< to print out the particles
	one line at a time.
	@param out is the ostream& that lets us write, for example, <<Z
	@param board is the Board object that gets printed
	@returns out is the ostream&
*/
ostream& operator<<(ostream& out, Board& board)
{
	vector<Thing*> v = board.get_things();
	for(size_t i=0, n=v.size(); i<n; ++i){
		out << "\n";
		v[i]->print(out);
	}
	return out;
}


/** This function first checks to see if there are any other particles currently located in the position 
	of the input value, and if not then it replaces its current position with the input value, and if so then 
	it does not update its position.  If the position changes then it returns true, and if it does not change
	then it returns false.
	@param position(int) is the position to check
	@returns true if position changes, false if it does not change
*/
bool ThingB::propose_new_position(int pos)
{
	if (board->ParticleInPosition(pos)){  //checks if particles in position of input
		return false;
	}
	position = pos;  //replaces current position with input value
	return true;
}

/** This overloads the member Board::operator[], which returns true if any of the particles
	on the board have position equal to the input value, and false otherwise.
	@param pos is the position
	@returns true if any particle on the board is at pos of input, false otherwise
*/
bool Board::operator[](int pos)
{
	return this->ParticleInPosition(pos);
}

/** This overloads the member Board::operator() to return true if there are any particles that
	share the same positon.
	@param void
	@returns true if any particles share same position
*/
bool Board::operator()()
{
	vector<int> VectorOfPositions;  //create vector to store all position values
	for (auto x : things){
		VectorOfPositions.push_back(x->get_position());  //positions of all particles in things vector
	}
	
	//check for repeating elements in vector of positions
	for (size_t i = 0, n = VectorOfPositions.size()-1; i < n; ++i){
		for (size_t j = i + 1, n = VectorOfPositions.size(); j < n; ++j){
			if (VectorOfPositions[i] == VectorOfPositions[j]){
				return true;
			}
		}
	}
	return false;
}
