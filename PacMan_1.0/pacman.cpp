#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;
const char PACMAN = 'P';
const char WALL = '#';
const char POINT = '.';
const char OBSTACLE = 'X';
const char REWARD = '*';

struct Position {
    int x, y;
};

class Game {
private:
    vector<vector<char>> board;
    Position pacmanPos;
    int score;
    int lives;

public:
    Game() : score(0), lives(3) {
        board.resize(HEIGHT, vector<char>(WIDTH, ' '));
        initBoard();
    }

    void initBoard() {
        // Setting walls and points
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                    board[i][j] = WALL;
                else
                    board[i][j] = POINT;
            }
        }

        // Adding Pac-Man
        pacmanPos = { WIDTH / 2, HEIGHT / 2 };
        board[pacmanPos.y][pacmanPos.x] = PACMAN;

        // Adding obstacles and rewards
        srand(time(0));
        for (int i = 0; i < 10; i++) {
            int x = rand() % (WIDTH - 2) + 1;
            int y = rand() % (HEIGHT - 2) + 1;
            board[y][x] = (i % 2 == 0) ? OBSTACLE : REWARD;
        }
    }

    void displayBoard() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                cout << board[i][j] << ' ';
            }
            cout << endl;
        }
        cout << "Score: " << score << " | Lives: " << lives << endl;
    }

    void movePacman(char direction) {
        int newX = pacmanPos.x;
        int newY = pacmanPos.y;

        switch (direction) {
            case 'w': newY--; break;
            case 's': newY++; break;
            case 'a': newX--; break;
            case 'd': newX++; break;
            default: return;
        }

        if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT || board[newY][newX] == WALL) {
            cout << "Bumped into a wall!" << endl;
            return;
        }

        if (board[newY][newX] == POINT) {
            score += 10;
        } else if (board[newY][newX] == OBSTACLE) {
            lives--;
            cout << "Hit an obstacle! Lives left: " << lives << endl;
            if (lives <= 0) {
                cout << "Game Over!" << endl;
                exit(0);
            }
        } else if (board[newY][newX] == REWARD) {
            score += 50;
            cout << "Found a reward!" << endl;
        }

        board[pacmanPos.y][pacmanPos.x] = ' ';
        pacmanPos = { newX, newY };
        board[pacmanPos.y][pacmanPos.x] = PACMAN;
    }

    void play() {
        char input;
        while (true) {
            displayBoard();
            cout << "Move (w/a/s/d): ";
            cin >> input;
            movePacman(input);
        }
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
