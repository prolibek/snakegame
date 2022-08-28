#include "Snake.h"

Snake::Snake(COORD pos, int speed)
{
    this->pos = pos;
    this->speed = speed;
    len = 1;
    dir = 'n';
    body.push_back(pos);
}

void Snake::ChangeDir (char direction) {
    this->dir = direction;
}

std::vector <COORD> Snake::GetBody(){
    return body;
}

void Snake::MoveSnake() {
    switch(dir) {
        case 'w':
            pos.y -= speed;
            break;
        case 's':
            pos.y += speed;
            break;
        case 'a':
            pos.x -= speed;
            break;
        case 'd':
            pos.x += speed;
            break;
    }

    body.push_back(pos);
    if(body.size() > len)
        body.erase(body.begin());
}

COORD Snake::GetPos() {
    return pos;
}

bool Snake::eaten (COORD food_pos) {
    if((food_pos.x == pos.x) && (food_pos.y == pos.y))
        return true;
    return false;
}

void Snake::Grow () {
    len++;
}

bool Snake::collided () {
    if(pos.x < 1 || pos.x > WIDTH-2 || pos.y < 1 || pos.y > HEIGHT-2)
        return true;

    for(int i = 0; i < len-1; i++)
    {
        if(pos.x == body[i].x && pos.y == body[i].y)
            return true;
    }
    return false;
}

char Snake::GetDir() {
    return dir;
}
