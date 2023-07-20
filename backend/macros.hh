#pragma once

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;


// comparisons
//#define abs(x) (((x) > 0) ? (x) : (-(x)))
#define min(x, y) ((x) < (y) ? (x) : (y))
#define min3(x, y, z) (min(x, min(y, z)))
#define max(x, y) ((x) > (y) ? (x) : (y))
#define max3(x, y, z) (max(x, max(y, z)))

#define cond(c, x, y) ((c) ? (x) : (y))
#define maxabs(x, y) (abs(x) > abs(y) ? (x) : (y))
#define minabs(x, y) (abs(x) < abs(y) ? (x) : (y))

// easier cache
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)


// logarithms
#define    log2u32(x) (32 - __builtin_clz(x))


// easier static casts
#define bytes2f(x) *(float*)&(x)
#define bytes2d(x) *(double*)&(x)


// identifying characters
#define alphl(x) (u32(x ^ ('a' - 1)) <= ('z' - 'a'))
#define alphu(x) (u32(x ^ ('A' - 1)) <= ('Z' - 'A'))
#define numbe(x) (u32(x ^ '0') <= ('9' - '0'))
#define punct(x) (x == '_' || x == '-')





// create a string into an integer


#define str8le(a, b, c, d, e, f, g, h) \
(a|(u16(b)<<8)|(u32(c)<<16)|(u32(d)<<24)|(u64(e)<<32)|(u64(f)<<40)|(u64(g)<<48)|(u64(h)<<56))

#define str8be(a, b, c, d, e, f, g, h) \
(h|(u16(g)<<8)|(u32(f)<<16)|(u32(e)<<24)|(u64(d)<<32)|(u64(c)<<40)|(u64(b)<<48)|(u64(a)<<56))


#define str7le(a, b, c, d, e, f, g) \
(a|(u16(b)<<8)|(u32(c)<<16)|(u32(d)<<24)|(u64(e)<<32)|(u64(f)<<40)|(u64(g)<<48))

#define str7be(a, b, c, d, e, f, g) \
(g|(u16(f)<<8)|(u32(e)<<16)|(u32(d)<<24)|(u64(c)<<32)|(u64(b)<<40)|(u64(a)<<48))


#define str6le(a, b, c, d, e, f) \
(a|(u16(b)<<8)|(u32(c)<<16)|(u32(d)<<24)|(u64(e)<<32)|(u64(f)<<40))

#define str6be(a, b, c, d, e, f) \
(f|(u16(e)<<8)|(u32(d)<<16)|(u32(c)<<24)|(u64(b)<<32)|(u64(a)<<40))


#define str5le(a, b, c, d, e) \
(a|(u16(b)<<8)|(u32(c)<<16)|(u32(d)<<24)|(u64(e)<<32))

#define str5be(a, b, c, d, e) \
(e|(u16(d)<<8)|(u32(c)<<16)|(u32(b)<<24)|(u64(a)<<32))


#define str4le(a, b, c, d) \
(a|(u16(b)<<8)|(u32(c)<<16)|(u32(d)<<24))

#define str4be(a, b, c, d) \
(d|(u16(c)<<8)|(u32(b)<<16)|(u32(a)<<24))


#define str3le(a, b, c) \
(a|(u16(b)<<8)|(u32(c)<<16))

#define str3be(a, b, c) \
(c|(u16(b)<<8)|(u32(a)<<16))


#define str2le(a, b) \
(a|(u16(b)<<8))

#define str2be(a, b) \
(b|(u16(a)<<8))




// substring of an 64 bit int (little endian)
#define substr7(x)    (x & 0xFFFFFFFFFFFFFF)
#define substr6(x)    (x & 0xFFFFFFFFFFFF)
#define substr5(x)    (x & 0xFFFFFFFFFF)
#define substr4(x)    (x & 0xFFFFFFFF)
#define substr3(x)    (x & 0xFFFFFF)
#define substr2(x)    (x & 0xFFFF)
#define substr1(x)    (x & 0xFF)



// loads


#define load8(x) \
    *x++;

#define load16(x) \
    *(uint16_t*)(x); \
    x += 2; \


#define load32(x) \
    *(uint32_t*)(x); \
    x += 4;


#define load64(x) \
    *(uint64_t*)(x); \
    x += 8; \




// serialize
#define ser8(i) *o++ = i;


#define ser16(i) { \
    *(uint16_t*)o = i; \
    o += 2; \
}

#define ser32(i) { \
    *(uint32_t*)o = i; \
    o += 4; \
}

#define ser64(i) { \
    *(uint64_t*)o = i; \
    o += 8; \
}

#define serObject(i) { \
    memcpy(o, i, sizeof(*i)); \
    o += sizeof(*i); \
}

#define serPtr(i) { \
    memcpy(o, i, sizeof(*i)); \
    o += sizeof(*i); \
}

#define serData(str, len) { \
    memcpy(o, str, len); \
    o += len; \
}

#define serString(str) { \
    serData(o, str.data(), str.length()); \
}

