// Curses-based implementation of uilow for compiling mockup on PC

#include "uilow.h"
#include <curses.h>
#include <stdlib.h>
#include <signal.h>

const int DISP_WIDTH = 16;
const int DISP_HEIGHT = 4;
int g_x = 0;
int g_y = 0;

static void wrap_cursor(void)
{
    g_y += g_x / DISP_WIDTH;
    g_x  = g_x % DISP_WIDTH;
    g_y  = g_y % DISP_HEIGHT;
}

static void finish(int sig)
{
    (void) sig;
    endwin();
    exit(0);
}

void uilow_init(void)
{
    signal(SIGINT, finish);
    initscr();
    keypad(stdscr, true);
    nonl();
    cbreak();
    echo();
}

void uilow_end(void)
{
    finish(0);
}

enum uilow_ret
uilow_move(int y, int x)
{
    if (y >= DISP_HEIGHT || x >= DISP_WIDTH) {
        return UI_ERR;
    }
    if (move(y, x) != ERR) {
        g_y = y;
        g_x = x;
        return UI_OK;
    } else {
        return UI_ERR;
    }
}

enum uilow_ret
uilow_addch(uilow_chtype ch)
{
    wrap_cursor();

    if (mvaddch(g_y, g_x, ch) == ERR) {
        return UI_ERR;
    }

    ++g_x;
    wrap_cursor();
    return UI_OK;
}

enum uilow_ret
uilow_mvaddch(int y, int x, uilow_chtype ch)
{
    if (uilow_move(y, x) == UI_ERR) {
        return UI_ERR;
    } else {
        return uilow_addch(ch);
    }
}

enum uilow_ret
uilow_addstr(const char *str)
{
    for (size_t i = 0; str[i]; ++i) {
        if (str[i] == '\n') {
            g_x = 0;
            ++g_y;
        } else {
            if (uilow_addch(str[i]) == UI_ERR) {
                return UI_ERR;
            }
        }
    }
    wrap_cursor();
    return UI_OK;
}

enum uilow_ret
uilow_mvaddstr(int y, int x, const char *str)
{
    if (uilow_move(y, x) == UI_ERR) {
        return UI_ERR;
    } else {
        return uilow_addstr(str);
    }
}

void uilow_getyx(int *y, int *x)
{
    *y = g_y;
    *x = g_x;
}

void uilow_getmaxyx(int *y, int *x)
{
    *y = DISP_HEIGHT;
    *x = DISP_WIDTH;
}
