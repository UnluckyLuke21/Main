#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;


class Person{
public:
    Person(string n, int m, vector<string> i);
    void trade(int item, Person& other);
    void printInventory();

private:
    string name;
    int money;
    vector<string> inventory;
};