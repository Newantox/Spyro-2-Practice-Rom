#include <types.h>
#include <common.h>
#include <menu.h>



extern void LevelWarp(int index);
extern int menuFlag;

const GameMenu levelWarpMenu =
{
    NULL,
    GRID_COUNT,
    MENU_TYPE_GRID
};

extern const GameMenu levelWarpMenu;

#define STR_SUMMER_FOREST   ((char*)0x800106e0)
#define STR_GLIMMER         ((char*)0x80066ea0)
#define STR_IDOL_SPRINGS    ((char*)0x800106d0)
#define STR_COLOSSUS        ((char*)0x800106c4)
#define STR_HURRICOS        ((char*)0x800106b8)
#define STR_AQUARIA_TOWERS  ((char*)0x800106a8)
#define STR_SUNNY_BEACH     ((char*)0x8001069c)
#define STR_OCEAN_SPEEDWAY  ((char*)0x8001068c)
#define STR_CRUSHS_DUNGEON  ((char*)0x8001067c)
#define STR_AUTUMN_PLAINS   ((char*)0x8001066c)
#define STR_SKELOS_BADLANDS ((char*)0x8001065c)
#define STR_CRYSTAL_GLACIER ((char*)0x8001064c)
#define STR_BREEZE_HARBOR   ((char*)0x8001063c)
#define STR_ZEPHYR          ((char*)0x80066e98)
#define STR_METRO_SPEEDWAY  ((char*)0x8001062c)
#define STR_SCORCH          ((char*)0x80066e90)
#define STR_SHADY_OASIS     ((char*)0x80010620)
#define STR_MAGMA_CONE      ((char*)0x80010614)
#define STR_FRACTURE_HILLS  ((char*)0x80010604)
#define STR_ICY_SPEEDWAY    ((char*)0x800105f4)
#define STR_GULPS_OVERLOOK  ((char*)0x800105e4)
#define STR_WINTER_TUNDRA   ((char*)0x800105d4)
#define STR_MYSTIC_MARSH    ((char*)0x800105c4)
#define STR_CLOUD_TEMPLES   ((char*)0x800105b4)
#define STR_ROBOTICA_FARMS  ((char*)0x80010594)
#define STR_METROPOLIS      ((char*)0x80010588)
#define STR_CANYON_SPEEDWAY ((char*)0x800105a4)
#define STR_RIPTOS_ARENA    ((char*)0x80010568)
#define STR_DRAGON_SHORES   ((char*)0x80010578)
#define STR_RELOAD_LEVEL   ((char*)0x80010578)

const char* levelNames[] =
{
    STR_SUMMER_FOREST,
    STR_GLIMMER,
    STR_IDOL_SPRINGS,
    STR_COLOSSUS,
    STR_HURRICOS,
    STR_AQUARIA_TOWERS,
    STR_SUNNY_BEACH,
    STR_OCEAN_SPEEDWAY,
    STR_CRUSHS_DUNGEON,
    STR_AUTUMN_PLAINS,
    STR_SKELOS_BADLANDS,
    STR_CRYSTAL_GLACIER,
    STR_BREEZE_HARBOR,
    STR_ZEPHYR,
    STR_METRO_SPEEDWAY,
    STR_SCORCH,
    STR_SHADY_OASIS,
    STR_MAGMA_CONE,
    STR_FRACTURE_HILLS,
    STR_ICY_SPEEDWAY,
    STR_GULPS_OVERLOOK,
    STR_WINTER_TUNDRA,
    STR_MYSTIC_MARSH,
    STR_CLOUD_TEMPLES,
    STR_CANYON_SPEEDWAY,
    STR_ROBOTICA_FARMS,
    STR_METROPOLIS,    
    STR_DRAGON_SHORES,
    STR_RIPTOS_ARENA,
    STR_RELOAD_LEVEL,

};

extern char hasValidState1;
extern char hasValidState2;
extern char hasValidState3;
extern char setLives;

void LevelWarp(int gridIndex) {
    *(char*)0x8006b084 = 1;
   if(gridIndex == 29) {
    resetCheckpoint();
    } else {
    int targetID = LEVEL_ID_ARRAY[gridIndex];

    for(int i = 0; i < 32; i++)
        _parentHomeworldArray[i] = targetID;

    _cameraZ = 0x50000;
    _zoe_checkpoint_active = 0;
    _lives = -1;
    _menuAnimation = 0x11;
    setLives = 0;
    GAME_GameOver();
    hasValidState1 = 0;
    hasValidState2 = 0;
    hasValidState3 = 0;
    }
    ResetMenu();
    lookToStartTimer = 1;
    menuFlag = 0;
    _updateFlags = 0x7b;
}

///// COMMENTED OUT TO SAVE SPACE, WORKS FINE //////////

#define ADDRESS_TO_HOOK 0x80073548
#define ORIGINAL_PATTERN 0x3C028007
#define NEW_JUMP 0x0801CE14

#define MENU_ANIMATION_BRANCH 0x800738d0
#define START_BUTTON_BRANCH 0x800738a0
#define GLIMMER_CHECK_BRANCH 0x8001cb14
#define JUMP_TO_LIVES 0x080072e9

#define NOP 0x0

void ChangeGameOver(void)
{
    // If the gameover overlay code is loaded, force the beginning code that handles
    // updating the animations of the menu and spyro to be skipped, and go straight to
    // level loading. Then, skip the check for the start button, to force it to load the
    // moment its allowed to.
    *((u32*)GLIMMER_CHECK_BRANCH) = JUMP_TO_LIVES;

    bool isOverlayLoaded = *((u32*)ADDRESS_TO_HOOK) == ORIGINAL_PATTERN && _menuAnimation > 0 ;
    if (isOverlayLoaded)
    {
        *((u32*)ADDRESS_TO_HOOK) = NEW_JUMP;
        *((u32*)ADDRESS_TO_HOOK + 1) = NOP;  // Clear the branch delay

        *((u32*)MENU_ANIMATION_BRANCH) = NOP;
        *((u32*)START_BUTTON_BRANCH) = NOP;
    }
}

