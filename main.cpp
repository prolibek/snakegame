#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include "Snake.h"
#include "Food.h"

#ifndef __linux

#include <conio.h>

#else

#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

bool kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}
int _getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

#endif // __linux

#define WIDTH 50
#define HEIGHT 25

void Map (Food food, Snake snake) {
    COORD snake_pos = snake.GetPos();
    COORD food_pos = food.GetPos();

    std::vector <COORD> snake_body = snake.GetBody();

    for(int i = 0; i < HEIGHT; i++) {
        std::cout << "\t\t#";
        for(int j = 0; j < WIDTH - 2; j++) {
            if(i == 0 || i == HEIGHT-1)
                std::cout << "#";

            else if(snake_pos.x == j+1 && snake_pos.y == i)
                std::cout << "@";
            else if(food_pos.x == j+1 && food_pos.y == i)
                std::cout << "*";

            else {
                bool isBodyPart = false;
                for(int k = 0; k < snake_body.size()-1; k++){
                    if(i == snake_body[k].y && j+1 == snake_body[k].x){
                        std::cout << "0";
                        isBodyPart = true;
                        break;
                    }
                }
                if(!isBodyPart)
                    std::cout << ' ';
            }
        }
        std::cout << "#\n";
    }
}

void game (Food food, Snake snake) {
    srand(time(NULL));

    food.GenFood();

    bool gameOver = false;

    while(!gameOver){
        Map(food, snake);
        if(kbhit()){
            switch(_getch()){
                case 'w':
                    if(snake.GetDir() != 's')
                        snake.ChangeDir('w'); break;
                case 's':
                    if(snake.GetDir() != 'w')
                        snake.ChangeDir('s'); break;
                case 'a':
                    if(snake.GetDir() != 'd')
                        snake.ChangeDir('a'); break;
                case 'd':
                    if(snake.GetDir() != 'a')
                        snake.ChangeDir('d'); break;
            }
        }

        if (snake.collided())
            gameOver = true;

        if (snake.eaten(food.GetPos())){
            food.GenFood();
            snake.Grow();
        }

        snake.MoveSnake();

        usleep(70000);
        system("clear");
    }
}

int main(){
    Food food;
    Snake snake({WIDTH/2, HEIGHT/2}, 1);
    std::cout << "Press any key to start game...";
    while(!kbhit()) { std::cout << ""; }
    sleep(1);
    while(true){
        system("clear");
        game(food, snake);
        std::cout << "Press any key to restart...";
        while(!kbhit()){    }
        sleep(1);
        continue;
    }
}
