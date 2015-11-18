#include "uilow.h"
#include <curses.h>

int main(void)
{
    uilow_init();
    uilow_mvaddstr(0, 0, "asdfasdfasdfasdfasdfasdf");
    getch();
    uilow_end();
}
