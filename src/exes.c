#include <types.h>
#include <symbols.h>
#include <syscalls.h>
#include <common.h>
//#include <stdint.h>

// =========================
//  Executable Menu Actions // Definitely better to move this to its own file later
// =========================
extern int sparxless;
extern int doubleJump;
extern char swimFlag;
extern char climbFlag;
extern char headbashFlag;
extern char rangeFlag;
extern char superflameFlag;
extern char abilityMode;
extern char zoeZaps;
extern char zoeRespawnsInRipto;
extern char powerupsOn;
extern char autoMinigames;
extern char sparx;
extern char inLevel;
extern char levelEntry;
extern char bosses;
extern char homeworlds;
extern int32_t gemValue;
extern int32_t orbValue;
extern int32_t taliValue;
extern int32_t fodderValue;
extern int32_t mbagsValue;
extern char satyrlessPrompt;
char satyrlessTxt[10];
extern char temple;

void ManageAbilities() {
    swim = swimFlag;
    climb = climbFlag;
    headbash = headbashFlag;
    erflag = rangeFlag;
    _fireballFlag = superflameFlag; 
}

void ManageUnlocks () {
    *(short*)0x80064672 = inLevel; //glacier bridge
    *(short*)0x80064676 = inLevel;//aquaria sub
    *(short*)0x8006467A = inLevel;//magma lift
    *(short*)0x8006467e = inLevel;//glimmer bridge
    *(short*)0x8006468e = levelEntry; //aquaria level
    *(short*)0x8006469a = levelEntry; //zephyr level
    *(short*)0x8006468e = levelEntry; //shady level
    *(short*)0x800646a2 = levelEntry; //icy level
    *(short*)0x800646ba = levelEntry; //canyon level
    *(short*)0x800646f2 = levelEntry; //metro level
    *(short*)0x800646ee = levelEntry; //ocean level
    *(short*)0x8006b09e = levelEntry; //metrop level
    *(short*)0x8006B09B = levelEntry; //cloud level
    *(char*)0x8006B08C = bosses; // crush
    *(char*)0x8006B098 = bosses; // gulp
    *(char*)0x8006B0A0 = bosses; // ripto
    if (_gameState == 3) {
        *(char*)0x8006B08d = homeworlds; // AP
        *(char*)0x8006B099 = homeworlds; // WT
    }
}

void ManageValues() {
    GAME_gems_collected_value = gemValue;
    GAME_orbs_collected_count = orbValue;
    _fodderUntilLife = 10-fodderValue;
    ManageMoneybags();
}

void MenuActions(void)
{
    if (sparxless)
        _sparxHealth = 0;
    if (abilityMode == 0) ManageAbilities();
    ManageUnlocks();
    SatyrlessTools();

    *(short*)0x80064794 = !zoeRespawnsInRipto;
    if (powerupsOn) *(char*)0x80066EFC = 0x30;
    if(autoMinigames) {
        *(char*)0x801984B4 = 0xA;
    }
}
// // checkpoint patch - 
// // not working correctly, saving whilst disabled somehow loses the existing checkpoint

void SatyrlessTools() {
    if (_currentLoadedLevel == 0x2c && satyrlessPrompt && _gameState < 2) {
        DrawSatylress();

        if (ButtonCombo(START_BUTTON) || temple) {
            *(char*)0x800B34FD = 1;
            *(char*)0x80193339 = 1;
            *(char*)0x800b3510 = 0x0A;
            *(char*)0x800b3512 = 0x0A;
    }
    }

}



void DrawSatylress() {
    if ((*(char*)0x800b3512) == 0x0A || temple) {
        sprintf(satyrlessTxt, "Faun Active");
        _DrawText_Right(satyrlessTxt, 370, 217, 4);
    } else {
        sprintf(satyrlessTxt, "Faun Inactive");
        _DrawText_Right(satyrlessTxt, 370, 217, 5);
    }
    
}

void Action_ZoeZaps()
{ 
    volatile uint32_t *code = (volatile uint32_t *)0x8004c0c8;

    zoeZaps ^= 1;
    if (!zoeZaps)
    {
        // Patch: return
        code[0] = 0x03e00008;
        code[1] = 0x00000000;
    }
    else
    {
        // Restore original instructions
        code[0] = 0x27BDFFD8;
        code[1] = 0xAFB20018;

     }
}

void ManageMoneybags()
{
    if (mbagsValue) // = 0
    {
        // normal instructions
    *(int*)0x8003A35C = 0x34020000;
    *(int*)0x8003A38C = 0x34030000;
    *(int*)0x8003A6cc = 0x34030000;
    *(int*)0x8003A6F4 = 0x34030000;
    }
    else
    {
        // new instructions
    *(int*)0x8003A35C = 0x84224670;
    *(int*)0x8003A38C = 0x84234670;
    *(int*)0x8003A6cc = 0x84234670;
    *(int*)0x8003A6F4 = 0x84234670;;
     }
}



