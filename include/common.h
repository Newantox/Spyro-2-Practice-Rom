#ifndef COMMON_H
#define COMMON_H

//typedef int bool;

#define FALSE 0
#define TRUE 1

#define NULL (void*) 0

#define BUTTON -1
#define SUBMENU -2
#define GRID_COUNT 30


void MenuActions(void);
typedef unsigned char byte;

void DrawSync(int x);

typedef struct Vector
{
    int x;
    int y;
    int z;
}Vector;

struct InputState
{
    int current;
    int pressed;
    int released;
    char rightStickAnalogX;
    char rightStickAnalogY;
    char leftStickAnalogX;
    char leftStickAnalogY;
};

typedef struct menuItem
{
    char* name;
    void* menuAction;
    short subOptions;
    short subIndex;
}menuItem;

typedef struct Menu {
    struct Menu* parentmenu;
    int length;
    menuItem items[16];
}Menu;

enum SpyroColor
{
    Normal = 0x0,
    Red = 0x1,
    Blue = 0x2,
    Pink = 0x3,
    Green = 0x4,
    Yellow = 0x5,
    Black = 0x6
};

enum InputFlags
{
    NONE = 0x0000,
    X_BUTTON = 0x0040,
    SQUARE_BUTTON = 0x0080,
    CIRCLE_BUTTON = 0x0020,
    TRIANGLE_BUTTON = 0x0010,

    UP_BUTTON = 0x1000,
    RIGHT_BUTTON = 0x2000,
    DOWN_BUTTON = 0x4000,
    LEFT_BUTTON = 0x8000,

    SELECT_BUTTON = 0x0100,
    START_BUTTON = 0x0800,

    R1_BUTTON = 0x0008,
    L1_BUTTON = 0x0004,
    R2_BUTTON = 0x0002,
    L2_BUTTON = 0x0001,

    L3_BUTTON = 0x0200,
    R3_BUTTON = 0x0400

};

enum AnalogFlags
{
    ANALOG_NONE  = 0,

    LSTICK_UP    = 1 << 0,
    LSTICK_RIGHT = 1 << 1,
    LSTICK_DOWN  = 1 << 2,
    LSTICK_LEFT  = 1 << 3,

    RSTICK_UP    = 1 << 4,
    RSTICK_RIGHT = 1 << 5,
    RSTICK_DOWN  = 1 << 6,
    RSTICK_LEFT  = 1 << 7
};


extern int* ptr_MobyArray;
extern byte* ptrToEndOfMobys;
extern int* ptr_DynamicMobyArray;
extern int count_DynamicMobys;
extern int* ptr_ParticleArray;
extern byte* _spyro;
extern int _cameraZ;

//void memcopy(void * target , void * values , int length);

void _RenderGame();

int* _OnWorldEnter(Vector* spawn);
extern Vector _maybeglobalSpawn;

void memset(int* start, int data, int len);

void _ProcessSpyroInput();

void LIBC_bzero(unsigned char* p, int n);

void _DrawOutlinedBG(short left, short right, short top, short bottom);
void _DrawDarkTransparentRect(short left, short right, short top, short bottom);

extern int _fodderUntilLife;
int printf(char* str, ...);
int sprintf(char* str, char* format, ...);
void DrawText(char* text, int x, int y, int colorIndex, int* unk);
void _DrawText_Right(char* text, int x, int y, int colorIndex);

void _VectorCopy(Vector* to, Vector* from);

void _PlayAudio(int id, int p2, int p3);

void GAME_GameOver();
void GAME_OnDeath();
int* GAME_OnWorldEnter(Vector* p1);

extern struct Vec3 speed;
extern int _gameState;
extern int _loadingStatus;
extern int _unknownGameOver;
void GAME_unknownGameOver();
void GAME_unknown79c();
extern int _currentLoadedLevel;
extern int _lives;
extern int _unknown_death;
extern int _unknown_death2;

extern struct InputState _currentButtons;
extern struct InputState _inputState;
extern char _fireballFlag;
extern char _updateFlags;
extern int _cheatSpyroColor;
extern int _colorArray[14];

extern int _spyroAnimation;

extern int _audioBank;

extern int _maybeSpyroHorizontalDecay;
extern int _spyroTrueVelocityX;
extern int _spyroTrueVelocityY;
extern int _spyroTrueVelocityZ;

extern int _spyroPhysicsVelocityX;
extern int _spyroPhysicsVelocityY;
extern int _spyroPhysicsVelocityZ;

extern int _spyroAirTime;

extern int _spyroDJRelatedUnk;

extern int _zoe_checkpoint_active;
extern int _menuAnimation;
extern int _pause_submenu_index;
extern int _menuState;
extern int _loadLevelID;
extern int cam_bossfix;
extern int cam_homefix;

int _vsync(int mode);
void _DrawNumberBig(int x, short y, int value);
void _DrawNumberSmall(int value, int x, short y, int colorIndex);

extern int _sparxHealth;
extern int GAME_orbs_collected_count;
extern int GAME_gems_collected_status;
extern int GAME_world_gems_collected;
extern int GAME_orbs_collected_status;
extern int GAME_end_level_portals_status;
extern int GAME_num_talismans;
extern int GAME_global_progress_flags;
extern int GAME_gems_collected_value;
extern int GAME_worlds_entered;
extern int GAME_NPC_talked_flags;
extern int GAME_crushDeathCounter;
extern int GAME_unknown_boss_thing;
extern int GAME_total_skillpoints;
extern int GAME_skillpoint_flags;
extern int GAME_unknown_prog;

extern int _splashTransition;
extern int _blackOverlayOpacity;
extern int _unknownTransition;
extern int _checkpointStorage;
extern int _checkpointData;

extern int _cameraState;

extern char _parentHomeworldArray[32];
extern int _levelID;


extern short _cosineLookup[192];
extern short _sineLookup[256];

extern char _spyroByteRotationZ;

extern char erflag;

extern short glacierbridge;
extern short aquariasub;
extern short magmalift;
extern short glimmerbridge;
extern char swim;
extern char climb;
extern char headbash;
extern short aquariawall;
extern short zephyr;
extern short shady;
extern short icy;
extern short canyon;

extern int * ptr_sparx;
extern int * ptr_dynamic_terrain;

extern int * _ptr_moving_collision_data;
extern int * _ptr_moving_texture_data;
extern int * _ptr_low_lod_texture_data;
extern int * _ptr_textures_array;

extern int _unkLeaveLevel;
extern void _saveRealCheckpoint(int, int, int);
extern void _loadRealCheckpoint(int);

extern int lookToStartTimer;
extern void updateTimers(void);

extern int (*_createLevelObjectFunc)(int,int);
extern int * _updatedObjects;

#endif /* COMMON_H */
