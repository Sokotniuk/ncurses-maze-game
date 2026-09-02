#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "game.h"

#define WALL_VERT '|'
#define WALL_HORIZ '_'
#define PATH ' '
#define PLAYER_RIGHT '>'
#define PLAYER_LEFT '<'
#define PLAYER_UP '^'
#define PLAYER_DOWN 'v'
#define EXIT 'E'
#define LEVEL_TIME 120

char game_map[24][80];
char player_dir = '>';
int map_width = 40;
int map_height = 15;
int player_x, player_y;
int exit_x, exit_y;
int game_time_left;
int game_moves = 0;
int game_warnings = 0;
int game_active = 0;
int current_level = 0;
time_t level_start_time;

void init_ncurses() {
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        start_color();

        // colors
        init_pair(1, COLOR_RED, COLOR_BLACK);     // walls
        init_pair(2, COLOR_GREEN, COLOR_BLACK);   // player
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);  // exit
        init_pair(4, COLOR_CYAN, COLOR_BLACK);    // message
        init_pair(5, COLOR_WHITE, COLOR_BLACK);   // text
        }
void create_level1() {
    map_width = 20;
    map_height = 10;

    for(int y = 0; y < 24; y++){
        for(int x = 0; x < 80; x++){
            game_map[y][x] = PATH;
        }
    }

    for(int x = 0; x < map_width; x++){
        game_map[0][x] = WALL_HORIZ;
        game_map[map_height-1][x] = WALL_HORIZ;
    }

    for(int y = 0; y < map_height; y++){
        game_map[y][0] = WALL_VERT;
        game_map[y][map_width-1] = WALL_VERT;
    }

    for(int x = 2; x < 18; x++) game_map[2][x] = WALL_HORIZ;
    game_map[2][6] = PATH;
    game_map[2][13] = PATH;

    for(int x = 3; x < 16; x++) game_map[5][x] = WALL_HORIZ;
    game_map[5][9] = PATH;

    for(int y = 3; y < 7; y++) game_map[y][10] = WALL_VERT;
    game_map[4][10] = PATH;
    game_map[6][10] = PATH;

    player_x = 1;
    player_y = 1;
    player_dir = PLAYER_RIGHT;

    exit_x = map_width - 2;
    exit_y = map_height - 2;

    game_map[player_y][player_x] = player_dir;
    game_map[exit_y][exit_x] = EXIT;
}
void create_level2() {
    map_width = 28;
    map_height = 12;

    for(int y = 0; y < 24; y++){
        for(int x = 0; x < 80; x++){
            game_map[y][x] = PATH;
        }
    }

    for(int x = 0; x < map_width; x++){
        game_map[0][x] = WALL_HORIZ;
        game_map[map_height-1][x] = WALL_HORIZ;
    }
    for(int y = 0; y < map_height; y++){
        game_map[y][0] = WALL_VERT;
        game_map[y][map_width-1] = WALL_VERT;
    }

    for(int x = 3; x < 25; x++) game_map[3][x] = WALL_HORIZ;
    game_map[3][8] = PATH;
    game_map[3][16] = PATH;

    for(int x = 5; x < 20; x++) game_map[7][x] = WALL_HORIZ;
    game_map[7][12] = PATH;

    for(int y = 3; y < 9; y++) game_map[y][10] = WALL_VERT;
    game_map[5][10] = PATH;

    for(int y = 4; y < 10; y++) game_map[y][17] = WALL_VERT;
    game_map[8][17] = PATH;

    for(int y = 2; y < 7; y++) game_map[y][22] = WALL_VERT;
    game_map[4][22] = PATH;

    player_x = 1;
    player_y = 1;
    player_dir = PLAYER_RIGHT;

    exit_x = map_width - 2;
    exit_y = map_height - 2;

    game_map[player_y][player_x] = player_dir;
    game_map[exit_y][exit_x] = EXIT;
}
void create_level3() {
    map_width = 40;
    map_height = 15;

    for(int y = 0; y < 24; y++){
        for(int x = 0; x < 80; x++){
            game_map[y][x] = PATH;
        }
    }

    for(int x = 0; x < map_width; x++){
        game_map[0][x] = WALL_HORIZ;
        game_map[map_height-1][x] = WALL_HORIZ;
    }
    for(int y = 0; y < map_height; y++){
        game_map[y][0] = WALL_VERT;
        game_map[y][map_width-1] = WALL_VERT;
    }

    for(int x = 2; x < 33; x++) game_map[3][x] = WALL_HORIZ;
    game_map[3][14] = PATH;
    game_map[3][25] = PATH;

    for(int x = 4; x < 35; x++) game_map[6][x] = WALL_HORIZ;
    game_map[6][11] = PATH;
    game_map[6][28] = PATH;

    for(int x = 5; x < 38; x++) game_map[9][x] = WALL_HORIZ;
    game_map[9][18] = PATH;

    for(int y = 4; y < 9; y++) game_map[y][12] = WALL_VERT;
    game_map[7][12] = PATH;

    for(int y = 7; y < 12; y++) game_map[y][21] = WALL_VERT;
    game_map[10][21] = PATH;

    for(int y = 2; y < 11; y++) game_map[y][30] = WALL_VERT;
    game_map[5][30] = PATH;

    player_x = 1;
    player_y = 1;
    player_dir = PLAYER_RIGHT;

    exit_x = map_width - 2;
    exit_y = map_height - 2;

    game_map[player_y][player_x] = player_dir;
    game_map[exit_y][exit_x] = EXIT;
}
void center_map() {
        int term_width, term_height;
        getmaxyx(stdscr, term_height, term_width);

        int start_x = (term_width - map_width) / 2;
        int start_y = (term_height - map_height) / 2;

        attron(COLOR_PAIR(5));
        for(int y = 0; y < term_height; y++) {
                for(int x = 0; x < term_width; x++) {
                        mvaddch(y,x, ' ');
                }
        }

        for(int y = 0; y < map_height; y++) {
                for(int x = 0; x < map_width; x++) {
                        int screen_x = start_x + x;
                        int screen_y = start_y + y;

                        if(screen_x >= 0 && screen_x < term_width && screen_y >= 0 && screen_y < term_height) {
                                char ch = game_map[y][x];

                                if(ch == WALL_VERT || ch == WALL_HORIZ) {
                                        attron(COLOR_PAIR(1));
                                } else if (ch == PLAYER_RIGHT || ch == PLAYER_LEFT || ch == PLAYER_DOWN || ch == PLAYER_UP) {
                                        attron(COLOR_PAIR(2) | A_BOLD);
                                } else if (ch == EXIT) {
                                        attron(COLOR_PAIR(3) | A_BOLD);
                                } else {
                                        attron(COLOR_PAIR(5));
                                }

                                mvaddch(screen_y, screen_x, ch);
                        }
                }
        }
}

