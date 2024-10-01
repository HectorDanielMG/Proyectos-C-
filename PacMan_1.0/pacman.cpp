#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 17;
int x, y, fruitX, fruitY, score;

void Setup() {
    gameOver = false;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    clear();
    for (int i = 0; i < width + 2; i++)
        printw("#");
    printw("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                printw("#"); // wall
            if (i == y && j == x)
                printw("O"); // Pacman
            else if (i == fruitY && j == fruitX)
                printw("F"); // fruit
            else
                printw(" ");
        }
        printw("#\n");
    }

    for (int i = 0; i < width + 2; i++)
        printw("#");
    printw("\n");
    printw("Score: %d\n", score);
    refresh();
}

void Input() {
    keypad(stdscr, TRUE);
    halfdelay(1); // Wait for 100 ms
    int c = getch();
    switch (c) {
        case 'a':
            x--;
            break;
        case 'd':
            x++;
            break;
        case 'w':
            y--;
            break;
        case 's':
            y++;
            break;
        case 'x':
            gameOver = true;
            break;
    }
}

void Logic() {
    // Wrap around
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    if (x == fruitX && y == fruitY) {
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator
    initscr(); // Start ncurses
    noecho(); // Don't echo input
    cbreak(); // Disable line buffering

    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
    }

    endwin(); // End ncurses
    return 0;
}
