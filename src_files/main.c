#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <raylib.h>

#include "config.h"

int font_size(int scale) {
    return GetScreenWidth() / 100 * scale;
};

int main(int argc, char *argv[])
{
    int init_width = 500;
    int init_height = 500;

    InitWindow(init_width, init_height,"numbers game");
    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawText("Press enter to begin!", GetScreenWidth() / 2, GetScreenHeight() / 2, font_size(500), BLACK);
        if (IsKeyPressed(KEY_ENTER)) {
            DrawText("5", GetScreenWidth() / 2, GetScreenHeight() / 2, font_size(500), BLACK);
        }
        EndDrawing();
    }


    return EXIT_SUCCESS;
}
