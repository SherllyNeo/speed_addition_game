#define _DEFAULT_SOURCE
#include <ctype.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
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
    FIN,
    RESULT
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
        if (NEGATIVES) 
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

bool finish_game(Game_Stage *current_stage, int total,char total_string[100], int * total_string_len) {
        BeginDrawing();
        ClearBackground(BEIGE);
        char* ending_text = "Please type in the total: ";
        int text_size = MeasureText(ending_text, font_size(5));
        DrawText(ending_text, (GetScreenWidth() - text_size) / 2, GetScreenHeight() / 2, font_size(5), BLACK);
        

        char cur_char = GetCharPressed();
        if (isdigit(cur_char) || cur_char == '-') {
            total_string[*total_string_len - 1] = cur_char;
            total_string[*total_string_len] = '\0';
            *total_string_len += 1;
            }

        if (IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_BACKSPACE)) {
            *total_string_len -= 1;
            total_string[*total_string_len - 1] = '\0';
        };

        int text_size_string = MeasureText(total_string, font_size(5));
        DrawText(total_string, (GetScreenWidth() - text_size_string) / 2, GetScreenHeight() / 2 + font_size(5), font_size(5), BLACK);

        if (IsKeyPressed(KEY_ENTER)) {
            bool win = (atoi(total_string) == total);
            *current_stage = RESULT;
            *total_string_len = 1;
            total_string[0] = '\0';
            return win;
        };
        EndDrawing();
        return false;

}

void result(Game_Stage *current_stage, int total, bool win) {
    BeginDrawing();
    if (win) {
        char* winning_text = "You won!!";
        int text_size = MeasureText(winning_text, font_size(5));
        DrawText(winning_text, (GetScreenWidth() - text_size) / 2, GetScreenHeight() / 2, font_size(5), GREEN);
    }
    else {
        char winning_text[100];
        sprintf(winning_text,"Wrong, the answer was %d",total);
        int text_size = MeasureText(winning_text, font_size(5));
        DrawText(winning_text, (GetScreenWidth() - text_size) / 2, GetScreenHeight() / 2, font_size(5), RED);
    }
    int text_size_string = MeasureText("Press enter to replay", font_size(5));
    DrawText("Press enter to replay", (GetScreenWidth() - text_size_string) / 2, GetScreenHeight() / 2 + font_size(5), font_size(5), BLACK);
    EndDrawing();
    if (IsKeyPressed(KEY_ENTER)) {
        *current_stage = PLAY;
    }
}

int main()
{
    srand(time(NULL));
    int init_width = 700;
    int init_height = 700;
    Game_Stage current_stage = START;
    int total;
    char total_string[100]; 
    total_string[0] = '\0';
    int total_string_len = 1;
    bool win;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(init_width, init_height,"numbers game");

    SetTargetFPS(FPS);
    while (!WindowShouldClose()) {
        ClearBackground(BEIGE);
        switch(current_stage) {
            case START: start_game(&current_stage); break;
            case PLAY: total = play(&current_stage); break;
            case FIN: win = finish_game(&current_stage,total,total_string,&total_string_len); break;
            case RESULT: result(&current_stage,total,win); break;
            default: start_game(&current_stage); break;
        };


    }


    return EXIT_SUCCESS;
}
