#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

/*Typedefs to make code cleaner*/
typedef unsigned char u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/*Convenience Macros*/
#define CHECK_FLAG(byte, flag) (!!(byte & flag))
#define SET_FLAG(byte, flag) (byte |= flag)
#define SIGNED(val) ((val>>(sizeof(val)*8-1)))
#define SIGN(val) ((SIGNED(val)) ? -val : val)
#define BITS(val, s, e) (((val) >> (s)) & ~((unsigned)-1 << ((e) - (s))))


#endif
