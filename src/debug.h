#ifndef DEBUG_H
#define DEBUG_H

extern unsigned int dbgLevel;

enum {
  DBG_LEVEL_0 = 0,
  DBG_LEVEL_1 = (1 << 0), // Function Trace
  DBG_LEVEL_2 = (1 << 1), // Memory Dump
  DBG_LEVEL_3 = (1 << 2)  // Reserve
};
#endif //  DEBUG_H
