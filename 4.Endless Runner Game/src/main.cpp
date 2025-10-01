#include<raylib.h>

int main()
{
    const int ScreenWidth=1200;
    const int ScreenHeight=700;
    InitWindow(ScreenWidth,ScreenHeight,"EndlessRunner");
    SetTargetFPS(60);

    //Rectange Dimension
    const int RecWidth{50};
    const int RecHeight{80};
    int posY{GetScreenHeight()-RecHeight};
    int Velocity{0};

    //Main Loop
    while (WindowShouldClose()==false)
    {
        BeginDrawing();
        ClearBackground(GREEN);
        
        if(IsKeyPressed(KEY_SPACE))
        {
            Velocity-=10;
        }
        posY+=Velocity;

        DrawRectangle(GetScreenWidth()/2,posY,RecWidth,RecHeight,BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}