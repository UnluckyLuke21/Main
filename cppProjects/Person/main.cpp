#include <iostream>
#include <vector>
#include <string>

#include "../include/person.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::string;


int main(){

    vector<string> inventory;
    inventory.push_back("Tape");
    inventory.push_back("Keys");
    inventory.push_back("Phone");
    inventory.push_back("Paper");


    Person L("L", 100, inventory);
    Person O("O", 100, inventory);

    L.printInventory();
    O.printInventory();

    L.trade(2, O);

    L.printInventory();
    O.printInventory();

    return 0;
}