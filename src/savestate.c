#include <common.h>

byte* local_savestate_region;

#include "common.h"

typedef unsigned char byte;

typedef struct {
    void* addr;
    int   size;
} StateBlock;

// ------------------------------------------------------------
// memcopy implementation
// ------------------------------------------------------------
void* memcopy(void* dest, const void* src, int len) {
    char* d = (char*)dest;
    const char* s = (const char*)src;
    while (len--) {
        *d++ = *s++;
    }
    return dest;
}


// ------------------------------------------------------------
// Static blocks
// ------------------------------------------------------------
static const StateBlock static_blocks[] = {
    { &GAME_orbs_collected_count,     0x4   },
    { &GAME_orbs_collected_status,    0x20  },
    { &GAME_num_talismans,            0x4   },
    { &GAME_end_level_portals_status, 0x1c  },
    { &GAME_gems_collected_value,     0x4   },
    { &GAME_world_gems_collected,     0x80  },
    { &GAME_gems_collected_status,    0x400 },
    { &GAME_worlds_entered,           0x20  },
    { &GAME_NPC_talked_flags,         0x20  },
    { &GAME_crushDeathCounter,        0x8   },
    { &GAME_unknown_boss_thing,       0x20  },
    { &GAME_global_progress_flags,    0x9a  },
    { &GAME_skillpoint_flags,         0x20  },

    { &_spyro,                        0x2E0 },

    // Fixed RAM addresses
    { (void*)0x80067028,              0x4   },
    { (void*)0x80066e7c,              0x5   },
    { (void*)0x80066f60,              0x2c  },
    { (void*)0x80066fb0,              0x4   },
    { (void*)0x80067e84,              0x1F3 },
    { (void*)0x8006712c,              0x4   },
    { (void*)0x8006718c,              0x248 },
    { (void*)0x80067414,              0x248 },
    { (void*)0x8006765c,              0x34  },
    { (void*)0x800687c4,              0x1D4 },

    { (void*)0x800670d8,              0x4   },
    { (void*)0x80067148,              0x4   },
    { (void*)0x80066ff0,              0x4   },
    { (void*)0x80066f44,              0x4   },
    { (void*)0x80066ff4,              0x4   },

    { (void*)0x80067084,              0x4   },
    { (void*)0x80067680,              0x4   },

    { (void*)0x80067000,              0x1000 },
    { (void*)0x80068000,              0x1000 },

    { (void*)0x8006700c,              0x4   },
    { (void*)0x80067008,              0x4   },
    { (void*)0x80067100,              0x4   },
    { (void*)0x8006701c,              0x4   },

    { (void*)0x800676bc,              0x4   },
    { (void*)0x800676b4,              0x4   },
    { (void*)0x80066fec,              0x4   },

    { (void*)0x80067088,              0x4   },
    { (void*)0x8006708c,              0x4   },
    { (void*)0x80066f30,              0x4   },
    { (void*)0x80066efc,              0x4   },
    { (void*)0x80066f50,              0x4   },
    { (void*)0x80067038,              0x4   },
    { (void*)0x800670f4,              0x4   },
    { (void*)0x80067174,              0x4   },
    { (void*)0x800670bc,              0x4   },

    { (void*)0x800B34fD,              0x1   },
    { (void*)0x800B3410,              0x1   },
    { (void*)0x800B3412,              0x1   },
    { (void*)0x80193339,              0x1   },


    { (void*)0x800698bb,              0x1   },
    { (void*)0x80061aac,              0x4   },

    { (void*)0x80066fd8,              0x4   },
    { (void*)0x8006aa00,              0x14c },
};

// ------------------------------------------------------------
// Dynamic blocks
// ------------------------------------------------------------
static void build_dynamic_blocks(StateBlock* out)
{
    out[0].addr = ptr_MobyArray;
    out[0].size = ((byte*)ptrToEndOfMobys) - ((byte*)ptr_MobyArray);

    out[1].addr = (byte*)ptrToEndOfMobys + 0x14;
    out[1].size = 0x30000;

    out[2].addr = &ptr_DynamicMobyArray;
    out[2].size = 0x4;

    out[3].addr = &count_DynamicMobys;
    out[3].size = 0x4;

    out[4].addr = ptr_ParticleArray;
    out[4].size = 0x2000;
}

// ------------------------------------------------------------
// transfer function
// direction = 0 → SAVE
// direction = 1 → LOAD
// ------------------------------------------------------------

static inline void* GetSavestateRegion(int slot)
{
    return (void*)(0x80200000 + ((slot - 1) * 0x37000)); // For Deckard PS2 = 0x80A10000, Emulator = 0x80200000 
}

void StateTransfer(void* savestate_region, int direction, int slot)
{
    byte* cursor = (byte*)savestate_region;

    // 1. static blocks
    
    for (int i = 0; i < (int)(sizeof(static_blocks)/sizeof(StateBlock)); i++) {
        void* addr = static_blocks[i].addr;
        int   size = static_blocks[i].size;




        if (direction == 0)
            memcopy(cursor, addr, size);
        else
            memcopy(addr, cursor, size);

        cursor += size;
    }

    // 2. dynamic blocks
    StateBlock dyn[5];
    build_dynamic_blocks(dyn);

    for (int i = 0; i < 5; i++) {
        if (direction == 0)
            memcopy(cursor, dyn[i].addr, dyn[i].size);
        else
            memcopy(dyn[i].addr, cursor, dyn[i].size);

        cursor += dyn[i].size;
    }
}

void SaveState(int slot)
{
    void* region = GetSavestateRegion(slot);
    StateTransfer(region, 0, slot);
}

void LoadState(int slot)
{
    void* region = GetSavestateRegion(slot);
    StateTransfer(region, 1, slot);
}

extern slotInfo;
extern currentStateSlot;

void DrawSlot(void)
{    sprintf(slotInfo, "Slot %d", currentStateSlot+1);
    _DrawText_Right(slotInfo, 500, 217, 13-currentStateSlot*5);
}