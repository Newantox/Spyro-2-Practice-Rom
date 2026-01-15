#include <common.h>
#include <math.h>

char menuOpen;
char index;
struct Menu* currentMenu;
int startDraw;
char slowMotion;
char timeStop;
extern bool djflag;
extern int proxyModifier;
extern int waterModifier;


const int CustomCheatColors[7] = { 8,5,9,10,4,1,11 };

void SetMenu(Menu* menuAddress) {
	currentMenu = menuAddress;
}

void MenuToggle() {
	menuOpen = 1 - menuOpen;
	index = 0;
	startDraw = 0;
	if (menuOpen == 1) {
		_updateFlags = 0;
	}
	else if (slowMotion || timeStop) {
		_updateFlags = 0x18;
	}
	else {
		_updateFlags = 0x7b;
	}
}

void FireballToggle() {
	_fireballFlag = 1 - _fireballFlag;
	_testfunction;
}

void SubMenu(Menu* submenu) {
	currentMenu = submenu;
	index = 0;
	startDraw = 0;
}

void SlowMotion() {
	slowMotion = 1 - slowMotion;
}

void TimeStop() {
	timeStop = 1 - timeStop;
}

char* defaultColorString = "Color: Default";
char* redColorString = "Color: Red    ";
char* blueColorString = "Color: Blue   ";
char* pinkColorString = "Color: Pink   ";
char* greenColorString = "Color: Green  ";
char* yellowColorString = "Color: Yellow ";
char* blackColorString = "Color: Black  ";

char* colorString = "Color: Default";

void ColorSlider(int subindex) {
	switch (subindex) {
		case 0:
		colorString = defaultColorString;
		break;
		case 1:
		colorString = redColorString;
		break;
		case 2:
		colorString = blueColorString;
		break;
		case 3:
		colorString = pinkColorString;
		break;
		case 4:
		colorString = greenColorString;
		break;
		case 5:
		colorString = yellowColorString;
		break;
		case 6:
		colorString = blackColorString;
	}
	_cheatSpyroColor = subindex;
	currentMenu->items[index].name = colorString;
}

void MBToggle(int subindex) {
	switch (subindex) {
		case 0:
		currentMenu->items[index].name = "Off";
		break;
		case 1:
		currentMenu->items[index].name = "On";
		break;
	}
	glacierbridge = subindex;
	aquariasub = subindex;
	magmalift = subindex;
	glimmerbridge = subindex;
	swim = subindex;
	climb = subindex;
	headbash = subindex;
	aquariawall = subindex;
	zephyr = subindex;
	shady = subindex;
	icy = subindex;
	canyon = subindex;
}

void DoubleJumpToggle() {
	djflag = 1 - djflag;
}

void ERToggle() {
	erflag = 1 - erflag;
}


Menu menu = { 0, 6, {
    { "Continue", &MenuToggle, BUTTON, 0 },
    { "Fireball", &FireballToggle, BUTTON, 0 },
	{ "Extended Range", &ERToggle, BUTTON, 0 },
    { "Moneybags Paid", &MBToggle, 2, 0 },
//	{ "Satyrless Tools", &SatyrlessToggle, BUTTON, 0 },
    { "Double Jump", &DoubleJumpToggle, BUTTON, 0 },
    { "Color: Default", &ColorSlider, 7, 0 },
} };

Menu menu2 = { &menu, 2, {
    { "Continue", &MenuToggle, BUTTON, 0 },
    { "Fireball", &FireballToggle, BUTTON, 0 },
    //{ "Proxy Strength: 5   ", &ProxySlider, 11, 5 },
   // { "Water jump strength: 1   ", &WaterSlider, 11, 1 }
} };


