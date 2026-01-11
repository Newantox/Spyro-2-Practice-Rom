#include <common.h>
#include <types.h>
#include "stdbool.h"

int buttons;
int spare;
Vector tempVec;
int flag1 = FALSE;
char myBuffer[10];
int timer;
int vTimer = 0;
int vTimerStart = 0;
int minutes;
int secondsTens;
int secondsUnits;
int milliseconds;
int milliseconds2;
int isWarping = FALSE;
char timerAscii[10];
int savestatemade = 0;

int first = true;

extern char slowMotion;
extern char timeStop;

extern Menu menu;
extern Menu menu2;
extern Menu menu3;

void mainFunction() {
	if (first) {
		_colorArray[8] = 0x64bc0052;
		_colorArray[9] = 0x64ff0007;
		_colorArray[10] = 0x64da7dc2;
		_colorArray[11] = 0x64000000;
		first = false;
		tempVec.x = 0x1d270;
		tempVec.y = 0x1d283;
		tempVec.z = 0x4486;
	}
	timer = timer + 1;
	vTimer = _vsync(-1) - vTimerStart;

	_RenderGame();
	if (slowMotion) {
		if (_updateFlags == 0x18 && (timer % 2 == 0)) {
			_updateFlags = 0x7b;
		}
		else if (_updateFlags == 0x7b) {
			_updateFlags = 0x18;
		}
	}
	if (timeStop) {
		if (_updateFlags == 0x7b) {
			_updateFlags = 0x18;
		}
	}
	if (ButtonCombo(L2_BUTTON + R2_BUTTON)) {
		SetMenu(&menu);
		MenuToggle();
	}
	if (ButtonCombo(SQUARE_BUTTON + L2_BUTTON)) {
		SetMenu(&menu2);
		MenuToggle();
	}
	if (ButtonCombo(L1_BUTTON + R1_BUTTON + X_BUTTON)) {
		if (isWarping == FALSE) {
			//isWarping = TRUE;
			LevelWarp(0x42);
		}

			//_menuAnimation = 17;
			//_splashTransition = 5;
			//_gameState = 4;
		//}
	}

	ChangeGameOver();

	if (ButtonCombo(L1_BUTTON + SQUARE_BUTTON + TRIANGLE_BUTTON)) {
		if (isWarping == FALSE) {
			isWarping = TRUE;
			_menuAnimation = 17;
			_splashTransition = 5;
			_gameState = 4;
		}
	}

	if (_levelID == 2) {
		_idolChestX = 0x1D784;
		_idolChestY = 0xE1D7;
		_idolChestZ = 0x17C0;
	}

	if (isWarping) {
		if (_gameState == 0) {
			_zoe_checkpoint_active = 0;

		// Reset worlds entered
			LIBC_bzero((unsigned char*)&GAME_worlds_entered, 0x20);

			_pause_submenu_index = 0;
			_menuAnimation = 0;
			_gameState = 3;
			_menuState = 0;

			vTimerStart = _vsync(-1);

			isWarping = 0;
		}

		//	_menuAnimation = 17;
		//	_splashTransition = 5;
		//	_gameState = 4;
	}

	  //  _loadLevelID = 26;

		//if (_gameState == 5) {
		//	_menuAnimation = 17;
		//	_splashTransition = 5;
		//	_gameState = 7;
		//}

	   // if (_gameState == 0) {
	   //     isWarping = 0;
	   // } 

		//else if (_gameState == 7) {
		//	if ((_loadLevelID == 26 || _loadLevelID == 46 || _loadLevelID == 66) && (cam_bossfix == 0x7404 || cam_bossfix == 0xc9b3 || cam_bossfix == 0x11a75)) {
		//		isWarping = 0;
		//	_menuAnimation = 0;
		//		_pause_submenu_index = 0;
		//		_menuState = 2;
		//		_gameState = 3;
		//		_unknownTransition = 1;
			//}
			// crush, gulp, ripto starting cams respectively
			//int is_boss_level_start = (cam_bossfix == 0x7404 || cam_bossfix == 0xc9b3 || cam_bossfix == 0x11a75); //&& rs2.warp_selected_level.type == BOSS;
			// home world starting cams respectively
			//int is_homeworld_level_start = (cam_homefix == 0xFFFFFDEF || cam_homefix == 0x0402 || cam_homefix == 0x0401); //&& rs2.warp_selected_level.type == HOMEWORLD;

		   //if (is_boss_level_start || is_homeworld_level_start) {
			 //   _menuAnimation = 0;
			 //   _gameState = 3;
			 //   _pause_submenu_index = 0;
			 //   _menuState = 0;
			//}//
	//	}
	//}

	if (ButtonCombo(R3_BUTTON)) {
		SaveState();
		savestatemade = 1;
	}

	if (ButtonCombo(L3_BUTTON)) {
		if (savestatemade == 1) LoadState();
	}

	if (ButtonCombo(L1_BUTTON + R1_BUTTON + TRIANGLE_BUTTON + CIRCLE_BUTTON)) {
		_zoe_checkpoint_active = 0;
		//memset(_checkpointStorage,0,0x248);
		//memset(_checkpointData,0,0x248);

		//Reset orbs
		GAME_orbs_collected_count = 0;
		LIBC_bzero((unsigned char*)&GAME_orbs_collected_status, 0x20);

		//Reset EoL
		GAME_num_talismans = 0;
		LIBC_bzero((unsigned char*)&GAME_end_level_portals_status, 0x1c);

		// Reset gems
		GAME_gems_collected_value = 0;
		LIBC_bzero((unsigned char*)&GAME_world_gems_collected, 0x80);
		LIBC_bzero((unsigned char*)&GAME_gems_collected_status, 0x400);

		// Reset worlds entered
		LIBC_bzero((unsigned char*)&GAME_worlds_entered, 0x20);

		// Reset NPCs
		LIBC_bzero((unsigned char*)&GAME_NPC_talked_flags, 0x20);

		// Reset stuff
		LIBC_bzero((unsigned char*)&GAME_crushDeathCounter, 0x8);
		LIBC_bzero((unsigned char*)&GAME_unknown_boss_thing, 0x20);

		//Reset Global Progress Flags
		LIBC_bzero((unsigned char*)&GAME_global_progress_flags, 0x9a);

		//Reset skill points
		GAME_total_skillpoints = 0;
		LIBC_bzero((unsigned char*)&GAME_skillpoint_flags, 0x20);

		ClearWorldStuffTest();
		
		//Reset unknown
		//GAME_unknown_prog

		_sparxHealth = 3;
		_pause_submenu_index = 0;
		_menuAnimation = 0;
		_gameState = 3;
		_menuState = 0;

		vTimerStart = _vsync(-1);
	}

	//ToggleFireball();
	//TempText();
	PauseMenu();
	if (_currentButtons.pressed != 0) {
		//_DrawText_Right("pressed", 200, 200, 4);
	}
	else {
		//_DrawText_Right("not pressed", 200, 200, 6);
	}
	//_DrawNumberSmall(vTimer,400,200,0);
	DisplayTime(vTimer);
	return;
}

