// Misc utility functions.
//
// Copyright (C) 2008  Kevin O'Connor <kevin@koconnor.net>
//
// This file may be distributed under the terms of the GNU GPLv3 license.

#include "util.h" // usleep
#include "bregs.h" // struct bregs
#include "config.h" // SEG_BIOS
#include "farptr.h" // GET_FARPTR

// Call a function with a specified register state.  Note that on
// return, the interrupt enable/disable flag may be altered.
inline void
call16(struct bregs *callregs)
{
    asm volatile(
#ifdef MODE16
        "calll __call16\n"
#else
        "calll __call16_from32\n"
#endif
        : "+a" (callregs), "+m" (*callregs)
        :
        : "ebx", "ecx", "edx", "esi", "edi", "ebp", "cc");
}

inline void
__call16_int(struct bregs *callregs, u16 offset)
{
    callregs->cs = SEG_BIOS;
    callregs->ip = offset;
    call16(callregs);
}

// Sum the bytes in the specified area.
u8
checksum(u8 *far_data, u32 len)
{
    u32 i;
    u8 sum = 0;
    for (i=0; i<len; i++)
        sum += GET_FARPTR(far_data[i]);
    return sum;
}

void *
memset(void *s, int c, size_t n)
{
    while (n)
        ((char *)s)[--n] = c;
    return s;
}

void *
memcpy(void *far_d1, const void *far_s1, size_t len)
{
    u8 *d = far_d1;
    u8 *s = (u8*)far_s1;

    while (len--) {
        SET_FARPTR(*d, GET_FARPTR(*s));
        d++;
        s++;
    }

    return far_d1;
}

void *
memmove(void *d, const void *s, size_t len)
{
    if (s >= d)
        return memcpy(d, s, len);

    d += len-1;
    s += len-1;
    while (len--) {
        *(char*)d = *(char*)s;
        d--;
        s--;
    }

    return d;
}

void
__set_fail(const char *fname, struct bregs *regs)
{
    __debug_fail(fname, regs);
    set_fail_silent(regs);
}

void
__set_code_fail(const char *fname, struct bregs *regs, u8 code)
{
    __debug_fail(fname, regs);
    set_code_fail_silent(regs, code);
}
