//
// Created by byukan on 11/20/19.
//

#ifndef CPP_PROGRAMS_CREATURE_H
#define CPP_PROGRAMS_CREATURE_H


class Creature {
public:
    Creature();             // initialize to Human, 10 strength, 10 hitpoints
    Creature(int newType, int newStrength, int newHitpoints);

    int getDamage() const;         // returns the amount of damage this Creature
    // inflicts in one round of combat

    // also include appropriate accessors and mutators

    //Destructor
    virtual ~Creature();


protected:  //protected allows derived classes to access private variables of the base class
    int type;               // 0 Human, 1 Cyberdemon, 2 Balrog, 3 elf
    int strength;           // how much damage this Creature inflicts
    int hitpoints;          // how much damage this Creature can sustain
    string getSpecies() const;    // returns the type of the species

    //Display text upon creation of Creature object
    void creation_text() {std::cout<<"created Creature object, id "<< id<<"\n";};
    //Display text upon destruction of Creature object
    void deletion_text() {std::cout<< "deleted Creature object, id "<< id <<"\n";}
};


#endif //CPP_PROGRAMS_CREATURE_H