void DisplayTime(int vTimer) {
	minutes = vTimer * 10 / 35892;
	secondsTens = ((vTimer * 10) % 35892) / 5982;
	secondsUnits = ((vTimer * 100) % 59820) / 5982;
	milliseconds = ((vTimer * 1000) % 59820) / 5982;
	milliseconds2 = ((vTimer * 10000) % 59820) / 5982;

	if (minutes == 0) {
		sprintf(timerAscii, "%d%d.%d%d", secondsTens, secondsUnits, milliseconds, milliseconds2);
	}
	else {
		sprintf(timerAscii, "%d:%d%d.%d%d", minutes, secondsTens, secondsUnits, milliseconds, milliseconds2);
	}
	//_DrawNumberSmall(vTimer, 400, 300, 1);
	//_DrawText_Right(timerAscii, 400, 200, 1);
}

void* memcopy(void* dest, const void* src, int len) {
	char* d = dest;
	const char* s = src;
	while (len--) {
		*d++ = *s++;
	}
	return dest;
}

void ClearWorldStuffTest()
{
*(u32*)0x80067008 = 0;
*(u32*)0x80067100 = 0;
*(u32*)0x8006701C = 0;

*(u32*)0x80066FA8 = 0;  

*(u32*)0x80067084 = 0;
*(u32*)0x80067088 = 0;
*(u32*)0x8006708C = 0;

*(u32*)0x80066F30 = 0;
*(u32*)0x80066EF8 = 0;  
*(u32*)0x80066EFC = 0;
*(u32*)0x80066F50 = 0;
*(u32*)0x80067038 = 0;
*(u32*)0x800670F4 = 0;

*(u32*)0x80067148 = 0;
*(u32*)0x80066ff0 = 0;
*(u32*)0x80066f44 = 0;
*(u32*)0x80066ff4 = 0;

*(u8*)0x8006AC01 = 0;
*(u8*)0x8006AC00 = 0;
*(u8*)0x8006ABFF = 0;
*(u8*)0x8006ABFE = 0;
*(u8*)0x8006ABFD = 0;
*(u8*)0x8006ABFC = 0;
*(u8*)0x8006ABFB = 0;
*(u8*)0x8006ABFA = 0;
*(u8*)0x8006ABF9 = 0;
*(u8*)0x8006ABF8 = 0;

*(u32*)0x80066FD0 = 0;
*(u32*)0x80066F3C = 0;
*(u32*)0x80067EC4 = 0;

memset(0x8006aa1c, 0, 0x130);
}

/* void ToggleFireball() {
	ButtonCombo(L2_BUTTON + R2_BUTTON,&flag1);

	if (flag1) {
		_fireballFlag = 1 - _fireballFlag;
		if (_fireballFlag) {
			StartTempText(600,"Fireball",12);
		} else {
			StartTempText(600,"Flame",2);
		}
	}
}*/