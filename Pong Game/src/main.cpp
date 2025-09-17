    /******Step to Make a Pong Game *********/
    // Step 1: Setup the Window    
    // Step 2: Create the Ball
    // Step 3: Create the Paddles
    // Step 4: Move the Paddles
    // Step 5: Move the Ball
    // Step 6: Collisions
    // Step 7: Scoring  
    // Step 8:Win/Loss

    #include <iostream>
    #include <raylib.h>
    using namespace std;

// AAA Style Colors
    Color Background_Top    = Color{15, 32, 39, 255};   // #0f2027 deep navy
    Color Background_Mid    = Color{32, 58, 67, 255};   // #203a43 teal-dark
    Color Background_Bottom = Color{44, 83, 100, 255};  // #2c5364 blue-gray
    Color Paddle_Left  = Color{0, 255, 247, 255};   // #00fff7 neon cyan
    Color Paddle_Right = Color{255, 0, 127, 255};   // #ff007f neon magenta
    Color Ping_Ball         = Color{255, 106, 0, 255};   // #ff6a00 neon orange
    Color Score_Text   = Color{255, 255, 255, 255}; // pure white

    int LeftPaddleScore=0;
    int RightPaddleScore=0;
    const int WinningScore=7;
    bool GameOver=false;

    class Ball
    {
    public:
            float PosX;
            float PosY;
            float SpeedX;
            float SpeedY;
            float Radius;
            void ResetBall()
            {
                PosX=GetScreenWidth()/2;
                PosY=GetScreenHeight()/2;

                int Speed_Choice[2]={-1,1};
                SpeedX *=Speed_Choice[GetRandomValue(0,1)];
                SpeedY *=Speed_Choice[GetRandomValue(0,1)];

            }
            void Draw()
            {
                DrawCircle(PosX,PosY,Radius,Ping_Ball);
            }
            void Updated()
            {   

                PosX+=SpeedX;
                PosY+=SpeedY;

                if(PosY+Radius >=GetScreenHeight()|| PosY-Radius <=0)
                {
                    SpeedY*=-1;
                }
                if(PosX+Radius >=GetScreenWidth()+20)
                {
                    RightPaddleScore++;
                    ResetBall();
                }
                if(PosX-Radius <=-20)
                {
                    LeftPaddleScore++;
                    ResetBall();
                }    
            }

    
    };


    class Paddle
    {
    protected:
            void LimtMovement()
            {
                if(PosY <=0)
                {
                    PosY=0;
                }
                if(PosY+PaddleHeight >=GetScreenHeight())
                {
                    PosY=GetScreenHeight()-PaddleHeight;
                }   
            }

            void LeftPowerUp()
            {
                if(IsKeyPressed(KEY_D))
                    {
                        PaddleHeight=GetScreenHeight();
                    }
                    if(IsKeyReleased(KEY_D))
                    {
                        PaddleHeight=120;
                    }
            }

            void RightPowerUp()
            {
                if(IsKeyPressed(KEY_LEFT))
                    {
                        PaddleHeight=300;
                    }
                    if(IsKeyReleased(KEY_LEFT))
                    {
                        PaddleHeight=120;
                    }
            }
    public:
            float PosX;
            float PosY;
            float SpeedY;
            float PaddleWidth;
            float PaddleHeight;
            void Draw()
            {
                DrawRectangleRounded(Rectangle{PosX,PosY,PaddleWidth,PaddleHeight},0.8,0,Paddle_Right);
            }
            void Updated(bool LeftPaddle)
            {   
                if(LeftPaddle==true)
                {
                    if (IsKeyDown(KEY_UP))   // Move paddle UP
                    {
                        PosY -= SpeedY;
                    }
                    if (IsKeyDown(KEY_DOWN))   // Move paddle DOWN
                    {
                        PosY += SpeedY;
                    }
                    RightPowerUp();
                }
                else
                {
                    if (IsKeyDown(KEY_W))   // Move paddle UP
                    {
                        PosY -= SpeedY;
                    }
                    if (IsKeyDown(KEY_S))   // Move paddle DOWN
                    {
                        PosY += SpeedY;
                    }
                    LeftPowerUp();  
                }
                
                LimtMovement();
            }
    };

    int main() 
    {   
        Ball ball;
        Paddle LeftPaddle;
        Paddle RightPaddle;

        const int ScreenWidth=1200;
        const int ScreenHeight=800;
        InitWindow(ScreenWidth,ScreenHeight,"Pong Game");
        SetTargetFPS(60);

            // Ball Variables Initialization
            ball.PosX=ScreenWidth/2;
            ball.PosY=ScreenHeight/2;
            ball.Radius=20;
            ball.SpeedX=7;
            ball.SpeedY=7;

            //Player 1 paddle Variables Initialization
            LeftPaddle.PaddleWidth=30;
            LeftPaddle.PaddleHeight=120;
            LeftPaddle.PosX=10;
            LeftPaddle.PosY=ScreenHeight/2-LeftPaddle.PaddleHeight/2;
            LeftPaddle.SpeedY=8;

            //Player 2 paddle Variables Initialization
            RightPaddle.PaddleWidth=30;
            RightPaddle.PaddleHeight=120;
            RightPaddle.PosX=ScreenWidth-RightPaddle.PaddleWidth-10;
            RightPaddle.PosY=ScreenHeight/2-RightPaddle.PaddleHeight/2;
            RightPaddle.SpeedY=8;


while (!WindowShouldClose())
{
    BeginDrawing();
    ClearBackground(Background_Top);

    if (!GameOver)
    {
        // --------------------
        // Update game objects
        // --------------------
        ball.Updated();
        LeftPaddle.Updated(false);
        RightPaddle.Updated(true);

        
        // --------------------
        // Collisions
        // --------------------
        if (CheckCollisionCircleRec(Vector2{ball.PosX, ball.PosY}, ball.Radius,
            Rectangle{LeftPaddle.PosX, LeftPaddle.PosY, LeftPaddle.PaddleWidth, LeftPaddle.PaddleHeight}))
        {
            ball.SpeedX *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.PosX, ball.PosY}, ball.Radius,
            Rectangle{RightPaddle.PosX, RightPaddle.PosY, RightPaddle.PaddleWidth, RightPaddle.PaddleHeight}))
        {
            ball.SpeedX *= -1;
        }



        // --------------------
        // Drawing game objects
        // --------------------
        DrawRectangle(0, 0, ScreenWidth/2, ScreenHeight, Background_Mid);
        DrawCircle(ScreenWidth/2, ScreenHeight/2, 120, Background_Bottom);
        DrawLine(ScreenWidth/2, 0, ScreenWidth/2, ScreenHeight, WHITE);
        DrawText(TextFormat("%i", RightPaddleScore), ScreenWidth/4-20, 20, 80, Score_Text);
        DrawText(TextFormat("%i", LeftPaddleScore), 3*ScreenWidth/4-20, 20, 80, Score_Text);

        ball.Draw();
        LeftPaddle.Draw();
        RightPaddle.Draw();



        // --------------------
        // Check Win Condition
        // --------------------
        if (LeftPaddleScore >= WinningScore || RightPaddleScore >= WinningScore)
        {
            GameOver = true;
        }
    }
    else
    {
        // --------------------
        // Game Over Screen
        // --------------------        
        if(LeftPaddleScore>=WinningScore)
        {
           DrawText("LEFT PLAYER WINS!", ScreenWidth/2 - 250, ScreenHeight/2 - 50, 50, Score_Text);
        }
        else
        {
            DrawText("RIGHT PLAYER WINS!", ScreenWidth/2 - 250, ScreenHeight/2 - 50, 50, Score_Text);
        }

        DrawText("Press ENTER to Restart", ScreenWidth/2 - 200, ScreenHeight/2 + 50, 30, Score_Text);

        if (IsKeyPressed(KEY_ENTER))
        {
            LeftPaddle.PaddleWidth=30;
            LeftPaddle.PaddleHeight=120;
            LeftPaddle.PosX=10;
            LeftPaddle.PosY=ScreenHeight/2-LeftPaddle.PaddleHeight/2;
            LeftPaddle.SpeedY=8;

            //Player 2 paddle Variables Initialization
            RightPaddle.PaddleWidth=30;
            RightPaddle.PaddleHeight=120;
            RightPaddle.PosX=ScreenWidth-RightPaddle.PaddleWidth-10;
            RightPaddle.PosY=ScreenHeight/2-RightPaddle.PaddleHeight/2;
            RightPaddle.SpeedY=8;


            LeftPaddleScore = 0;
            RightPaddleScore = 0;
            ball.ResetBall();
            GameOver = false;
        }
    }

    EndDrawing();
}

}