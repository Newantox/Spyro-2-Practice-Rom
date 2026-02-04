#include <types.h>
#include <symbols.h>
#include <syscalls.h>
#include <common.h>

// Only globals that must persist
int vTimerStart = 0;
int dialogueTime = 0;
int lookToStartTimer = 0;
int inTalkbox = 0;

extern char promptBonk;
extern char promptTalk;
extern char promptGround;
extern char timerVisibility;
extern menuFlag;
int grounded = 0;

void DisplayTime(int vTimer, int type, int color);

void Timers()
{   
    grounded++;

    // Start timer when requested
    if (lookToStartTimer == 1 && _gameState == 0) {
        vTimerStart = _vsync(-1);
        lookToStartTimer = 0;
    }

    // Dialogue timing logic - functionality flawed if immediately transition from one to another, time doesn't update.
    if (_gameState == 1 || (_gameState == 0 && _spyroAnimation == 0xD) || (_gameState ==7) || menuFlag || (grounded < 60 && _spyroAirTime < 10)) {
        if (!inTalkbox) {
            dialogueTime = _vsync(-1) - vTimerStart;
            inTalkbox = 1;
        }
    } else {
        inTalkbox = 0;
    }

    // Compute vTimer only when needed
    int vTimer = _vsync(-1) - vTimerStart;


    // Draw main timer
    if (_gameState < 2 && timerVisibility == 1) {
        DisplayTime(vTimer, 0, 1);
        if (menuFlag) DisplayTime(dialogueTime, 1, 3);
    } else if(_gameState == 7) {
        DisplayTime(dialogueTime, 1, 3);
    }

    // Draw prompt timers
    if (promptTalk && _gameState == 1)
        DisplayTime(dialogueTime, 1, 4);

    if (promptBonk && _spyroAnimation == 0xD && _gameState == 0)
         DisplayTime(dialogueTime, 1, 5);


    if (_spyroAirTime > 10) grounded = 0;
    
    if (promptGround && grounded <60 && _spyroAirTime < 10 && _gameState == 0)
         DisplayTime(dialogueTime, 1, 6);
}

void DisplayTime(int vTimer, int type, int color)
{
    int t = vTimer * 10;

    int minutes = t / 35892;
    int rem = t % 35892;

    int secondsTens = rem / 5982;
    rem %= 5982;

    int secondsUnits = (vTimer * 100 % 59820) / 5982;
    int ms1 = (vTimer * 1000 % 59820) / 5982;
    int ms2 = (vTimer * 10000 % 59820) / 5982;

    // "M:SS.xx"
    char buf[8];
    buf[0] = '0' + minutes;
    buf[1] = ':';
    buf[2] = '0' + secondsTens;
    buf[3] = '0' + secondsUnits;
    buf[4] = '.';
    buf[5] = '0' + ms1;
    buf[6] = '0' + ms2;
    buf[7] = 0;

    int x = (type == 0) ? 85 : 175;

    _DrawNumberSmall(vTimer, x, 317, color);
    _DrawText_Right(buf, x, 217, color);
}
