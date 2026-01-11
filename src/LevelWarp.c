#include <types.h>
#include <common.h>

#define ADDRESS_TO_HOOK 0x80073548
#define ORIGINAL_PATTERN 0x3C028007
#define NEW_JUMP 0x0801CE14

#define MENU_ANIMATION_BRANCH 0x800738d0
#define START_BUTTON_BRANCH 0x800738a0
#define GLIMMER_CHECK_BRANCH 0x8001cb14
#define JUMP_TO_LIVES 0x080072e9

#define NOP 0x0

void LevelWarp(int targetID)
{
    for(int i = 0; i < 13; i++) {
        _parentHomeworldArray[i] = targetID;
    }
    _zoe_checkpoint_active = 0;
	_lives = -1;
    _menuAnimation = 0x11;
	GAME_GameOver();
}

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