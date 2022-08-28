#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <cstdio>
#include "Snake.h"

#define WIDTH 50
#define HEIGHT 25

class Food
{
    private:
        COORD posf;
    public:
        void GenFood();
        COORD GetPos();
};

#endif // FOOD_H
