#pragma once

#define VALID_HEX(x) ((x - 'a') < 16)


void encode_ahex(char* out, const uint8_t* in, size_t len)
{
    for (int i = 0; i < len; ++i, out += 2) {
        out[0] = (in[i] >> 4) + 97;
        out[1] = (in[i] & 0xF) + 97;
    }
}

inline std::string encode_ahex_int(const uint64_t x)
{
    return encode_ahex((const uint8_t *)&x, 8);
}

inline int decode_ahex(uint8_t* out, const char* in, size_t len)
{
    for (int i = 0; i < len; i += 2) {
        int a = in[0] - 'a';
        int b = in[1] - 'a';
        
        if (!VALID_HEX(a) || !VALID_HEX(b))
            return -1;
        
        *out++ = (a << 4) | b;
        
        in += 2;
    }
    
    return 0;
}

inline int decode_ahex_int(const char* in, size_t len)
{
    const char* p = in;
    uint32_t val = 0;
    
    while (VALID_HEX(*p)) {
        val <<= 4;
        val |= (*p++ - 'a');
    }
    
    return 0;
}
