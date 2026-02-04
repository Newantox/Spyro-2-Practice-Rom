#include <types.h>
#include <symbols.h>
#include <syscalls.h>
#include <common.h>
#include <menu.h>

extern const GameMenu levelWarpMenu;
#define DIR_UP     0
#define DIR_DOWN   1
#define DIR_LEFT   2
#define DIR_RIGHT  3

extern void Action_ZoeZaps();
extern void ToggleSparx();

static const int32_t gemCycleValues[4] = { 0, 400, 2000, 10000};
static uint8_t gemCycleIndex = 0;
static const int32_t orbCycleValues[2] = { 0, 64};
static uint8_t orbCycleIndex = 0;
static const int32_t fodderCycleValues[10] = {10,9,8,7,6,5,4,3,2,1};
static uint8_t fodderCycleIndex = 0;


///////////////////////////////////////////////////////////////////
// =========================
//  Menu Titles //
// // // To add menus, update here, Flags, Actions, Structure, title handler and menu handler// 
// =========================
static const char* abilityMenuTitle = "Abilities";
static const char* modMenuTitle     = "Game Mods";
static const char* timerMenuTitle   = "Timer";
static const char* miscMenuTitle   = "Misc";
static const char* triggerMenuTitle = "Actions";
static const char* unlocksMenuTitle = "Unlocks";
static const char* valueMenuTitle = "Values";

// =========================
//  Ability Menu Flags
// =========================
char swimFlag;
char climbFlag;
char headbashFlag;
char rangeFlag;
char superflameFlag;
char abilityMode; 
// =========================
//  Mod Menu Flags
// =========================
extern int djflag;
int sparxless  = 0;
// =========================
//  Timer Menu Flags
// =========================c
char timerVisibility = 1;
char promptTalk = 0;
char promptBonk = 0;
char promptGem = 0;
char promptHurt = 0;
char promptEnemy = 0;
char promptGround = 0;
// =========================
//  Misc Menu Flags
// =========================c
char zoeZaps = 1;
char zoeRespawnsInRipto = 1;
char powerupsOn = 0;
char autoMinigames = 0;
char satyrlessPrompt = 0;
char temple = 0;
// =========================
//  Action Menu Flags
// =========================c
char sparx = 4;
char checkpoints = 1;
char cpResets = 0;
char savestates = 1;
char stateMode = 0;
char moonJump = 1;
// =========================
//  Unlocks Menu Flags
// =========================c
char inLevel = 0;
char levelEntry = 0;
char bosses = 0;
char homeworlds = 0;
// =========================
//  Values Menu Flags
// =========================c
int32_t gemValue = 0;
int32_t orbValue = 0;
int32_t taliValue = 0;
int32_t fodderValue = 10;
int32_t mbagsValue = 0;
///////////////////////////////////////////////////////////////////

// =========================
//  Ability Menu Actions
// =========================
static void Action_Swim(void)      { swimFlag          ^= 1; }
static void Action_Climb(void)     { climbFlag         ^= 1; }
static void Action_Headbash(void)  { headbashFlag      ^= 1; }
static void Action_Range(void)     { rangeFlag        ^= 1; }
static void Action_Fireball(void)  { superflameFlag ^= 1; }
static void Action_AbilityMode(void) {abilityMode ^= 1;}
// =========================
//  Mod Menu Actions
// =========================
static void Action_DoubleJump(void) { djflag ^= 1; }  // broken functionality
static void Action_Sparxless(void)  { sparxless  ^= 1; }
// =========================
//  Timer Menu Actions
// =========================
static void Action_TimerVisibility(void) { timerVisibility ^= 1; }
static void Action_PromptTalk(void)  { promptTalk  ^= 1; }
static void Action_PromptBonk(void)  { promptBonk  ^= 1; }
static void Action_PromptGem(void)  { promptGem  ^= 1; } // not implemented
static void Action_PromptHurt(void)  { promptHurt  ^= 1; } // not implemented
static void Action_PromptEnemy(void)  { promptEnemy  ^= 1; } // not implemented
static void Action_PromptGround(void)  { promptGround  ^= 1; } // not implemented
// =========================
//  Misc Menu Actions
// =========================
static void Action_ZoeRespawnsInRipto(void)  { zoeRespawnsInRipto  ^= 1; }
static void Action_PowerupsOn(void) { powerupsOn ^= 1; } 
static void Action_AutoMinigames(void)  { autoMinigames  ^= 1; }
static void Action_SatylressPrompt(void)  { satyrlessPrompt  ^= 1; }
static void Action_Temple(void)  { temple  ^= 1; }
// =========================
//  Misc Menu Actions
// =========================
static void Action_SetSparx(void)  { sparx = ((sparx + 4) % 5); }
static void Action_Checkpoints(void)  { checkpoints  ^= 1; }
static void Action_CPResets(void)  { cpResets  ^= 1; }
static void Action_Savestates(void) { savestates ^= 1;}
static void Action_StateMode(void) { stateMode ^= 1; } 
static void Action_MoonJump(void)  { moonJump  ^= 1; }
// =========================
//  Unlocks Menu Actions
// =========================
static void Action_InLevel(void)  { inLevel ^= 1; }
static void Action_LevelEntry(void)  { levelEntry  ^= 1; }
static void Action_Bosses(void) { bosses ^= 1;}
static void Action_Homeworlds(void) { homeworlds ^= 1; } 
// =========================
//  Values Menu Actions
// =========================
static void Action_GemValue(void)  { 
    gemCycleIndex = (gemCycleIndex + 1) & 3;   // modulo 4
    gemValue = gemCycleValues[gemCycleIndex];
}
static void Action_OrbValue(void)  {
    orbCycleIndex ^= 1;
    orbValue = orbCycleValues[orbCycleIndex];
}
static void Action_TaliValue(void) { taliValue ^= 1;}
static void Action_FodderValue(void) {     
    fodderCycleIndex = (fodderCycleIndex + 1) % 10;
    fodderValue = fodderCycleValues[fodderCycleIndex];}
