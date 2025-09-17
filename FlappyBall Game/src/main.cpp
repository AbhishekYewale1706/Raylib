#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define GROUND_H 80

typedef struct {
    float x, y;
    float radius;
    float velocity;
} Bird;

typedef struct {
    float x;
    float gapY;
    float width;
    float gapHeight;
    bool passed;
} Pipe;

#define PIPE_COUNT 3
static Pipe pipes[PIPE_COUNT];
static float pipeSpeed = 200.0f;
static Bird bird;
static int score;
static bool gameOver;

static void ResetGame() {
    bird.x = SCREEN_W/4;
    bird.y = SCREEN_H/2;
    bird.radius = 16;
    bird.velocity = 0;

    for (int i=0; i<PIPE_COUNT; i++) {
        pipes[i].x = SCREEN_W + i * 300;
        pipes[i].width = 60;
        pipes[i].gapHeight = 150;
        pipes[i].gapY = GetRandomValue(100, SCREEN_H - GROUND_H - 100);
        pipes[i].passed = false;
    }

    score = 0;
    gameOver = false;
}

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "Flappy Bird (raylib)");
    SetTargetFPS(60);
    srand(time(NULL));

    ResetGame();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (!gameOver) {
            // Bird physics
            bird.velocity += 800 * dt; // gravity
            bird.y += bird.velocity * dt;

            if (IsKeyPressed(KEY_SPACE)) {
                bird.velocity = -300; // jump
            }

            // Move pipes
            for (int i=0; i<PIPE_COUNT; i++) {
                pipes[i].x -= pipeSpeed * dt;

                // recycle pipe
                if (pipes[i].x + pipes[i].width < 0) {
                    pipes[i].x = SCREEN_W + 200;
                    pipes[i].gapY = GetRandomValue(100, SCREEN_H - GROUND_H - 100);
                    pipes[i].passed = false;
                }

                // check scoring
                if (!pipes[i].passed && bird.x > pipes[i].x + pipes[i].width) {
                    score++;
                    pipes[i].passed = true;
                }

                // collision check
                Rectangle topRect = { pipes[i].x, 0, pipes[i].width, pipes[i].gapY - pipes[i].gapHeight/2 };
                Rectangle bottomRect = { pipes[i].x, pipes[i].gapY + pipes[i].gapHeight/2,
                                         pipes[i].width, SCREEN_H - GROUND_H - (pipes[i].gapY + pipes[i].gapHeight/2) };
                if (CheckCollisionCircleRec((Vector2){bird.x, bird.y}, bird.radius, topRect) ||
                    CheckCollisionCircleRec((Vector2){bird.x, bird.y}, bird.radius, bottomRect)) {
                    gameOver = true;
                }
            }

            // ground or ceiling collision
            if (bird.y + bird.radius > SCREEN_H - GROUND_H || bird.y - bird.radius < 0) {
                gameOver = true;
            }
        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                ResetGame();
            }
        }

        
        BeginDrawing();
        ClearBackground(SKYBLUE);

        
        DrawRectangle(0, SCREEN_H - GROUND_H, SCREEN_W, GROUND_H, DARKGREEN);
        for (int i=0; i<PIPE_COUNT; i++) {
            DrawRectangle(pipes[i].x, 0, pipes[i].width,
                          pipes[i].gapY - pipes[i].gapHeight/2, GREEN);
            DrawRectangle(pipes[i].x, pipes[i].gapY + pipes[i].gapHeight/2,
                          pipes[i].width, SCREEN_H - GROUND_H - (pipes[i].gapY + pipes[i].gapHeight/2), GREEN);
        }

        DrawCircle((int)bird.x, (int)bird.y, bird.radius, YELLOW);
        DrawText(TextFormat("Score: %i", score), 10, 10, 30, BLACK);

        if (gameOver) {
            DrawText("GAME OVER", SCREEN_W/2 - MeasureText("GAME OVER", 40)/2, SCREEN_H/2 - 50, 40, RED);
            DrawText("Press Enter to Restart", SCREEN_W/2 - MeasureText("Press Enter to Restart", 20)/2, SCREEN_H/2 + 10, 20, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
