#ifndef SANCUS_SUPPORT_SM_IO_H_INC
#define SANCUS_SUPPORT_SM_IO_H_INC

#include <sancus/sm_support.h>
#include <stdint.h>

#define INFO_STR(str)               "[" __FILE__ "] " str
#define pr_info(str)                puts(INFO_STR(str))
#define pr_info1(str, a1)           printf1(INFO_STR(str), a1)
#define pr_info2(str, a1, a2)       printf2(INFO_STR(str), a1, a2)
#define pr_info3(str, a1, a2, a3)   printf3(INFO_STR(str), a1, a2, a3)

#define EXIT()                                      \
  do {                                              \
    /* set CPUOFF bit in status register */         \
    asm("bis #0x210, r2");                          \
    while(1);                                       \
  } while(0)

#define ASSERT(cond)                                \
  do {                                              \
    if (!(cond))                                    \
    {                                               \
        /* pr_info1 to work around an LLVM bug */   \
        pr_info1("assertion failed: " #cond, 0);    \
        EXIT();                                     \
    }                                               \
  } while(0)

void msp430_io_init(void);
void pr_sm_info(struct SancusModule *sm);
int __attribute__((noinline)) putchar(int c);

#define __always_inline static inline __attribute__((always_inline))

#ifndef __SANCUS_IO_QUIET
    #include <stdio.h>
    void __attribute__((noinline)) printf0(const char* str);
    void __attribute__((noinline)) printf1(const char* fmt, int arg1);
    void __attribute__((noinline)) printf2(const char* fmt, int arg1, int arg2);
    void __attribute__((noinline)) printf3(const char* fmt, int arg1, int arg2, int arg3);

    __always_inline void dump_buf(const uint8_t *buf, int size, char *name)
    {
        int i;
        printf2("%s (%d bits) is: ", (int) name, size*8);
        for (i = 0; i < size; i++)
            printf1("%02x", (int) buf[i] & 0xff);
        puts(" ");
    }
#else
    #define puts(s)
    #define printf0(s)
    #define printf1(s, arg1)
    #define printf2(s, arg1, arg2)
    #define printf3(s, arg1, arg2, arg3)

    #define dump_buf(buf, size, name)
#endif

#endif
