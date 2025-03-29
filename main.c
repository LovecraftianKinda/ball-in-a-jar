#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define FPS 144
#define ScreenWidth 1280
#define ScreenHeight 720
typedef struct
{
    Vector2 BallPosition;
    Vector2 BallVelocity;
    double BallRadius;
    Color BallColor;
} Ball;

void UpdateBall(Ball *Ball, const float DeltaTime);
void UpdateJar(Rectangle *Jar, Vector2 *JarVelocity, const float DeltaTime);

Color RandomColor()
{
    return (Color){rand() % 256, rand() % 256, rand() % 256, 255};
}

const double JarThickness = 10.0f;
const Color JarColor = GRAY;
const double JarWidth = 200;
const double JarHeight = 400;
const double damping = 0.8f;
const Vector2 Gravity = {0.0f, +4000.0f};
Rectangle Jar = {(ScreenWidth - JarWidth) / 2.0f, (ScreenHeight - JarHeight) / 2.0f, JarWidth, JarHeight};
Vector2 JarVelocity = {0.0f, 0.0f};

int main()
{
    Ball BallA = {{ScreenWidth / 2.0f, ScreenHeight / 2.0f}, {4000.0f, -4000.0f}, 30.0f, RandomColor()};

    InitWindow(ScreenWidth, ScreenHeight, "Ball in a jar");

    SetTargetFPS(FPS);
    srand(time(NULL));

    while (!WindowShouldClose())
    {
        const double DeltaTime = GetFrameTime();

        UpdateJar(&Jar, &JarVelocity, DeltaTime);
        UpdateBall(&BallA, DeltaTime);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircleV(BallA.BallPosition, BallA.BallRadius, BallA.BallColor);
        DrawCircleLines(BallA.BallPosition.x, BallA.BallPosition.y, BallA.BallRadius, GRAY);

        DrawRectangleLinesEx(Jar, JarThickness, JarColor);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void UpdateBall(Ball *Ball, const float DeltaTime)
{
    Ball->BallVelocity.y += Gravity.y * DeltaTime;
    Ball->BallVelocity.x += Gravity.x * DeltaTime;
    Ball->BallPosition.x += Ball->BallVelocity.x * DeltaTime;
    Ball->BallPosition.y += Ball->BallVelocity.y * DeltaTime;

    if (Ball->BallPosition.y + Ball->BallRadius + JarThickness > JarHeight + Jar.y)
    {
        Ball->BallPosition.y = JarHeight + Jar.y - Ball->BallRadius - JarThickness;
        Ball->BallVelocity.y = -Ball->BallVelocity.y * damping;
        Ball->BallColor = RandomColor();
    }
    if (Ball->BallPosition.y - Ball->BallRadius - JarThickness < Jar.y)
    {
        Ball->BallPosition.y = Jar.y + Ball->BallRadius + JarThickness;
        Ball->BallVelocity.y = -Ball->BallVelocity.y * damping;
        Ball->BallColor = RandomColor();
    }
    if (Ball->BallPosition.x + Ball->BallRadius + JarThickness > JarWidth + Jar.x)
    {
        Ball->BallPosition.x = JarWidth + Jar.x - Ball->BallRadius - JarThickness;
        Ball->BallVelocity.x = -Ball->BallVelocity.x * damping;
        Ball->BallColor = RandomColor();
    }
    if (Ball->BallPosition.x - Ball->BallRadius - JarThickness < Jar.x)
    {
        Ball->BallPosition.x = Jar.x + Ball->BallRadius + JarThickness;
        Ball->BallVelocity.x = -Ball->BallVelocity.x * damping;
        Ball->BallColor = RandomColor();
    }
}

void UpdateJar(Rectangle *Jar, Vector2 *JarVelocity, const float DeltaTime)
{
    Jar->x += JarVelocity->x * DeltaTime;
    Jar->y += JarVelocity->y * DeltaTime;

    if (Jar->x + JarThickness + Jar->width > ScreenWidth)
    {
        Jar->x = ScreenWidth - JarThickness - Jar->width;
        JarVelocity->x = -JarVelocity->x;
    }
    if (Jar->x - JarThickness < 0.0f)
    {
        Jar->x = JarThickness;
        JarVelocity->x = -JarVelocity->x;
    }
    if (Jar->y + JarThickness + Jar->height > ScreenHeight)
    {
        Jar->y = ScreenHeight - JarThickness - Jar->height;
        JarVelocity->y = -JarVelocity->y;
    }
    if (Jar->y - JarThickness < 0.0f)
    {
        Jar->y = JarThickness;
        JarVelocity->y = -JarVelocity->y;
    }
}