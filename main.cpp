#include <iostream>
#include <raylib.h>
#include <vector>

enum FigureType {
    CIRCLE,
    TRIANGLE,
    SQUARE,
};

int main() {
    FigureType state = FigureType::CIRCLE;
    srand(time(nullptr));

    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, ".");

    SetTargetFPS(60);
    std::vector<Vector2> circles;
    std::vector<Vector2> triangles;
    std::vector<Vector2> squares;
    float drawDelay = 0.f;
    while (!WindowShouldClose()) {
        BeginDrawing();
        drawDelay -= GetFrameTime();
        if (IsMouseButtonDown(0) && drawDelay <= 0.f) {
            Vector2 pos = GetMousePosition();
            if (state == FigureType::CIRCLE) {
                circles.push_back(pos);
                state = FigureType::TRIANGLE;
            } else if (state == FigureType::TRIANGLE) {
                triangles.push_back(pos);
                state = FigureType::SQUARE;
            } else if (state == FigureType::SQUARE) {
                squares.push_back(pos);
                state = FigureType::CIRCLE;
            }
            drawDelay = 0.2f;
        }
        for (int i = 0; i < circles.size(); i++) {
            Vector2 pos = circles[i];
            DrawCircle(pos.x, pos.y, 5.f, RED);
        }
        for (int i = 0; i < triangles.size(); i++) {
            Vector2 pos = triangles[i];
            Vector2 a;
            a.x = pos.x;
            a.y = pos.y - 10;

            Vector2 b;
            b.x = pos.x - 10;
            b.y = pos.y + 10;

            Vector2 c;
            c.x = pos.x + 10;
            c.y = pos.y + 10;

            DrawTriangle(a, b, c, RED);
        }
        for (int i = 0; i < squares.size(); i++) {
            Vector2 pos = squares[i];
            DrawRectangle(pos.x, pos.y, 5, 5, RED);
        }
        DrawFPS(50, 50);
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

