#include <types.h>
#include <symbols.h>
#include <syscalls.h>
#include <common.h>

extern char zoeZaps;
extern char cpResets;

volatile uint32_t *code = (volatile uint32_t *)0x8004c0c8;

void saveCheckpoint(void) {
    code[0] = 0x27BDFFD8;
    code[1] = 0xAFB20018;
    *(int*)0x80069ff8 -= 0x164;
    _saveRealCheckpoint(0x80067414,&_spyro,*(char*)0x80069ffe);
    *(int*)0x80069ff8 += 0x164;
    if(!zoeZaps) {
    code[0] = 0x03e00008;
    code[1] = 0x00000000;
    }
}

typedef struct {
    void* addr;
    int   size;
} ClearEntry;

static const ClearEntry checkpointClears[] = {
    { &GAME_orbs_collected_status,      0x20 },
    { &GAME_end_level_portals_status,   0x1C },
    { &GAME_world_gems_collected,       0x480 },
    //{ &GAME_gems_collected_status,      0x400 }, combined with 0x80 above to save space to fit in codecave
    { &GAME_worlds_entered,             0x20 },
    { &GAME_NPC_talked_flags,           0x20 },
    { &GAME_crushDeathCounter,          0x08 },
    { &GAME_unknown_boss_thing,         0x20 },
    { &GAME_global_progress_flags,      0x9A },
    { &GAME_skillpoint_flags,           0x20 },
};

void resetCheckpoint(void)
{
    _zoe_checkpoint_active = 0;
    GAME_orbs_collected_count = 0;
    GAME_num_talismans        = 0;
    GAME_gems_collected_value = 0;
    GAME_total_skillpoints    = 0;
    SimpleReset();
    loadCheckpoint();
}

void loadCheckpoint(void) {
    if (cpResets) SimpleReset();
    _loadRealCheckpoint(&_zoe_checkpoint_active);
    ManageValues();

}

void SimpleReset() {
      for (int i = 0; i < (sizeof(checkpointClears)/sizeof(ClearEntry)); i++) {
        LIBC_bzero((unsigned char*)checkpointClears[i].addr,
                   checkpointClears[i].size);
    }

}





