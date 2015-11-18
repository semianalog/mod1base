#ifndef _UILOW_H
#define _UILOW_H

enum uilow_ret { UI_OK, UI_ERR };
typedef unsigned int uilow_chtype;

// Low-level UI functions

/// Initialize the low-level UI
void uilow_init(void);

/// Deinitialize the low-level UI
void uilow_end(void);

/// Move to a position on the display
enum uilow_ret
uilow_move(int y, int x);

/// Add a character, then advance the cursor
enum uilow_ret
uilow_addch(uilow_chtype ch);

/// Move and add a character, then advance the cursor
enum uilow_ret
uilow_mvaddch(int y, int x, uilow_chtype ch);

/// Add a string of characters, then advance the cursor
enum uilow_ret
uilow_addstr(const char *str);

/// Move, add a string of characters, then advance the cursor
enum uilow_ret
uilow_mvaddstr(int y, int x, const char *str);

/// Get the current cursor position
void uilow_getyx(int *y, int *x);

/// Get the width and height
void uilow_getmaxyx(int *y, int *x);

#endif // _UILOW_H