void draw_game() {
        int term_width, term_height;

        clear();

        getmaxyx(stdscr, term_height, term_width);

        center_map();

        attron(COLOR_PAIR(5) | A_BOLD);

        char level_msg[50];
        sprintf(level_msg, "Level: %d/3", current_level + 1);
        mvprintw(1,2,"%s", level_msg);

        // time
        int time_passed = (int)(time(NULL) - level_start_time);
        game_time_left = LEVEL_TIME - time_passed;
        if(game_time_left < 0) game_time_left = 0;

        char time_msg[50];
        sprintf(time_msg, "Time: %02d:%02d", game_time_left / 60, game_time_left % 60);
        mvprintw(1, term_width - strlen(time_msg) - 2,"%s", time_msg);

        char moves_msg[50];
        sprintf(moves_msg, "Step: %d", game_moves);
        mvprintw(2,2,"%s",  moves_msg);

        char warn_msg[50];
        sprintf(warn_msg, "Warning: %d", game_warnings);
        mvprintw(3,2, "%s", warn_msg);

        mvprintw(term_height - 3, 2, "Control: WASD - step, Q - EXIT");
        mvprintw(term_height - 2, 2, "The goal is to reach the E");

        attron(COLOR_PAIR(1));
        mvhline(term_height - 5, 0, WALL_HORIZ, term_width);

        refresh();
}

int move_player(char input) {
        int old_x = player_x;
        int old_y = player_y;
        char old_dir = player_dir;

        switch(input) {
                case 'w':
                case 'W':
                        player_dir = '^';
                        player_y--;
                        break;
                case 's':
                case 'S':
                        player_dir = 'v';
                        player_y++;
                        break;
                case 'a':
                case 'A':
                        player_dir = '<';
                        player_x--;
                        break;
                case 'd':
                case 'D':
                        player_dir = '>';
                        player_x++;
                        break;
                default:
                        return 0;
        }

        if(player_x < 0 || player_x >= map_width || player_y < 0 || player_y >= map_height) {
                player_x = old_x;
                player_y = old_y;
                player_dir = old_dir;
                game_warnings++;
                return -1;
        }

        char target_cell = game_map[player_y][player_x];
        if(target_cell == WALL_VERT || target_cell == WALL_HORIZ) {
                player_x = old_x;
                player_y = old_y;
                player_dir = old_dir;
                game_warnings++;
                return -1;
        }

        game_map[old_y][old_x] = PATH;

        if(target_cell != EXIT) {
                game_map[player_y][player_x] = player_dir;
        } else {
                game_map[old_y][old_x] = player_dir;
        }
        game_moves++;
        return 1;
}

void show_message(const char *msg, int y_offset) {
        int term_width, term_height;
        getmaxyx(stdscr, term_height, term_width);

        int start_x = (term_width - strlen(msg)) / 2;
        int start_y = (term_height - map_height) / 2 + map_height + y_offset;

        attron(COLOR_PAIR(4) | A_BOLD | A_BLINK);
        mvprintw(start_y, start_x,"%s", msg);
        attroff(A_BLINK);

        refresh();

        flushinp();

        napms(1000);

        flushinp();

        flushinp();
}

void run_game(int level) {
        current_level = level -1;
        game_active = 1;
        game_moves = 0;
        game_warnings = 0;
        level_start_time = time(NULL);

        nodelay(stdscr, TRUE);

        switch(level) {
                case 1:
                        create_level1();
                        break;
                case 2:
                        create_level2();
                        break;
                case 3:
                        create_level3();
                        break;
                default:
                        create_level1();
                        break;
        }

        while(game_active) {
                draw_game();

                if(game_time_left <= 0) {
                        show_message("TIME LEFT! LOSE!", 1);
                        game_active = 0;
                        break;
                }

                if(player_x == exit_x && player_y == exit_y) {
                        show_message("WIN! Level passed!", 1);
                        game_active = 0;
                        break;
                }


                int ch = getch();
                if(ch != ERR) {
                        if(ch == 'q' || ch == 'Q') {
                                game_active = 0;
                                break;
                        }

                        int result = move_player(ch);
                        if(result == -1) {
                                show_message("You can't go into the wall!", 2);
                        }
                }

                napms(50);
        }

        nodelay(stdscr, FALSE);

        clear();
        refresh();


        flushinp();

        napms(100);
}

void init_game_ncurses() {
        init_ncurses();
}
void end_game_ncurses() {
        endwin();
}