static void Action_MbagsValue(void) { mbagsValue ^= 1; } 
/////////////////////////////////////////////////////////////////////
// =========================
//  Ability Menu Structure
// =========================
static const MenuEntry abilityMenuEntries[] =
{
    { "Swim",      &swimFlag,          Action_Swim },
    { "Climb",     &climbFlag,         Action_Climb },
    { "Headbash",  &headbashFlag,      Action_Headbash },
    { "Range",     &rangeFlag,        Action_Range },
    { "Fireball",  &superflameFlag, Action_Fireball },
    { ".Mode", &abilityMode, Action_AbilityMode}
};

static const GameMenu abilityMenu =
{
    abilityMenuEntries,
    sizeof(abilityMenuEntries) / sizeof(MenuEntry),
    MENU_TYPE_LIST
};
// =========================
//  Mod Menu Structure
// =========================
static const MenuEntry modMenuEntries[] =
{
    { "DJ", &djflag, Action_DoubleJump },
    { "Sparxless",   &sparxless,  Action_Sparxless }
};

static const GameMenu modMenu =
{
    modMenuEntries,
    sizeof(modMenuEntries) / sizeof(MenuEntry),
    MENU_TYPE_LIST
};

// =========================
//  Timer Menu Structure
// =========================
static const MenuEntry timerMenuEntries[] =
{
    { "Visibility", &timerVisibility, Action_TimerVisibility },
    { "Talkbox",   &promptTalk,  Action_PromptTalk },    
    { "Bonk",   &promptBonk,  Action_PromptBonk },    
    { "Gem",   &promptGem,  Action_PromptGem},
    { "Damage",   &promptHurt,  Action_PromptHurt },
    { "Enemy",   &promptEnemy,  Action_PromptEnemy },
    { "Ground",   &promptGround,  Action_PromptGround }
};

static const GameMenu timerMenu =
{
    timerMenuEntries,
    sizeof(timerMenuEntries) / sizeof(MenuEntry),
    MENU_TYPE_LIST
};
// =========================
//  Misc Menu Structure
// =========================
static const MenuEntry miscMenuEntries[] =
{
    { "Zoe Zaps", &zoeZaps, Action_ZoeZaps },
    { "Zoe in Ripto",   &zoeRespawnsInRipto,  Action_ZoeRespawnsInRipto },    
    { "Powerups",   &powerupsOn,  Action_PowerupsOn },    
    { "Minigames",   &autoMinigames,  Action_AutoMinigames},
    { "Satyrless",   &satyrlessPrompt,  Action_SatylressPrompt},
    { "Faun Lock",   &temple,  Action_Temple}


};

static const GameMenu miscMenu =
{
    miscMenuEntries,
    sizeof(miscMenuEntries) / sizeof(MenuEntry),
    MENU_TYPE_LIST
};

