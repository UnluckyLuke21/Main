#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

class Bot{
public:
    Bot();
    void move(int x, int y);
    int explore(vector<vector<int>> field);

private:
    int direction;
    int posX;
    int posY;
    
    // Map
    vector<vector<int>> map;
};