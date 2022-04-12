#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x,y, fruit_X, fruit_Y, score;
int tail_X[100],tail_Y[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruit_X = rand()% width;
    fruit_Y = rand()% height;
    score = 0;
}

void Draw () {
    system("clear"); //system ("cls");
    for (int i = 0; i < width + 1; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i=0; i < height; i++) {
        for (int j=0; j < width; j++) {
            if (j == 0 || j == width - 1)
                cout << "#";
            if (i == y && j == x)
                cout << "0";
            else if (i == fruit_Y && j == fruit_X)
                cout << "F";
            else {
                bool print = false;
                for (int k; k < nTail; k++)
                {
                    if (tail_X[k] == j && tail_Y[k] == i)
                    {
                        print = true;
                        cout << "o";
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 1; i++) {
        cout << "#";
    }
    cout << endl;

    cout << "Score" << score << endl;

}

void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x': //a button for exit of the game
                gameOver = true;
                break;

        }
    }
}

void Logic() {
    int prev_X = tail_X[0];
    int prev_Y = tail_Y[0];
    int prev_2X, prev_2Y;
    tail_X[0] = x;
    tail_Y[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev_2X = tail_X[i];
        prev_2Y = tail_Y[i];
        tail_X[i] = prev_X;
        tail_Y[i] = prev_Y;

        prev_X = prev_2X;
        prev_Y = prev_2Y;
    }

    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    //if (x > width || x < 0 || y > height || y < 0)
    //    gameOver = true;
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 2;

    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

    for (int i = 0; i < nTail; i++) {
        if (tail_X[i] == x && tail_Y[i] == y)
            gameOver = true;
    }

    if (x == fruit_X && y == fruit_Y) {
        score += 10;
        fruit_X = rand()% width;
        fruit_Y = rand()% height;
        nTail++;
    }
}


int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
    }
    return 0;
}