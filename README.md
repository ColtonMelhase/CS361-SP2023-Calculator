# CS361-SP2023-Calculator

## Helpful links
- [raylib examples - lots of interactive examples with code](https://www.raylib.com/examples.html)
- [raylib cheatsheet - list and explains everything in raylib](https://www.raylib.com/cheatsheet/cheatsheet.html)
- [setup raylib windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows)
- [setup raylib macOS](https://github.com/raysan5/raylib/wiki/Working-on-macOS)

## Bare minimum raylib example
```cpp
#include "raylib.h"

int main() {
    InitWindow(800, 450, "title");
    SetTargetFPS(60);

    // initialization done here

    while(!WindowShouldClose()) {

        // get inputs, detect button presses and do calculations here
        // e.g. CheckCollisionPointRec(GetMousePosition(), Rectangle{400,225,100,24});

        BeginDrawing();
        ClearBackground(WHITE);
        
        // draw things here
        // e.g. DrawText("Hello World", 400, 225, 24, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```
