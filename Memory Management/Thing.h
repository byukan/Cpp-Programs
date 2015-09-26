#pragma once

/** @file Thing.h
	@brief This file contains class and member function declarations for Thing base class and
	inherited classes ThingA and ThingB.  Thing is a particle with a position.
	Also contains Board class.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;



/** @class Thing
	@brief particles that have a position

*/
class Thing {
public:
	// Constructors
	Thing() : position(0) {
		id = generate_id();
		creation_text();
	};
	Thing(int pos) : position(pos) {
		id = generate_id();
		creation_text();
	};
	// Accessors
	virtual int get_position() const {return position; };
	virtual void print(ostream& out) const { };
	// Mutator, transformation functions
	//Destructor
	virtual ~Thing();

protected:  //protected allows derived classes to access private variables of the base class
	int position;
	int id;  //each particle is given a unique id

	//Protected member function for generating id
	int generate_id(){
		static int id_gen=0;
		return id_gen++;
	}
	//Display text upon creation of Thing object
	void creation_text() {cout<<"created Thing object, id "<< id<<"\n";};
	//Display text upon destruction of Thing object
	void deletion_text() {cout<< "deleted Thing object, id "<< id <<"\n";}

};

/** @class ThingA
	@brief inherits from Thing class

	ThingA particles can move to a position where a ThingB particle is currently located.
*/
class ThingA : public Thing {
public:
	ThingA(int pos, string prop) : Thing(pos), property(prop) {};
	virtual void print (ostream& out) const {out<<"A:"<<get_position()<<":"<<property; };

private:
	string property;
};


class Board; //Forward declaration


/** @class ThingB
	@brief inherits from Thing class

	ThingB particles can't be placed or moved on the board to a position that is already occupied
	by another particle of either type.
*/
class ThingB : public Thing {
public:
	ThingB(int pos, double prop , Board* b) : Thing(pos) , property(prop) , board(b) { } ;
	virtual void print(ostream& out) const {out<<"B: "<<get_position()<<":"<< property; };

	bool propose_new_position(int position);

private:
	double property;
	Board* board;
};

/** @class Board
	@brief Board class contains Thing particles.
*/
class Board {
public:
	bool ParticleInPosition (int pos) const {
		for (size_t i=0;i<things.size(); ++i)
			if (things[i] -> get_position() == pos)
				return true;
	return false;
	};

	void AddAParticle (int pos , string prop) {
		try{
			thing = new ThingA (pos, prop);
		}
		catch(std::exception e){
			if(thing) delete thing;
			thing = nullptr;
			std::cerr << "Failed to allocate a new ThingA\n";
		}
	things.push_back (thing) ;
	};

	 bool AddBParticle (int pos, double prop ) {
		// If no particle is at position pos, then add, otherwise don't add.
			if ( !ParticleInPosition(pos) ) {
				try{
					thing = new ThingB(pos, prop, this);
				}
				catch(std::exception e){
					if(thing) delete thing;
					thing = nullptr;
					std::cerr<< "Failed to allocate a new ThingB\n";
				}
				things.push_back(thing) ;

			return true;
			}
		    return false;
	};

	 bool operator()();
	 bool operator[](int pos);
	 void AddThingBParticlePtr(Thing* B){
		 for (size_t i = 0, n = things.size(); i < n; ++i){
			 if (things[i] == B){
				 return;
			 }
		 }
		 things.push_back(B);
	 }


	 // Accessor
	 vector<Thing*> get_things() {return things;};

	 //Destructor
	virtual ~Board();

private:
	vector<Thing*> things;
	Thing* thing;
};


ostream& operator<<(ostream& out, Board& board);

