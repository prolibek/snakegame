#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#define WIDTH 50
#define HEIGHT 25

struct COORD {
    int x, y;
};

class Snake
{
    private:
        int len;
        int speed;
        char dir;
        COORD pos;
        std::vector <COORD> body;
    public:
        Snake (COORD pos, int speed);
        void ChangeDir(char direction);
        std::vector <COORD> GetBody();
        void MoveSnake();
        COORD GetPos();
        bool eaten(COORD food_pos);
        void Grow();
        bool collided();
        char GetDir();
};

#endif // SNAKE_H
