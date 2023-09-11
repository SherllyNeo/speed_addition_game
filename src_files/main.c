#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <raylib.h>
#include <unistd.h>

#include "config.h"

#define FPS 100

int font_size(int scale) {
    return GetScreenWidth() / 100 * scale;
}

typedef enum {
    START,
    PLAY,
    FIN
} Game_Stage;

void start_game(Game_Stage *current_stage) {
    BeginDrawing();
    ClearBackground(BEIGE);
    int text_size = MeasureText("Press enter to begin!", font_size(5));
    DrawText("Press enter to begin!", (GetScreenWidth()  - text_size) / 2, GetScreenHeight() / 2, font_size(5), BLACK);
    if (IsKeyPressed(KEY_ENTER)) {
        *current_stage = PLAY;
        EndDrawing();
        return;
    }
    EndDrawing();
}

int play(Game_Stage *current_stage) {
    int total = 0;
    for (int i = 0; i<AMOUNT_OF_NUMBERS; i++) {
        int random_number = rand() % 10;
        random_number = rand() & 1 ? random_number : random_number * -1;
        total += random_number;
        char random_number_text[50]; 
        sprintf(random_number_text,"%d",random_number);
        int text_size = MeasureText(random_number_text, font_size(20));
        BeginDrawing();
        ClearBackground(BEIGE);
        EndDrawing();
        usleep(100000);
        BeginDrawing();
        ClearBackground(BEIGE);
        DrawText(random_number_text, (GetScreenWidth() - text_size) / 2, GetScreenHeight() / 2, font_size(20), BLACK);
        EndDrawing();
        sleep(60 / BPM);
    }
    BeginDrawing();
    ClearBackground(BEIGE);
    EndDrawing();

    *current_stage = FIN;
    return total;
}

void finish_game(Game_Stage *current_stage, int total) {
        BeginDrawing();
        ClearBackground(BEIGE);
        char* ending_text = "Please type in the total: ";
        int text_size = MeasureText(ending_text, font_size(20));
        DrawText(ending_text, (GetScreenWidth() - text_size) / 2, GetScreenHeight() / 2, font_size(20), BLACK);
        EndDrawing();

}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int init_width = 700;
    int init_height = 700;
    Game_Stage current_stage = START;
    int total;

    InitWindow(init_width, init_height,"numbers game");

    SetTargetFPS(FPS);
    while (!WindowShouldClose()) {
        ClearBackground(BEIGE);
        switch(current_stage) {
            case START: start_game(&current_stage); break;
            case PLAY: total = play(&current_stage); break;
            case FIN: finish_game(&current_stage,total); break;
            default: start_game(&current_stage); break;
        };


    }


    return EXIT_SUCCESS;
}
