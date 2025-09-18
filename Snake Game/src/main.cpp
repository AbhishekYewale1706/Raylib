
#include<iostream>
#include<raylib.h>

const int CellSize=30;
const int CellCount=25;

class Food
{
public:
        Vector2 Position={5,6};
        Texture2D texture;

        Food()//Constructor
        {
            Image image=LoadImage("Image/food.png");
            texture=LoadTextureFromImage(image);
            UnloadImage(image);
        }
        ~Food()//Destructor
        {
            UnloadTexture(texture);
        }
        void Draw()
        {
           DrawTexture(texture,Position.x*CellSize,Position.y*CellSize,WHITE);
        }

};

int main()
{
    
    //Window Setup
    InitWindow(CellSize*CellCount,CellSize*CellCount,"Snake Game");
    SetTargetFPS(60);

    Food food=Food();

    while (WindowShouldClose()==false)
    {
        BeginDrawing();
        ClearBackground(GREEN);
        //Event Handling
        //Updated
        //Draw
        food.Draw();
        EndDrawing();
    }
  
    CloseWindow();
    return 0;
}
