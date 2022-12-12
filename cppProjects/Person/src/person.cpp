#include "../include/person.hpp"

#pragma once

Person::Person(string n, int m, vector<string> i) : name(n), money(m){

    // Create Inventory:
    for(int j = 0; j < i.size(); j++){
        this->inventory.push_back(i[j]);
    }
}

void Person::trade(int item, Person &other){

    cout << "Trading" << endl;

    // Take Item from Other Person:
    string tempItem = other.inventory[item];
    other.inventory.erase(other.inventory.begin() + item);

    // Give Item to Self Person:
    this->inventory.push_back(tempItem);
}

void Person::printInventory(){

    //Print Self Inventory:
    cout << "Inventory " << this->name << ":" << endl;
    for(int i = 0; i < this->inventory.size(); i++){
        cout << this->inventory[i] << endl;
    }
    cout << endl;
}