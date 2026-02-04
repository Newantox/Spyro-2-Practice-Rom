#include <types.h>
#include <symbols.h>
#include <syscalls.h>
#include <common.h>
#include <menu.h>

extern int lookToStartTimer;
extern int pendingLoadSlot;
extern char stateMode;
extern char stateHeld;

void altMainMod(void)
{
    
    if (pendingLoadSlot)
    {
        LoadState(pendingLoadSlot);

        // post-load fixes
        lookToStartTimer = 1;

        if (stateMode) {
            _updateFlags = 0;
            stateHeld = 1;
        } else {
            _updateFlags = 0x7b;
            stateHeld = 0;
        }

        pendingLoadSlot = 0;
    }

    _RenderGame();
}
