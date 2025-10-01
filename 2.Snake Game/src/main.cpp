#include <raylib.h>
#include <deque>
#include <cstdlib>
#include <ctime>

const int screenWidth = 800;
const int screenHeight = 600;
const int cellSize = 20;
const int cols = screenWidth / cellSize;
const int rows = screenHeight / cellSize;

struct Segment {
    int x, y;
};

std::deque<Segment> snake;
Segment food;
int dirX = 1, dirY = 0;
bool gameOver = false;

// Reset game 
void ResetGame() {
    snake.clear();
    snake.push_back({cols / 2, rows / 2});
    dirX = 1; dirY = 0;
    food = { rand() % cols, rand() % rows };
    gameOver = false;
}


void UpdateSnake() {
    
    Segment newHead = { snake.front().x + dirX, snake.front().y + dirY };
    if (newHead.x < 0) newHead.x = cols - 1;
    if (newHead.x >= cols) newHead.x = 0;
    if (newHead.y < 0) newHead.y = rows - 1;
    if (newHead.y >= rows) newHead.y = 0;
    for (auto &seg : snake) {
        if (seg.x == newHead.x && seg.y == newHead.y) {
            gameOver = true;
            return;
        }
    }

    snake.push_front(newHead);
    if (newHead.x == food.x && newHead.y == food.y) {
        food = { rand() % cols, rand() % rows }; 
    } else {
        snake.pop_back(); 
    }
}


int main() {
    InitWindow(screenWidth, screenHeight, "Snake Game - Raylib");
    SetTargetFPS(10); 

    srand(time(0));
    ResetGame();

    while (!WindowShouldClose()) {
        // Controls
        if (IsKeyDown(KEY_W) && dirY != 1) { dirX = 0; dirY = -1; }
        if (IsKeyDown(KEY_S) && dirY != -1) { dirX = 0; dirY = 1; }
        if (IsKeyDown(KEY_A) && dirX != 1) { dirX = -1; dirY = 0; }
        if (IsKeyDown(KEY_D) && dirX != -1) { dirX = 1; dirY = 0; }

        if (!gameOver) {
            UpdateSnake();
        } else if (IsKeyPressed(KEY_ENTER)) {
            ResetGame();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(food.x * cellSize, food.y * cellSize, cellSize, cellSize, RED);
        for (auto &seg : snake) {
            DrawRectangle(seg.x * cellSize, seg.y * cellSize, cellSize, cellSize, GREEN);
        }
        if (gameOver) {
            DrawText("GAME OVER! Press Enter to Restart", screenWidth/2 - 160, screenHeight/2, 20, WHITE);
        }
            EndDrawing();
        }

    CloseWindow();
    return 0;
}