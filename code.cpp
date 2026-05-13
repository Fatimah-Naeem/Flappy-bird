#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

// Constants for screen dimensions
const int SCREEN_WIDTH = 30;
const int SCREEN_HEIGHT = 20;
const int NUM_PIPES = 3; // Number of pipes on the screen at once

// Game State Variables
bool isRunning = true;

// Bird Position
int birdY = SCREEN_HEIGHT / 2;
const int birdX = SCREEN_WIDTH / 4;           

// Pipes
int pipeX[NUM_PIPES];        // Horizontal positions of pipes
int pipeY[NUM_PIPES];        // Top of the gap for each pipe
const int pipeGap = 5;       // Gap size for the bird to pass through

// Score Variable
int score = 0;

// Function Prototypes
void initializeGame();
void handleInput();
void updateGame();
void renderGame();
void endGame();

int main() {
    initializeGame();

    while (isRunning) {
        handleInput();
        updateGame();
        renderGame();
        Sleep(100); // Adjust game speed
    }

    endGame();
    return 0;
}

void initializeGame() {
    cout << "Welcome to Console Flappy Bird!" << endl;
    cout << "Press any key to start the game." << endl;
    srand(time(0)); // Seed random numbers
    _getch(); // Wait for user input to start

    // Initialize pipe positions
    for (int i = 0; i < NUM_PIPES; ++i) {
        pipeX[i] = SCREEN_WIDTH + i * (SCREEN_WIDTH / NUM_PIPES); // Staggered positions
        pipeY[i] = rand() % (SCREEN_HEIGHT - pipeGap);           // Random gap positions
    }

    score = 0; // Initialize score to 0
}

void handleInput() {
    if (_kbhit()) {
        char key = _getch();
        if (key == ' ') {
            birdY -= 2; // Move the bird up
        }
    }
}

void updateGame() {
    // Gravity effect: bird falls
    birdY += 1;

    // Move pipes
    for (int i = 0; i < NUM_PIPES; ++i) {
        pipeX[i] -= 1; // Move pipe left

        // If the pipe goes off-screen, reset it to the right
        if (pipeX[i] < 0) {
            pipeX[i] = SCREEN_WIDTH - 1;
            pipeY[i] = rand() % (SCREEN_HEIGHT - pipeGap); // Randomize the gap
            score++; // Increment score when a pipe resets
        }
    }

    // Check for collisions
    for (int i = 0; i < NUM_PIPES; ++i) {
        if (birdX == pipeX[i] && (birdY < pipeY[i] || birdY > pipeY[i] + pipeGap)) {
            isRunning = false; // End the game if there's a collision
        }
    }

    // Boundary check for bird
    if (birdY < 0 || birdY >= SCREEN_HEIGHT) {
        isRunning = false; // End the game if the bird hits the top or bottom
    }
}

void renderGame() {
    system("cls"); // Clear the screen

    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            bool isPipe = false;

            // Check if the current position is part of any pipe
            for (int k = 0; k < NUM_PIPES; ++k) {
                if (j == pipeX[k] && (i < pipeY[k] || i > pipeY[k] + pipeGap)) {
                    cout << "|"; // Pipe
                    isPipe = true;
                    break;
                }
            }

            if (!isPipe) {
                if (i == birdY && j == birdX) {
                    cout << "00>"; // Bird
                } else {
                    cout << " "; // Empty space
                }
            }
        }
        cout << endl;
    }

    // Display the score at the bottom of the screen
    cout << "Score: " << score << endl;
}

void endGame() {
    cout << "Game Over! Thanks for playing." << endl;
    cout << "Your Final Score: " << score << endl;
}