// =========================
//  Trigger Menu Structure
// =========================
static const MenuEntry triggerMenuEntries[] =
{
    { "Set Sparx", &sparx, NULL, Action_SetSparx },   
    { "Checkpoints",   &checkpoints,  Action_Checkpoints }, 
    { "CP Resets",   &cpResets,  Action_CPResets }, 
    { "Save States",   &savestates,  Action_Savestates },
    { "State Hold",   &stateMode,  Action_StateMode},
    { "Moon Jump",   &moonJump,  Action_MoonJump},
};

static const GameMenu triggerMenu =
{
    triggerMenuEntries,
    sizeof(triggerMenuEntries) / sizeof(MenuEntry),
    MENU_TYPE_LIST
};

// =========================
//  Unlocks Menu Structure
// =========================
static const MenuEntry unlocksMenuEntries[] =
{
    { "In-Level", &inLevel, Action_InLevel },   
    { "Level Entry",   &levelEntry,  Action_LevelEntry }, 
    { "Bosses",   &bosses,  Action_Bosses },
    { "Homeworlds",   &homeworlds,  Action_Homeworlds},
};

static const GameMenu unlocksMenu =
{
    unlocksMenuEntries,
    sizeof(unlocksMenuEntries) / sizeof(MenuEntry),
    MENU_TYPE_LIST
};
// =========================
//  Unlocks Menu Structure
// =========================
static const MenuEntry valueMenuEntries[] =
{
    { "Gems",       &gemValue,    NULL, Action_GemValue,    MENU_TYPE_INT32 },
    { "Orbs",       &orbValue,    NULL, Action_OrbValue,    MENU_TYPE_INT32 },
    { "Talismans",  &taliValue,   NULL, Action_TaliValue,   MENU_TYPE_INT32 },
    { "Fodder",     &fodderValue, Action_FodderValue, NULL, MENU_TYPE_INT32},
    { "Moneybags",  &mbagsValue,  NULL, Action_MbagsValue,  MENU_TYPE_INT32 },
};


static const GameMenu valueMenu =
{
    valueMenuEntries,
    sizeof(valueMenuEntries) / sizeof(MenuEntry),
    MENU_TYPE_LIST,
    1
};

// =========================
//  Title Handler
// =========================

static const char* GetMenuTitle(const GameMenu* menu)
{
    if (menu == &abilityMenu) return abilityMenuTitle;
    if (menu == &modMenu)     return modMenuTitle;
    if (menu == &timerMenu)   return timerMenuTitle;
    if (menu == &miscMenu)   return miscMenuTitle;
    if (menu == &triggerMenu)   return triggerMenuTitle;
    if (menu == &unlocksMenu)   return unlocksMenuTitle;
    if (menu == &valueMenu)   return valueMenuTitle;
    if (menu == &levelWarpMenu) return "Level Warp";

    return "";
}
////////////////////

void DrawMenuEntry(const GameMenu* menu, const MenuEntry* e, int x, int y, int color)
{
    char buf[48];

    if (menu->showValues && e->flagPtr)
    {
        int value = 0;

        switch (e->param)
        {
            case MENU_TYPE_BOOL:
            case MENU_TYPE_INT8:
                value = *(int8_t*)e->flagPtr;
                break;

            case MENU_TYPE_INT16:
                value = *(int16_t*)e->flagPtr;
                break;

            case MENU_TYPE_INT32:
                value = *(int32_t*)e->flagPtr;
                break;
        }

        sprintf(buf, "%s:%d", e->label, value);
        DrawText(buf, x, y, color, 0);
    }
    else
    {
        DrawText((char*)e->label, x, y, color, 0);
    }
}







// =========================
//  Menu Handler
// =========================
const GameMenu* menuList[] =
{
    &abilityMenu,
    &modMenu,
    &timerMenu, 
    &miscMenu,
    &triggerMenu,
    &unlocksMenu,
    &valueMenu,
    &levelWarpMenu
    
};

const int menuCount = sizeof(menuList) / sizeof(menuList[0]);
int currentMenuIndex = 0;

#define CURRENT_MENU (menuList[currentMenuIndex])

// =========================
//  Menu State
// =========================
int selectedIndex = 0;
int previousIndex = -1;

#define COLOR_OFF      5
#define COLOR_ON       4
#define COLOR_FLASH    3

// =========================
//  Draw Menu
// =========================

void DrawMenuEx(const GameMenu* menu, int index)
{
    if (menu->type == MENU_TYPE_GRID)
        DrawGridMenu(menu);
    else
        DrawListMenu();
    if(index != -1) currentMenuIndex = index;
}

