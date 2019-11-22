//
// Created by byukan on 11/20/19.
//

#include "Creature.h"

/***
 * Creature destructor
 */
Creature:: ~Creature() {
    deletion_text();
}


/**
 * Here is an implementation of the getSpecies() function.
 * @return
 */
string Creature::getSpecies() const {
    switch (type) {
        case 0:
            return "Human";
        case 1:
            return "Cyberdemon";
        case 2:
            return "Balrog";
        case 3:
            return "Elf";
    }
    return "unknown";
}
