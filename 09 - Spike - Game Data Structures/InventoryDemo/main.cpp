#include "Inventory.h"
#include "Bag.h"
#include "Rock.h"

int main() {
    Inventory inv = Inventory();
    Bag b1 = Bag();
    Bag b2 = Bag();
    Rock r1 = Rock();
    Rock r2 = Rock();

    inv.AddItem(b1);
    inv.PrintContents();
    inv.AddItem(b2);
    inv.PrintContents();
    inv.AddItem(r1);
    inv.PrintContents();
    inv.AddItem(r2);
    inv.PrintContents();

    inv.RemoveItem(ItemType::BAG);
    inv.PrintContents();
    inv.RemoveItem(ItemType::ROCK);
    inv.PrintContents();

    return 0;
}