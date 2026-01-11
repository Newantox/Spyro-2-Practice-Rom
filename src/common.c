#include <common.h>
#include "math.h"
#include "stdbool.h"




int lastButtonCombo = NONE;


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

/*bool ButtonCombo(int buttons) {
    return ((_currentButtons.pressed & buttons) == buttons);
}*/

int tempTextTimer = 0;
char* tempText;
int tempTextColor;

void StartTempText(int time, char* s, int color) {
    tempTextTimer = time;
    tempText = s;
    tempTextColor = color;
}

void TempText() {
    char tempBuffer[16];
    if (tempTextTimer > 0) {
        sprintf(tempBuffer, "%s", tempText);
        DrawText(tempBuffer, 0x09, 0xd6, tempTextColor, 0);
        tempTextTimer--;
    }
}

bool StringMatch(char* s1, char* s2, int i) {
    for (int j = 0; j < i; j++) {
        printf("%s \n", s2);
        if (s1[j] != s2[j]) {
            printf("%c", s1[j]);
            printf("%c \n", s2[j]);
            return false;
        }
    }
    printf("%d \n", 1);
    return true;
}

char* SubString(char* s, int start, int length, char* output) {
    for (int j = 0; j < length; j++) {
        output[j] = s[j + start];
    }
    output[length] = '\0';
    return output;
}