void DrawMenu(void)
{
    DrawMenuEx(CURRENT_MENU,-1);
}


int flashCounter = 0;

void DrawListMenu(void)
{
    const GameMenu* menu = CURRENT_MENU;
    const MenuEntry* e   = menu->entries;

    _DrawOutlinedBG(10,140,60,200);

    int* unk = 0;

    // -------------------------
    // Draw Title
    // -------------------------
    const char* title = GetMenuTitle(menu);
    DrawText((char*)title, 20, 78, 6, unk);

    int y = 90 + 4;

    // Flash logic
    if (selectedIndex != previousIndex)
    {
        flashCounter = 0;
        previousIndex = selectedIndex;
    }

    flashCounter++;
    const int flashOn = ((flashCounter & 15) < 4);

    // Global color map for multi‑state flags
    static const unsigned char colorMap[] = {
        5,      // 0
        8,      // 1
        4,      // 2
        13,     // 3
        2,      // 4
        12,      // 5
        11,      // 6
        7,      // 7
        10,      // 8
        9,      // 9
        0,    // 10
    };

    for (int i = 0; i < menu->count; i++, e++, y += 12)
    {
        // Read full flag value
        const unsigned int flag = *(volatile unsigned char*)e->flagPtr;

        int color;

        // Boolean vs Multi‑state detection
        if (e->actionInt == NULL)
        {
            if (flag == 0)  {
            color = COLOR_OFF;
            } else {
                color = COLOR_ON;
            }
        }
        else
        {
            const unsigned int safe = (flag < sizeof(colorMap)) ? flag : 0;
            color = colorMap[safe];
        }

        // Flash highlight override
        if (i == selectedIndex && flashOn)
            color = COLOR_FLASH;

        // 🔥 NEW: dynamic label rendering
        DrawMenuEntry(menu, e, 20, y, color);

    }
}



extern const char* levelNames[];

static const char* GetGridLabel(int index)
{
    if (index == 29)
        return "Reload Level";

    return levelNames[index];
}


void DrawGridMenu(const GameMenu* menu)
{
    const int startX = 20;
    const int startY = 60;

    const int cellW = 160;
    const int cellH = 12;

    _DrawOutlinedBG(10,500,50,185);


    for (int i = 0; i < menu->count; i++)
    {
        int col = i % GRID_COLS;
        int row = i / GRID_COLS;

        int x = startX + col * cellW;
        int y = startY + row * cellH;

        int color = (i == selectedIndex) ? COLOR_FLASH : 9;

        const char* label = GetGridLabel(i);
        DrawText(label, x, y, color, 0);
    }
}




// =========================
//  Menu Input
// =========================



void MenuInput(int direction)
{
    const GameMenu* menu = CURRENT_MENU;
    const int count = menu->count;

    // List Navigation
    if (menu->type == MENU_TYPE_LIST)
    {
        if (direction == DIR_UP)
        {
            selectedIndex--;
            if (selectedIndex < 0)
                selectedIndex = count - 1;
        }
        else if (direction == DIR_DOWN)
        {
            selectedIndex++;
            if (selectedIndex >= count)
                selectedIndex = 0;
        }

        return;
    }

    // Grid Navigation
    if (menu->type == MENU_TYPE_GRID)
    {
        int row = selectedIndex / GRID_COLS;
        int col = selectedIndex % GRID_COLS;

        switch (direction)
        {
            case DIR_UP:
                row--;
                if (row < 0)
                    row = GRID_ROWS - 1;
                break;

            case DIR_DOWN:
                row++;
                if (row >= GRID_ROWS)
                    row = 0;
                break;

            case DIR_LEFT:
                col--;
                if (col < 0)
                    col = GRID_COLS - 1;
                break;

            case DIR_RIGHT:
                col++;
                if (col >= GRID_COLS)
                    col = 0;
                break;
        }

        selectedIndex = row * GRID_COLS + col;

        if (selectedIndex >= count)
            selectedIndex = count - 1;

        return;
    }
}



// =========================
//  Run Action
// =========================
void RunMenuAction(void)
{
    const GameMenu* menu = CURRENT_MENU;

    if (menu->type == MENU_TYPE_GRID)
    {
        LevelWarp(selectedIndex);
        return;
    }
    
    const MenuEntry* e = &menu->entries[selectedIndex];

    if (e->actionInt)
        e->actionInt(e->param);
    else if (e->actionVoid)
        e->actionVoid();
}


