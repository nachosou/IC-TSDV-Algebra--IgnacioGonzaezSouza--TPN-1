#include <iostream>
#include "raylib.h"
#include <vector>

using namespace std;

struct line
{
    Vector2 start;
    Vector2 end;
};

void ballMovement(float& ballX, float& ballY, int speed);
bool colLineLine(line line, vector<Vector2> vector);

int main(void)
{
    InitWindow(1366, 768, "raylib [core] example - basic window");

    float ballX = 75;
    float ballY = 150;
    int speed = 1200;
    int ballSpeed = 600;
    Color ballColor = RED;

    vector <Vector2> Mouse;

    line right;
    line left;
    line up;
    line down;

    while (!WindowShouldClose())
    {
        ballMovement(ballX, ballY, speed);

        right.start.x = ballX;  //genera la linea desde la pelota hasta el final de la pantalla hasta la derecha
        right.start.y = ballY;
        right.end.x = GetScreenWidth();
        right.end.y = ballY;

        left.start.x = 0;   //genera la linea desde la pelota hasta el final de la pantalla hasta la izquierda
        left.start.y = ballY;
        left.end.x = ballX;
        left.end.y = ballY;

        up.start.x = ballX;    //genera la linea desde la pelota hasta el final de la pantalla hasta arriba
        up.start.y = 0;
        up.end.x = ballX;
        up.end.y = ballY;

        down.start.x = ballX;    //genera la linea desde la pelota hasta el final de la pantalla hasta abajo
        down.start.y = ballY;
        down.end.x = ballX;
        down.end.y = GetScreenHeight();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) //agrego la pos del mouse y se toca el boton iz
        {
            Mouse.push_back(GetMousePosition());
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) // se borra lo dibujado
        {
            Mouse.clear();
        }

        if (colLineLine(right, Mouse) && colLineLine(left, Mouse) && colLineLine(down, Mouse) && colLineLine(up, Mouse)) //si en todas las dirc las lineas se cortan existe colicion
        {
            ballColor = BLUE;
        }
        else
        {
            ballColor = RED;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircle(ballX, ballY, 25, ballColor);

        if (Mouse.size() > 1)
        {
            for (int j = 1; j != Mouse.size(); j++)
            {
                DrawLine(Mouse[j - 1].x, Mouse[j - 1].y, Mouse[j].x, Mouse[j].y, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void ballMovement(float& ballX, float& ballY, int speed)// movimiento de la pelota
{
    if (IsKeyDown(KEY_W))
    {
        if (ballY >= 0 + 25)
        {
            ballY -= speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_S))
    {
        if (ballY <= 768 - 25)
        {
            ballY += speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_A))
    {
        if (ballX >= 0 + 25)
        {
            ballX -= speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_D))
    {
        if (ballX <= 1366 - 25)
        {
            ballX += speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_UP))
    {
        if (ballY >= 0 + 25)
        {
            ballY -= speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_DOWN))
    {
        if (ballY <= 768 - 25)
        {
            ballY += speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_LEFT))
    {
        if (ballX >= 0 + 25)
        {
            ballX -= speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        if (ballX <= 1366 - 25)
        {
            ballX += speed * GetFrameTime();
        }
    }
}

//http://www.jeffreythompson.org/collision-detection/line-line.php
//calcula si las lineas se cortan
bool colLineLine(line line, vector<Vector2> vector)
{
    float a;
    float b;

    if (vector.size() > 4)
    {
        for (int i = 1; i != vector.size(); i++)
        {
            a = (((vector[i].x - vector[i - 1].x) * (line.start.y - vector[i - 1].y)) - ((vector[i].y - vector[i - 1].y) * (line.start.x - vector[i - 1].x)))
                / (((vector[i].y - vector[i - 1].y) * (line.end.x - line.start.x)) - ((vector[i].x - vector[i - 1].x) * (line.end.y - line.start.y)));

            b = ((line.end.x - line.start.x) * (line.start.y - vector[i - 1].y) - (line.end.y - line.start.y) * (line.start.x - vector[i - 1].x))
                / (((vector[i].y - vector[i - 1].y) * (line.end.x - line.start.x)) - ((vector[i].x - vector[i - 1].x) * (line.end.y - line.start.y)));

            if (a >= 0 && a <= 1 && b >= 0 && b <= 1)
            {
                return true;
            }

        }
        return false;
    }
}