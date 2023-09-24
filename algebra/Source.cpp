#include <iostream>
#include <vector>
#include "raylib.h"

using namespace std;

void ballMovement(Vector2& ball, int ballSpeed, int ballRadius);
bool ballInPoly(Vector2 ball, vector <Vector2> mouse);

void main()
{
    InitWindow(1366, 768, "raylib [core] example - basic window");

    Vector2 ball;
    ball.x = 75;
    ball.y = 150;
    int ballRadius = 25;
    Color ballColor;
    int ballSpeed = 1200;

    vector <Vector2> mouse; //"array dinamico" de vectores
    
    SetTargetFPS(144);

    while (!WindowShouldClose())
    {
        ballMovement(ball, ballSpeed, ballRadius);

        bool isInPoly = false;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) //toma el click del mouse para aumentar el "array dinamico" de vectores
        {
            mouse.push_back(GetMousePosition());
        }

        if (mouse.size() > 2)  //si son mas de 2 lados se puede generar el poligono
        {
            isInPoly = ballInPoly(ball, mouse);
        }

        if (isInPoly) //cambia el color de la pelota dependiendo de si esta adentro o no del poligono
        {
            ballColor = BLUE;
        }
        else
        {
            ballColor = RED;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawCircle(ball.x, ball.y, ballRadius, ballColor);

        if (mouse.size() > 1) //dibuja las lineas 
        {
            for (int j = 1; j != mouse.size(); j++)
            {
                DrawLine(mouse[j - 1].x, mouse[j - 1].y, mouse[j].x, mouse[j].y, WHITE);
            }
        }
        EndDrawing();
    }

    CloseWindow();
}

//Movimiento de la pelota
void ballMovement(Vector2& ball, int ballSpeed, int ballRadius) 
{
    if (IsKeyDown(KEY_W))
    {
        if (ball.y >= 0 + ballRadius)
        {
            ball.y -= ballSpeed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_S))
    {
        if (ball.y <= GetScreenHeight() - ballRadius)
        {
            ball.y += ballSpeed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_A))
    {
        if (ball.x >= 0 + ballRadius)
        {
            ball.x -= ballSpeed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_D))
    {
        if (ball.x <= GetScreenWidth() - ballRadius)
        {
            ball.x += ballSpeed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_UP))
    {
        if (ball.y >= 0 + ballRadius)
        {
            ball.y -= ballSpeed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_DOWN))
    {
        if (ball.y <= GetScreenHeight() - ballRadius)
        {
            ball.y += ballSpeed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_LEFT))
    {
        if (ball.x >= 0 + ballRadius)
        {
            ball.x -= ballSpeed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        if (ball.x <= GetScreenWidth() - ballRadius)
        {
            ball.x += ballSpeed * GetFrameTime();
        }
    }
} 

bool ballInPoly(Vector2 ball, vector <Vector2> mouse)  //chequea si esta adentro o no del poligono
{
    int raycastXD = 0;

    for (int i = 0, j = mouse.size() - 1; i < mouse.size(); j = i++)
    {
        if ((mouse[i].y > ball.y) != (mouse[j].y > ball.y) &&
            (ball.x < (mouse[j].x - mouse[i].x) * (ball.y - mouse[i].y) / (mouse[j].y - mouse[i].y) + mouse[i].x))
        {
            raycastXD++;
        }
    }

    return (raycastXD % 2 == 1);
}