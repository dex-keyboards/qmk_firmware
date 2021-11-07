#pragma once

#include "quantum.h"

#define startCoroutine static uint16_t state=0; switch(state) { case 0:
#define yield do { state=__LINE__; return; case __LINE__:; } while (0)
#define yieldWaitMs(ms) do { state=__LINE__; static uint32_t exit_time=timer_read32(); return; case __LINE__:; if(timer_elapsed32(exit_time) < ms) { return; } } while (0)
#define endCoroutine }
