#include "raylib.h"

int main() {
    // Window setup
    InitWindow(800, 450, "Simple 2D Endless Runner");
    SetTargetFPS(60);

    // Player variables
    float playerX = 100;
    float playerY = 300;
    float playerWidth = 50;
    float playerHeight = 50;
    float velocityY = 0;
    float gravity = 0.5;
    bool onGround = true;

    // Obstacle variables
    float obsX = 800;
    float obsY = 300;
    float obsWidth = 50;
    float obsHeight = 50;
    float speed = 5;

    int score = 0;

    while (!WindowShouldClose()) {
        
        // Player Input
        if (IsKeyPressed(KEY_SPACE) && onGround) {
            velocityY = -12;
            onGround = false;
        }

        velocityY += gravity;
        playerY += velocityY;

        if (playerY >= 300) {
            playerY = 300;
            velocityY = 0;
            onGround = true;
        }

        // Move obstacle
        obsX -= speed;
        if (obsX < -obsWidth) obsX = 800;

        // Collision
        if (playerX < obsX + obsWidth && playerX + playerWidth > obsX &&
            playerY < obsY + obsHeight && playerY + playerHeight > obsY) {
            //Game Over start again
            playerY = 300;
            velocityY = 0;
            obsX = 800;
            score = 0;
        }

        score++;

        // Start Drawing
        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawRectangle(0, 350, 800, 100, GREEN);
        DrawRectangle(playerX, playerY, playerWidth, playerHeight, BLUE);
        DrawRectangle(obsX, obsY, obsWidth, obsHeight, RED);
        DrawText(TextFormat("Score: %d", score / 10), 10, 10, 20, BLACK);
        //End Drawing
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
