#include <types.h>
#include <symbols.h>
#include <syscalls.h>
#include <common.h>
#include <menu.h>

#define DIR_UP     0
#define DIR_DOWN   1
#define DIR_LEFT   2
#define DIR_RIGHT  3


int lastButtonCombo = NONE;
bool ButtonCombo(int buttons);
bool menuFlag = 0;
int actionHighlightTimer = 0;   // counts frames
extern const GameMenu levelWarpMenu;
extern int currentMenuIndex;
int currentStateSlot = 0;
int hasValidState1 = 0;
int hasValidState2 = 0;
int hasValidState3 = 0;
char slotInfo[10];
char setupGame = 0;
char setLives = 1;
extern char moonJump;
extern char stateMode;
char stateHeld;
extern char sparx;
extern char checkpoints;
extern char savestates;
int pendingLoadSlot = 0;
int sky = 0;
char skipOpening;



void SetupGame() {
    skipOpening = 1;
    lookToStartTimer = 1;
    *(int*)0x80063808 = 0x64Fc9803;
    }

char CycleSlot(char dir)
{
    currentStateSlot = (currentStateSlot + dir + 2) % 2; // change if 3 slots wanted
}

void ModMain(void)
{   DrawSync(0); // Main Hook

    if (!skipOpening) {
        if (_gameState == 0xb) {
            *(int*)0x80066f90 = 0xb;
            *(int*)0x800668f4 = 0x3;
            *(int*)0x80067e0c = 0x5;
            skipOpening = 1;
        }
    }
    if(!setupGame) SetupGame(); // setup any one time flags
    //if (*(int*) 0x800069ff0 == 0x10C66) 
    setupGame = 1; // if spyro x-coord glimmer spawn
    ChangeGameOver();
    *(int*)0x80067EC4 = sky; // day/night
    // handles lives to allow game overs
    if(setLives) _lives = 99;
    if(setLives) *(int*)0x80067670 = 99;
    if (!_gameState) setLives = 1;

    if(setupGame) Timers();
    MenuActions();

    if (stateHeld)lookToStartTimer = 1;
    if(stateHeld && (_currentButtons.current != 0 && _currentButtons.current != L3_BUTTON)) {
            stateHeld = 0;
            _updateFlags = 0x7b;

        }
    

    if(_gameState == 7) {
        menuFlag = 1;
        currentMenuIndex = 7;    
    }

    int combo = GetPressedCombo();

	if(menuFlag) DrawMenu();

    // Moon Jump - uses different buttonCombo due to constant write needed
    if (_currentButtons.current == 0x140 && moonJump) {
        *(char*)0x8006A08D = 0xF;
    }


    if((_gameState == 0 || _gameState == 1 ||_gameState == 7) && setupGame == 1) {

            DrawSlot();


    if(checkpoints) {
        switch (combo) {

        case (L1_BUTTON | R1_BUTTON | SQUARE_BUTTON):
            lookToStartTimer = 1;
            loadCheckpoint();
            ManageAbilities();
            break;

        case (L1_BUTTON | R1_BUTTON | CIRCLE_BUTTON):
            saveCheckpoint();
            break;

        case (L1_BUTTON | R1_BUTTON | TRIANGLE_BUTTON):
            lookToStartTimer = 1;
            resetCheckpoint();
            break;

            }
    }
    switch (combo)
    {
case (L3_BUTTON): // load
    if (_gameState < 2 && savestates) {
        if (currentStateSlot == 0 && hasValidState1) pendingLoadSlot = 1;
        else if (currentStateSlot == 1 && hasValidState2) pendingLoadSlot = 2;
        else if (currentStateSlot == 2 && hasValidState3) pendingLoadSlot = 3;
    }
    break;

        
        case (R3_BUTTON): //save
            if(_gameState < 2 && savestates) {
                if (currentStateSlot == 0) {
                    SaveState(1);
                    hasValidState1 = 1; }    
                else if (currentStateSlot == 1) {
                    SaveState(2);
                    hasValidState2 = 1; }    
                else if (currentStateSlot == 2) {
                    SaveState(3);
                    hasValidState3 = 1; }   
            }
            break;

		case (SELECT_BUTTON + TRIANGLE_BUTTON):
            menuFlag ^= 1;
			_updateFlags = menuFlag ? 0 : 0x7b;
            //if (!menuFlag) ResetMenu(); // Add to make menu default to page 1 every time opening
            break;

        case (L1_BUTTON | L2_BUTTON):
            CycleSlot(-1);
            break;
        case (R1_BUTTON | R2_BUTTON):
            CycleSlot(1);
            break;
        case (L1_BUTTON | SELECT_BUTTON):
            sky = sky - 0x200;
            break;
        case (R1_BUTTON | SELECT_BUTTON):
            sky = sky + 0x200;
            break;
        case (L1_BUTTON | R1_BUTTON | SELECT_BUTTON):
            sky = 0;
            break;
        case (L2_BUTTON | R2_BUTTON | SELECT_BUTTON):
            if (_sparxHealth < 1 && sparx>1) {
                _sparxHealth = sparx-1;
                ptr_sparx = (*_createLevelObjectFunc)(0x78, *_updatedObjects);
            } else {
                _sparxHealth = sparx-1;
            }
            break;
    }

}

if (menuFlag)
{
    switch (combo)
    {
        case UP_BUTTON:
            MenuInput(DIR_UP);
            break;

        case DOWN_BUTTON:
            MenuInput(DIR_DOWN);
            break;
        case LEFT_BUTTON:
            MenuInput(DIR_LEFT);
            break;

        case RIGHT_BUTTON:
            MenuInput(DIR_RIGHT);
            break;

        case X_BUTTON:
            RunMenuAction();
            break;

        case L1_BUTTON:
            PrevMenu();
            break;

        case R1_BUTTON:
            NextMenu();
            break;
    }
}

    }
