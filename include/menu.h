#ifndef MENU_H
#define MENU_H

typedef void (*MenuActionVoid)(void);
typedef void (*MenuActionInt)(int);

typedef enum
{
    MENU_TYPE_LIST,
    MENU_TYPE_GRID
} MenuType;

typedef struct
{
    const char* label;
    void*       flagPtr;
    MenuActionVoid actionVoid;
    MenuActionInt  actionInt;
    int            param;

} MenuEntry;

typedef struct
{
    const MenuEntry* entries;
    int count;
    MenuType type;
    int showValues;   // 0 = off, 1 = show "Label: X"
} GameMenu;

#define GRID_COLS 3
#define GRID_ROWS 10


#define LEVEL_ID_ARRAY ((u8*)0x80064994)

#define DIR_UP     0
#define DIR_DOWN   1
#define DIR_LEFT   2
#define DIR_RIGHT  3

#define GRID_START_X 20
#define GRID_START_Y 60
#define GRID_CELL_W  160
#define GRID_CELL_H  12

#define MENU_TYPE_BOOL   0
#define MENU_TYPE_INT8   1
#define MENU_TYPE_INT16  2
#define MENU_TYPE_INT32  3

#endif

