#include "Food.h"

void Food::GenFood(){
    posf.x = (rand() % (WIDTH-2))+1;
    posf.y = (rand() % (HEIGHT-2))+1;
}

COORD Food::GetPos() { return posf; }
