#if !defined(ARENA_H)
/* ========================================================================
   $File: Arena.h $
   $Date: October 19 2024 04:51 pm $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#define ARENA_H
#include "../Intrinsics.h"
#include <stdlib.h>
#include <string.h>

struct memory_arena
{
    uint64 Capacity;
    uint64 Used;
    uint8 *Memory;
};

internal memory_arena
ArenaCreate(uint64 Size)
{
    memory_arena Arena = {};
    Arena.Memory = (uint8 *)malloc(Size);
    if(Arena.Memory)
    {
        Arena.Capacity = Size;
        memset(Arena.Memory, 0, Size);
    }
    return(Arena);    
}

internal uint8*
ArenaAlloc(memory_arena *Memory, uint64 Size)
{   
    uint8 *Result = {};
    uint64 AlignedSize = (Size + 7) & ~ 7;
    if(Memory->Used + AlignedSize <= Memory->Capacity)
    {
        Result = Memory->Memory + Memory->Used;
        Memory->Used += AlignedSize;
    }
    else
    {
        Check(0, "Allocation is too large!\n");
    }
    return(Result);
}

internal inline void
ArenaReset(memory_arena *Memory)
{
    memset(Memory->Memory, 0, sizeof(Memory->Capacity));
    Memory->Used = 0;
}

internal inline void
ArenaDestroy(memory_arena *Memory)
{
    free(Memory->Memory);
    Memory = {};
}

#endif // ARENA_H

