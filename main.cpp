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
                circlessize.push_back(rand() % 30);
                if(circlessize.size() >= 100){
                    circlessize.erase(circlessize.begin());
                    circlescolor.erase(circlescolor.begin());
                    circlespos.erase(circlespos.begin());
                }
                state = FigureType::TRIANGLE;
            } else if (state == FigureType::TRIANGLE) {
                trianglespos.push_back(pos);
                trianglescolor.push_back({
                    static_cast<unsigned char>(rand() % 256),
                    static_cast<unsigned char>(rand() % 256),
                    static_cast<unsigned char>(rand() % 256),
                    255
                });
                trianglessize.push_back({
                    static_cast<float>(rand() % 10),
                    static_cast<float>(rand() % 10)
                });
                if(trianglessize.size() >= 100){
                    trianglessize.erase(trianglessize.begin());
                    trianglespos.erase(trianglespos.begin());
                    trianglescolor.erase(trianglescolor.begin());
                }
                state = FigureType::SQUARE;
            } else if (state == FigureType::SQUARE) {
                squaressize.push_back({
                    static_cast<float>(rand() % 20),
                    static_cast<float>(rand() % 20)
                });
                squarescolor.push_back({
                    static_cast<unsigned char>(rand() % 256),
                    static_cast<unsigned char>(rand() % 256),
                    static_cast<unsigned char>(rand() % 256),
                    255
                });
                squarespos.push_back(pos);
                if(squaressize.size() >= 100){
                    squaressize.erase(squaressize.begin());
                    squarespos.erase(squarespos.begin());
                    squarescolor.erase(squarescolor.begin());
                }
                state = FigureType::CIRCLE;
            }
            drawDelay = 0.02f;
        }

        for (int i = 0; i < circlespos.size(); i++) {
            Vector2 pos = circlespos[i];
            DrawCircle(pos.x, pos.y, circlessize[i],circlescolor[i]);
        }
        for (int i = 0; i < trianglespos.size(); i++) {
            Vector2 a;
            a.x = trianglespos[i].x;
            a.y = trianglespos[i].y - 10;

            Vector2 b;
            b.x = trianglespos[i].x - trianglessize[i].x;
            b.y = trianglespos[i].y + trianglessize[i].y;

            Vector2 c;
            c.x = trianglespos[i].x + trianglessize[i].x;
            c.y = trianglespos[i].y + trianglessize[i].y;

            DrawTriangle(a, b, c,trianglescolor[i]);
        }
        for (int i = 0; i < squarespos.size(); i++) {
            Vector2 pos = squarespos[i];
            DrawRectangle(pos.x, pos.y, squaressize[i].x, squaressize[i].y, squarescolor[i]);
        }
        DrawFPS(50, 50);
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