void PauseMenu() {
	if (menuOpen) {
		DrawText("*", 5, 20 + 10 * (index - startDraw), 2, 0);
		if (currentMenu->length < 7) {
			for (int j = 0; j < currentMenu->length; j++) {
				if (StringMatch("Color: ", currentMenu->items[j].name, 7)) {
					char* output1;
					char* output2;
					DrawText(SubString(currentMenu->items[j].name, 0, 7, output1), 25, 20 + 10 * j, 2, 0);
					DrawText(SubString(currentMenu->items[j].name, 7, 8, output2), 85, 20 + 10 * j, CustomCheatColors[currentMenu->items[j].subIndex], 0);
				}
				else {
					DrawText(currentMenu->items[j].name, 25, 20 + 10 * j, 2, 0);
				}
			}
		}
		else {
			for (int j = startDraw; j < startDraw + 6; j++) {
				if (StringMatch("Color: ", currentMenu->items[j].name, 7)) {
					char* output1;
					char* output2;
					DrawText(SubString(currentMenu->items[j].name, 0, 7, output1), 25, 20 + 10 * (j - startDraw), 2, 0);
					DrawText(SubString(currentMenu->items[j].name, 7, 8, output2), 85, 20 + 10 * (j - startDraw), CustomCheatColors[currentMenu->items[j].subIndex], 0);
				}
				else {
					DrawText(currentMenu->items[j].name, 25, 20 + 10 * (j - startDraw), 2, 0);
				}
			}
		}

		if (ButtonCombo(DOWN_BUTTON)) {
			index = index + 1;
			if (index > currentMenu->length - 1) {
				index = 0;
				startDraw = 0;
			}
			else if (index > startDraw + 5) {
				if (!(currentMenu->length < 7)) startDraw = startDraw + 1;
			}
		}
		if (ButtonCombo(UP_BUTTON)) {
			index = index - 1;
			if (index < 0) {
				index = currentMenu->length - 1;
				if (!(currentMenu->length < 7)) startDraw = currentMenu->length - 6;
			}
			else if (index < startDraw) {
				if (!(currentMenu->length < 7)) startDraw = startDraw - 1;
			}
		}
		if (ButtonCombo(LEFT_BUTTON)) {
			if (currentMenu->items[index].subOptions > -1) {
				currentMenu->items[index].subIndex = (currentMenu->items[index].subIndex - 1);
				if (currentMenu->items[index].subIndex < 0) {
					currentMenu->items[index].subIndex = currentMenu->items[index].subOptions - 1;
				}
				void (*pointer) (int);
				pointer = currentMenu->items[index].menuAction;
				pointer(currentMenu->items[index].subIndex);
			}
		}
		if (ButtonCombo(RIGHT_BUTTON)) {
			if (currentMenu->items[index].subOptions > -1) {
				currentMenu->items[index].subIndex = (currentMenu->items[index].subIndex + 1) % (currentMenu->items[index].subOptions);
				void(*pointer) (int);
				pointer = currentMenu->items[index].menuAction;
				pointer(currentMenu->items[index].subIndex);
			}
		}
		if (ButtonCombo(X_BUTTON)) {
			printf("%d \n", currentMenu->items[index].subIndex);
			if (currentMenu->items[index].subOptions == SUBMENU) {
				void (*pointer) (Menu*);
				pointer = currentMenu->items[index].menuAction;
//				pointer(&menu3);
			}
			else if (currentMenu->items[index].subOptions > -1) {
				currentMenu->items[index].subIndex = (currentMenu->items[index].subIndex + 1) % (currentMenu->items[index].subOptions);
				void (*pointer) (int);
				pointer = currentMenu->items[index].menuAction;
				pointer(currentMenu->items[index].subIndex);
			}
			else if (currentMenu->items[index].subOptions == BUTTON) {
				void (*pointer) ();
				pointer = currentMenu->items[index].menuAction;
				pointer();
			}
		}
		if (ButtonCombo(TRIANGLE_BUTTON)) {
			if (currentMenu->parentmenu == 0) {
				MenuToggle();
			}
			else {
				currentMenu = currentMenu->parentmenu;
			}
		}
	}
}


		//_DrawOutlinedBG(50,600,50,200);
		/*_DrawText_Right("Continue",200,40,2);
		_DrawText_Right("Yes",200,80,2);
		_DrawText_Right("No",200,120,2);
		_DrawText_Right("Maybe",200,160,2);
		_DrawText_Right("*",300,40+40*index,2);
		if(ButtonCombo(DOWN_BUTTON)) {
			index = (index + 1) & 3;
		}
		if (ButtonCombo(UP_BUTTON)) {
			index = (index - 1) & 3;
		}
		if (ButtonCombo(X_BUTTON)) {
			MenuAction(index);
		}
	}
}*/