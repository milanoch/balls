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

class Figure {
public:
    virtual ~Figure() = default;
    virtual void update() = 0;
};

class RectangleFigure : public Figure {
public:
    RectangleFigure(Vector2 _pos) {
        velocity = {(rand() % 100 - 50.f), (rand() % 100 - 50.f)};
        size = {
                static_cast<float>(rand() % 20),
                static_cast<float>(rand() % 20)
        };
        color = {
                static_cast<unsigned char>(rand() % 256),
                static_cast<unsigned char>(rand() % 256),
                static_cast<unsigned char>(rand() % 256),
                255
        };
        pos = _pos;
    }

    void update() override {
        pos.x += velocity.x * GetFrameTime();
        pos.y += velocity.y * GetFrameTime();
        DrawRectangle(pos.x, pos.y, size.x, size.y, color);
    }

    Vector2 velocity;
    Vector2 pos;
    Color color;
    Vector2 size;
};

class TriangleFigure : public Figure {
public:
    TriangleFigure(Vector2 _pos) {
        velocity = {(rand() % 100 - 50.f), (rand() % 100 - 50.f)};
        pos = _pos;
        color = {
                static_cast<unsigned char>(rand() % 256),
                static_cast<unsigned char>(rand() % 256),
                static_cast<unsigned char>(rand() % 256),
                255
        };
        size = {
                static_cast<float>(rand() % 10),
                static_cast<float>(rand() % 10)
        };
    }

    void update() override {
        pos.x += velocity.x * GetFrameTime();
        pos.y += velocity.y * GetFrameTime();

        Vector2 a;
        a.x = pos.x;
        a.y = pos.y - 10;

        Vector2 b;
        b.x = pos.x - size.x;
        b.y = pos.y + size.y;

        Vector2 c;
        c.x = pos.x + size.x;
        c.y = pos.y + size.y;

        DrawTriangle(a, b, c, color);
    }

    Vector2 velocity;
    Vector2 pos;
    Color color;
    Vector2 size;
};

class CircleFigure : public Figure {
public:
    CircleFigure(Vector2 _pos) {
        velocity = {(rand() % 100 - 50.f), (rand() % 100 - 50.f)};
        pos = _pos;
        color = {
                static_cast<unsigned char>(rand() % 256),
                static_cast<unsigned char>(rand() % 256),
                static_cast<unsigned char>(rand() % 256),
                255
        };
        size = rand() % 30;
    }

    void update() override {
        pos.x += velocity.x * GetFrameTime();
        pos.y += velocity.y * GetFrameTime();
        DrawCircle(pos.x, pos.y, size, color);
    }

    Vector2 velocity;
    Vector2 pos;
    Color color;
    int size;
};

int main() {
    const int MAX_FIGURES = 100;
    std::srand(std::time(nullptr));
    FigureType state = FigureType::CIRCLE;
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, ".");
    SetTargetFPS(60);
    std::vector<Figure *> figures;
    float drawDelay = 0.f;
    // MAIN LOOP BEGIN
    while (!WindowShouldClose()) {
        BeginDrawing();
        drawDelay -= GetFrameTime();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && drawDelay <= 0.f) {
            Vector2 pos = GetMousePosition();
            if (state == FigureType::CIRCLE) {
                figures.push_back(new CircleFigure(pos));
                state = FigureType::TRIANGLE;
            } else if (state == FigureType::TRIANGLE) {
                figures.push_back(new TriangleFigure(pos));
                state = FigureType::SQUARE;
            } else if (state == FigureType::SQUARE) {
                figures.push_back(new RectangleFigure(pos));
                state = FigureType::CIRCLE;
            }
            if (figures.size() >= MAX_FIGURES) {
                delete figures[0];
                figures.erase(figures.begin());
            }
            drawDelay = 0.02f;
        }
        for (Figure *figure: figures) {
            figure->update();
        }
        DrawFPS(50, 50);
        ClearBackground(BLACK);
        EndDrawing();
    }
    // MAIN LOOP END
    for (Figure *figure: figures) {
        delete figure;
    }
    CloseWindow();
    return 0;
}

