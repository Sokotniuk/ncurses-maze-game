#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

void menuLevel();
void playLevel(int level_num);

int showMenu(char *items[], int count) {
    char *game_titl[] = {
        "GGG   AAAAA   M     M  EEEEE     M     M  EEEEE   N   N   U   U  ",
        "G     A   A   MM   MM  E         MM   MM  E       NN  N   U   U  ",
        "G  GG AAAAA   M M M M  EEEE      M M M M  EEEE    N N N   U   U  ",
        "G   G A   A   M  M  M  E         M  M  M  E       N  NN   U   U  ",
        "GGGGG A   A   M     M  EEEEE     M     M  EEEEE   N   N   UUUUU  "
};
int titl_line = 5;

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    int color_support = has_colors();
    if(color_support) {
            start_color();

    if(can_change_color()) {
            init_color(COLOR_BLACK, 0,0,0);
    }

            if(can_change_color() || COLORS >= 16) {
            // colors menu
            init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_BLUE, COLOR_BLACK);
        init_pair(6, COLOR_YELLOW, COLOR_BLACK);
        init_pair(7, COLOR_MAGENTA, COLOR_BLACK);

            // rainbow colors
            init_pair(10, COLOR_RED, COLOR_BLACK);
        init_pair(11, COLOR_YELLOW, COLOR_BLACK);
        init_pair(12, COLOR_GREEN, COLOR_BLACK);
        init_pair(13, COLOR_CYAN, COLOR_BLACK);
        init_pair(14, COLOR_BLUE, COLOR_BLACK);
        init_pair(15, COLOR_MAGENTA, COLOR_BLACK);
            bkgd(COLOR_PAIR(1));
        }
    }

    clear();

    int choise = 0;
    int running = 1;
    int wrong_key = 0;
    char wrong_message[200] = "Please use onle arrows, Enter or ESC";

    while(running) {
            clear();

            int rows, cols;

            getmaxyx(stdscr, rows, cols);
//Draw rainbow title
            int title_w = 0;
            for(int i = 0; i < titl_line; i++) {
                    int len = strlen(game_titl[i]);
                    if(len > title_w) title_w = len;
            }

            int title_x = (cols - title_w) / 2;
            int title_y = rows / 4;

            int rainbow_order[] = {10, 11, 12, 13, 14};

            for(int line = 0; line < titl_line; line++) {
                    int y = title_y + line;
                    int x = title_x;

                    int color_index = 0;

                    for(int j = 0; j < (int)strlen(game_titl[line]); j++) {
                            if(game_titl[line][j] == ' ') {
                                    mvaddch(y,x+j,' ');
                                    continue;
                            }

                            int color_pair = rainbow_order[color_index % 6];
                            attron(COLOR_PAIR(color_pair) | A_BOLD);
                            mvaddch(y,x + j, game_titl[line][j]);
                            attroff(COLOR_PAIR(color_pair) | A_BOLD);

                            color_index++;
                    }
            }

 // Draw menu items
            for(int i = 0; i < count; i++) {
                    int y = rows/2 - count/2 + i;
                    int x = (cols - strlen(items[i])) /2;
                    if(i == choise) {
                            attron(A_REVERSE);
                            mvprintw(y,x, "%s", items[i]);
                            attroff(A_REVERSE);
                    }
                    else {
                            mvprintw(y,x,"%s", items[i]);
                    }
            }
            mvprintw(rows-3, (cols-30)/2, " ____________________________ ");
            mvprintw(rows-2, (cols-30)/2, "| Arrows + Enter, ESC - Exit |");
            mvprintw(rows-1, (cols-30)/2, "|                            |");
            if(wrong_key) {
                    attron(A_BOLD | COLOR_PAIR(1));
                    mvprintw(rows-5, (cols - strlen(wrong_message)) / 2, "%s", wrong_message);
                    attroff(A_BOLD | COLOR_PAIR(1));
                    wrong_key = 0;
            }
            int max_y, max_x;
            getmaxyx(stdscr, max_y, max_x);

            char* avtor = "made by Nikita Sokotniuk";
            int avtor_len = strlen(avtor);

            int avtor_y = max_y - 2;
            int avtor_x = max_x - avtor_len - 1;

            if(avtor_x < 0) {
                    avtor = 0;
            }

            int gradient_colors[] = {COLOR_BLUE, COLOR_CYAN, COLOR_GREEN, COLOR_YELLOW, COLOR_MAGENTA, COLOR_RED};

            attron(A_BOLD);
            for(int i = 0; i < avtor_len; i++) {
                    int color_index = (i * 6) / avtor_len;

                    init_pair(20 + i, gradient_colors[color_index], COLOR_BLACK);
                    attron(COLOR_PAIR(20 + i));
                    mvprintw(avtor_y, avtor_x + i, "%c", avtor[i]);
                    attroff(COLOR_PAIR(20 + i));
            }
            attroff(A_BOLD);

            refresh();

            int key = getch();

            strcpy(wrong_message, "");

            switch (key) {
                    case KEY_UP:
                            if(choise > 0) choise--;
                            break;
                    case KEY_DOWN:
                            if(choise < count - 1) choise++;
                            break;
                    case 10: //enter
                            running = 0;
                            break;
                    case 27: // ESC
                            choise = -1;
                            running = 0;
                            break;

                    default:
                            wrong_key = 1;
                            strcpy(wrong_message, "Please, use only ARROWS, ENTER, ESC!");
                            break;
            }
    }

    clear();
    refresh();

    return choise;
}
void menuLevel() {

        clear();
        refresh();

        nodelay(stdscr, TRUE);
        timeout(0);

        int ch;
        for(int i = 0; i < 5; i++) {
                while((ch = getch()) != ERR) {

                }
                flushinp();
                napms(10);
        }
        timeout(-1);


        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

int color_support = has_colors();
    if(color_support) {
            start_color();

    if(can_change_color()) {
            init_color(COLOR_BLACK, 0,0,0);
    }

            if(can_change_color() || COLORS >= 16) {
            // colors menu
            init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_BLUE, COLOR_BLACK);
        init_pair(6, COLOR_YELLOW, COLOR_BLACK);
        init_pair(7, COLOR_MAGENTA, COLOR_BLACK);

            // rainbow colors
            init_pair(10, COLOR_RED, COLOR_BLACK);
        init_pair(11, COLOR_YELLOW, COLOR_BLACK);
        init_pair(12, COLOR_GREEN, COLOR_BLACK);
        init_pair(13, COLOR_CYAN, COLOR_BLACK);
        init_pair(14, COLOR_BLUE, COLOR_BLACK);
        init_pair(15, COLOR_MAGENTA, COLOR_BLACK);
            bkgd(COLOR_PAIR(1));
        }
    }
    clear();

   char *level_title[] = {
        "L     EEEEE V   V EEEEE L            SSSS EEEEE L     EEEEE  CCC  TTTTT",
        "L     E     V   V E     L           S     E     L     E     C       T",
        "L     EEEE  V   V EEEE  L            SSS  EEEE  L     EEEE  C       T",
        "L     E      V V  E     L               S E     L     E     C       T",
        "LLLLL EEEEE   V   EEEEE LLLLL       SSSS  EEEEE LLLLL EEEEE  CCC    T"
    };

    int title_lines = 5;

    int title_w = 0;
    for(int i = 0; i < title_lines; i++) {
            int len = strlen(level_title[i]);
            if(len > title_w) title_w = len;
    }
    int title_x = (max_x - title_w) / 2;
    int title_y = max_y / 6;

    int rainbow_order[] = { 10, 11, 12,13,14,15};

    for(int line = 0; line < title_lines; line++) {
            int y = title_y + line;
            int x = title_x;

            int color_index = 0;

            for(int j = 0; j < (int)strlen(level_title[line]); j++) {
                    if(level_title[line][j] == ' ') {
                            mvaddch(y,x + j, ' ');
                            continue;
                    }

                    int color_pair = rainbow_order[color_index % 6];

                    if(has_colors()) {
                            attron(COLOR_PAIR(color_pair) | A_BOLD);

                    } else {
                            attron(A_BOLD);
                    }
                    mvaddch(y,x + j, level_title[line][j]);

                    if(has_colors()) {
                            attroff(COLOR_PAIR(color_pair) | A_BOLD);
                    } else {
                            attroff(A_BOLD);
                    }
                    color_index++;
            }
    }

    int total_items = 4;
    int selected = 0;
    int wrong_key = 0;
    time_t warning_start_time = 0;
    char wrong_message[100] = "Please, use only arrows, Enter or ESC";
    while(1) {
            getmaxyx(stdscr, max_y, max_x);

            int menu_start_y = max_y / 2 - 2;
            int menu_w = 20;
            int warning_display_y = menu_start_y + 5;

            for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < menu_w; j++) {
                            mvaddch(menu_start_y + i, (max_x - menu_w)/2 + j, ' ');
                    }
            }


        move(warning_display_y, 0);
        clrtoeol();

            for(int i = 0; i < total_items && i < 4; i++) {
                    int row = menu_start_y + i;
                    int col = (max_x - 15)/2;

                    if(i == selected) {
                            attron(A_REVERSE);
                    }

                    if(has_colors()) {
                            if(i < 3) {
                            attron(COLOR_PAIR(3));
                            } else {
                                    attron(COLOR_PAIR(1));
                            }
                    }
                if(i < 3) {
                        char level_text[20];
                    sprintf(level_text, "Level %d", i +1);
                    int text_len = strlen(level_text);
                    mvprintw(row,col + (menu_w - text_len)/2, "%s", level_text);
                } else {
                        char back_text[] = "BACK to Main menu";
                        int text_len = strlen(back_text);
                        mvprintw(row,col + (menu_w - text_len)/2, "%s", back_text);
                }

                    if(has_colors()) {
                            if(i < 3) {
                            attroff(COLOR_PAIR(3));
                            } else {
                                    attroff(COLOR_PAIR(1));
                            }
                    }

                    if(i == selected) {
                            attroff(A_REVERSE);
                    }
            }
            if(wrong_key) {
                    time_t current_time = time(NULL);
                    if(difftime(current_time, warning_start_time) < 2.0) {
                            if (warning_display_y < max_y - 1) {
                                int msg_len = strlen(wrong_message);
                                int msg_x = (max_x - msg_len) / 2;

                    if(has_colors()) {
                            attron(COLOR_PAIR(2) | A_BOLD);
                    }
                    else {
                            attron(A_BOLD);
                    }
                    mvprintw(warning_display_y, msg_x, "%s", wrong_message);

                    if(has_colors()) {
                            attroff(COLOR_PAIR(2) | A_BOLD);
                    } else {
                            attroff(A_BOLD);
                    }
                    }
                 } else {

                        wrong_key = 0;
                        refresh();
                 }
            }

            int help_y = max_y - 4;
            char* help_lines[] = {
            "Use ARROW KEYS to navigate",
            "Press ENTER to select",
            "Press ESC to go back"
        };

        for (int i = 0; i < 3; i++) {
            int text_len = strlen(help_lines[i]);
            mvprintw(help_y + i, (max_x - text_len) / 2, "%s", help_lines[i]);
        }


        char* avtor = "made by Nikita Sokotnyuk";
        int avtor_len = strlen(avtor);
        int avtor_y = max_y - 2;
        int avtor_x = max_x - avtor_len - 1;

        if (avtor_x >= 0 && avtor_y >= 0) {
            int gradient_colors[] = {COLOR_BLUE, COLOR_CYAN, COLOR_GREEN,
                                    COLOR_YELLOW, COLOR_MAGENTA, COLOR_RED};

            attron(A_BOLD);
            for (int i = 0; i < avtor_len; i++) {
                int color_index = (i * 6) / avtor_len;
                if (color_index >= 6) color_index = 5;

                init_pair(30 + i, gradient_colors[color_index], COLOR_BLACK);
                attron(COLOR_PAIR(30 + i));
                mvprintw(avtor_y, avtor_x + i, "%c", avtor[i]);
                attroff(COLOR_PAIR(30 + i));
            }
            attroff(A_BOLD);
        }

        refresh();

        int ch = getch();

        switch(ch) {
                case KEY_UP:
                        if(selected > 0) selected --;
                        wrong_key = 0;
                        break;

                case KEY_DOWN:
                        if(selected < total_items - 1) selected++;
                        wrong_key = 0;
                        break;

                case '\n':
                case KEY_ENTER:
                        if(selected < 3) {
                        playLevel(selected + 1);

                        selected = 0;
                        wrong_key = 0;

                        flushinp();
                        refresh();
                        clear();

                        getmaxyx(stdscr, max_y, max_x);
                        title_x = (max_x - title_w) / 2;
                        title_y = max_y / 6;

                        for(int line = 0; line < title_lines; line++) {
                                int y = title_y + line;
                                int x = title_x;
                                int color_index = 0;

                                for (int j = 0; j < (int)strlen(level_title[line]); j++) {
                                  if (level_title[line][j] == ' ') {
                                          mvaddch(y, x + j, ' ');
                                                 continue;
                                      }

                                int color_pair = rainbow_order[color_index % 6];

                                 if (has_colors()) {
                                   attron(COLOR_PAIR(color_pair) | A_BOLD);
                                 } else {
                                         attron(A_BOLD);
                                         }

                                 mvaddch(y, x + j, level_title[line][j]);

                                 if (has_colors()) {
                                         attroff(COLOR_PAIR(color_pair) | A_BOLD);
                                         } else {
                                          attroff(A_BOLD);
                                 }

                                 color_index++;
                                 }
                        }

                     } else {
                             flushinp();
                             return;
                     }
                     break;


                case 27: // ECS
                        endwin();
                        exit(0);
                        break;

                default:
                        wrong_key = 1;
                        warning_start_time = time(NULL);
                        strcpy(wrong_message, "Invalid key! Use ARROWS, ENTER");
                        break;
        }
    }
}

void playLevel(int level_num) {

        flushinp();

        nodelay(stdscr, FALSE);
        curs_set(0);

        clear();
        refresh();

        run_game(level_num);

        clear();
        refresh();
        nodelay(stdscr, TRUE);
        curs_set(0);

        flushinp();

        nodelay(stdscr,TRUE);
        timeout(0);

        int ch;
        for(int i = 0; i < 5; i++) {
                while((ch = getch()) != ERR) {

                }
                flushinp();
                napms(20);
        }
        nodelay(stdscr, FALSE);
        timeout(-1);

        flushinp();


}
int main() {
       initscr();
       noecho();
       cbreak();
       keypad(stdscr, TRUE);
       curs_set(0);

       while(1) {
        char *menu_items[] = {
                "Play Game",
                "Exit"
        };

        int choise = showMenu(menu_items, 2);
        if(choise == 0) {
                menuLevel();
        }
        else if(choise == 1 || choise == -1) {
                break;
        }
       }

        endwin();
        return 0;
}