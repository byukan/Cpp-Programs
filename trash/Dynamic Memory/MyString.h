//
// Created by byukan on 11/20/19.
//

#ifndef CPP_PROGRAMS_MYSTRING_H
#define CPP_PROGRAMS_MYSTRING_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>

/** @class MyString
	@brief This object is designed to make working with sequences of characters a little more convenient and less
 error-prone than handling raw c-strings, (although it will be implemented as a c-string behind the scenes).
 The MyString class will handle constructing strings, reading/printing, and accessing characters. In addition,
 the MyString object will have the ability to make a full deep-copy of itself when copied.
*/
class MyString {
public:
    // Constructors
    MyString() : position(0) {
        char *a = new char[3] { 't', 'h', 'e' };
        id = generate_id();
        creation_text();
    };

    MyString(int pos) : position(pos) {
        id = generate_id();
        creation_text();
    };

    // Accessors
    virtual int get_position() const { return position; };

    virtual void print(ostream &out) const {};

    // Mutator, transformation functions

    //Destructor
    virtual ~MyString();

private:
//    int *array = new int[size];
    int id;  //each particle is given a unique id

    //Protected member function for generating id
    int generate_id() {
        static int id_gen = 0;
        return id_gen++;
    }

    //Display text upon creation of MyString object
    void creation_text() { cout << "created MyString object, id " << id << "\n"; };

    //Display text upon destruction of MyString object
    void deletion_text() { cout << "deleted MyString object, id " << id << "\n"; }

};


#endif //CPP_PROGRAMS_MYSTRING_H
