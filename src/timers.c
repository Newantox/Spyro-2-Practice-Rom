#include <common.h>

int timer;
int dialogueTime;
int endTime;
int vTimer = 0;
int vTimerStart = 0;
char timerAscii[10];
char timerAscii2[10];
char timerAscii3[10];
int lookToStartTimer = 0;
int inTalkbox;
int inTalkbox2;

void mainTimers() {
	timer = timer + 1;
	if(lookToStartTimer == 1 && _gameState == 0) {
		vTimerStart = _vsync(-1);
		lookToStartTimer = 0;
	}
	if (_gameState == 1) {
		if (inTalkbox ==0) {
			dialogueTime = vTimer;
			inTalkbox = 1;
		}
	}
	if (_gameState == 0) {
		inTalkbox = 0;
        inTalkbox2 = 0;
	}
    if (_gameState == 7 && _unkLeaveLevel==1) { //(_menuAnimation >= 0x100d || _unkLeaveLevel==1)
        printf("Condition\n");
        if (inTalkbox2 ==0) {
            endTime = vTimer;
            printf("End Time: %d\n", endTime);
            inTalkbox2 = 1;
        }
    }
    
	vTimer = _vsync(-1) - vTimerStart;
    DisplayTime(vTimer,0);
    //if (_gameState == 0 || _gameState == 1) DisplayTime(vTimer,0);
	if (_gameState == 1) DisplayTime(dialogueTime,1);
    if (_gameState == 7 || _gameState == 6)  DisplayTime(endTime,2);
}

void DisplayTime(int vTimer , int type) {
	int minutes = vTimer * 10 / 35892;
	int secondsTens = ((vTimer * 10) % 35892) / 5982;
	int secondsUnits = ((vTimer * 100) % 59820) / 5982;
	int milliseconds = ((vTimer * 1000) % 59820) / 5982;
	int milliseconds2 = ((vTimer * 10000) % 59820) / 5982;

	if (minutes == 0) {
		if (type==0) sprintf(timerAscii, "%d%d.%d%d", secondsTens, secondsUnits, milliseconds, milliseconds2);
		else if (type==1) sprintf(timerAscii2, "%d%d.%d%d", secondsTens, secondsUnits, milliseconds, milliseconds2);
        else if (type==2) sprintf(timerAscii3, "%d%d.%d%d", secondsTens, secondsUnits, milliseconds, milliseconds2);
	}
	else {
		if (type==0) sprintf(timerAscii, "%d:%d%d.%d%d", minutes, secondsTens, secondsUnits, milliseconds, milliseconds2);
		else if (type==1) sprintf(timerAscii2, "%d:%d%d.%d%d", minutes, secondsTens, secondsUnits, milliseconds, milliseconds2);
        else if (type==2) sprintf(timerAscii3, "%d:%d%d.%d%d", minutes, secondsTens, secondsUnits, milliseconds, milliseconds2);
	}
	if (type == 0) {
		_DrawOutlinedBG(0,93,201,216);
		_DrawNumberSmall(vTimer, 90, 305, 1);
		_DrawText_Right(timerAscii, 90, 205, 1);
	}
	else if (type == 1) {
		_DrawNumberSmall(vTimer, 90, 290, 10);
		_DrawText_Right(timerAscii2, 90, 190, 10);
	}
    else if (type == 2) {
		_DrawNumberSmall(vTimer, 90, 290, 5);
		_DrawText_Right(timerAscii3, 90, 190, 5);
	}
}