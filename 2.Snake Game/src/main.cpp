/****** Steps to Make a Snake Game *********/
//Step 1: Setup the Window
//Step 2: Create the Snake
//Step 3: Create the Food
//Step 4: Move the Snake (direction control)
//Step 5: Grow the Snake when eating food
//Step 6: Handle Collisions (wall & self)
//Step 7: Add Scoring System
//Step 8: Win/Loss Condition
//Step 9: Game Loop (update & render)

#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define CELL 20            //macro  "repacle CELL with 20 vaule "
#define COLS 40            //macro
#define ROWS 30            //macro 

typedef struct { int x, y; } Cell;

int main() {
    InitWindow(COLS*CELL, ROWS*CELL, "Simple Snake with Score + Retry");
    SetTargetFPS(10);
    srand(time(NULL));

    // Snake  Varabiles setup
    Cell snake[100];
    int len;
    int dirX, dirY;
    Cell food;
    int score;
    bool gameOver;

    //reset the game
    auto reset = [&](){
        len = 3;
        snake[0] = (Cell){20, 15};
        snake[1] = (Cell){19, 15};
        snake[2] = (Cell){18, 15};
        dirX = 1; dirY = 0;
        food = (Cell){ rand()%COLS, rand()%ROWS };
        score = 0;
        gameOver = false;
    };

    reset();

    while (!WindowShouldClose()) {
        // Input
        if (IsKeyPressed(KEY_UP) && dirY==0)   { dirX=0; dirY=-1; }
        if (IsKeyPressed(KEY_DOWN) && dirY==0) { dirX=0; dirY=1; }
        if (IsKeyPressed(KEY_LEFT) && dirX==0) { dirX=-1; dirY=0; }
        if (IsKeyPressed(KEY_RIGHT) && dirX==0){ dirX=1; dirY=0; }

        if (gameOver && IsKeyPressed(KEY_ENTER)) {
            reset();
        }

        if (!gameOver) {
            // Move snake
            for (int i=len; i>0; i--) snake[i]=snake[i-1];
            snake[0].x += dirX;
            snake[0].y += dirY;

            // Check wall collision
            if (snake[0].x<0 || snake[0].x>=COLS || snake[0].y<0 || snake[0].y>=ROWS) gameOver = true;

            // Check self collision
            for (int i=1;i<len;i++) 
                if (snake[0].x==snake[i].x && snake[0].y==snake[i].y) gameOver=true;

            // Eat food
            if (!gameOver && snake[0].x==food.x && snake[0].y==food.y) {
                len++;
                score += 10;
                food.x = rand()%COLS;
                food.y = rand()%ROWS;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(food.x*CELL, food.y*CELL, CELL, CELL, RED);
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);
        for (int i=0; i<len; i++)
        {
            DrawRectangle(snake[i].x*CELL, snake[i].y*CELL, CELL, CELL, GREEN);
        }
        // Game over text
        if (gameOver) {
            DrawText("GAME OVER", 200, 200, 40, MAROON);
            DrawText("Press ENTER to Retry", 200, 250, 20, DARKGRAY);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