bool ButtonCombo(int buttons) {

    if (((_currentButtons.current & buttons) == buttons) && !((lastButtonCombo & buttons) == buttons)) {
        lastButtonCombo = buttons;
        return true;
    }
    else if ((_currentButtons.current & lastButtonCombo) != lastButtonCombo) {
        lastButtonCombo = NONE;
    }
    return false;
}


static const uint16_t comboMasks[] = {
    L1_BUTTON | R1_BUTTON | SELECT_BUTTON,
    L1_BUTTON | R1_BUTTON | SQUARE_BUTTON,
    L1_BUTTON | L2_BUTTON,
    L1_BUTTON | SELECT_BUTTON,
    L1_BUTTON | R1_BUTTON | CIRCLE_BUTTON,
    L1_BUTTON | R1_BUTTON | TRIANGLE_BUTTON,
    L2_BUTTON | R2_BUTTON | SELECT_BUTTON,
    L2_BUTTON | R2_BUTTON,
    R1_BUTTON | R2_BUTTON,
    R1_BUTTON | SELECT_BUTTON,
    SELECT_BUTTON | X_BUTTON,
    SELECT_BUTTON | TRIANGLE_BUTTON,

    L1_BUTTON,
    R1_BUTTON,
    L3_BUTTON,
    R3_BUTTON,
    SQUARE_BUTTON,
    CIRCLE_BUTTON,
    TRIANGLE_BUTTON,
    START_BUTTON,
    SELECT_BUTTON,
    UP_BUTTON,
    DOWN_BUTTON,
    LEFT_BUTTON,
    RIGHT_BUTTON,
    X_BUTTON,
};


int GetPressedCombo(void)
{
    for (int i = 0; i < sizeof(comboMasks)/sizeof(comboMasks[0]); i++)
        if (ButtonCombo(comboMasks[i]))
            return comboMasks[i];

    return 0;
}




// =========================
//  Menu Cycling L1/R1
// =========================

extern int selectedIndex;
extern int previousIndex;
extern int currentMenuIndex;
extern const int menuCount;
extern int flashCounter;

void NextMenu(void)
{
    currentMenuIndex++;
    if (currentMenuIndex == menuCount)
        currentMenuIndex = 0;

    selectedIndex = 0;
    previousIndex = -1;
}

void PrevMenu(void)
{
    currentMenuIndex--;
    if (currentMenuIndex < 0)
        currentMenuIndex = menuCount - 1;

    selectedIndex = 0;
    previousIndex = -1;
}

void ResetMenu(void) {
    currentMenuIndex = 0;
        selectedIndex    = 0;
        previousIndex    = -1;
        flashCounter     = 0;
}

#define SPARX_PTR_ADDR  0x80067028
#define SPYRO_ADDR      0x80069FF0

// 






