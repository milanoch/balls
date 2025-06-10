#include <iostream>
#include <raylib.h>
#include <vector>
#include <cstdlib>
#include <ctime>

enum FigureType {
    CIRCLE,
    TRIANGLE,
    SQUARE,
};

int main() {
    std::srand(std::time(nullptr));
    FigureType state = FigureType::CIRCLE;

    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, ".");

    SetTargetFPS(60);

    std::vector<Vector2> circlespos;
    std::vector<Color> circlescolor;
    std::vector<int> circlessize;

    std::vector<Vector2> trianglespos;
    std::vector<Color> trianglescolor;
    std::vector<Vector2> trianglessize;

    std::vector<Vector2> squarespos;
    std::vector<Color> squarescolor;
    std::vector<Vector2> squaressize;

    float drawDelay = 0.f;
    while (!WindowShouldClose()) {
        BeginDrawing();
        drawDelay -= GetFrameTime();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && drawDelay <= 0.f) {
            Vector2 pos = GetMousePosition();
            if (state == FigureType::CIRCLE) {
                circlespos.push_back(pos);
                circlescolor.push_back({
                    static_cast<unsigned char>(rand() % 256),
                    static_cast<unsigned char>(rand() % 256),
                    static_cast<unsigned char>(rand() % 256),
                    255
                });
                circlessize.push_back(static_cast<unsigned char>(rand() % 30));
                state = FigureType::TRIANGLE;
            } else if (state == FigureType::TRIANGLE) {
                trianglespos.push_back(pos);
                state = FigureType::SQUARE;
            } else if (state == FigureType::SQUARE) {
                squarespos.push_back(pos);
                state = FigureType::CIRCLE;
            }
            drawDelay = 0.02f;
        }
        for (int i = 0; i < circlespos.size(); i++) {
            Vector2 pos = circlespos[i];
            DrawCircle(pos.x, pos.y, circlessize[i],circlescolor[i]);
        }
        for (int i = 0; i < trianglespos.size(); i++) {
            Vector2 pos = trianglespos[i];
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
        for (int i = 0; i < squarespos.size(); i++) {
            Vector2 pos = squarespos[i];
            DrawRectangle(pos.x, pos.y, 5, 5, RED);
        }
        DrawFPS(50, 50);
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

