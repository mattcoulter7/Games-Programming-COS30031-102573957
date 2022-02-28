#include "Inventory.h"

class Player {
public:
    Player();
    void SetLocation(int _location);
    int GetLocation();
    Inventory* GetInventory();
private:
    int location;// current world ID(int)
    Inventory* inventory; // inventory list of item id's (ints)
    int steps; // move / action counter
};