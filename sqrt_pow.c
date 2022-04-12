#include <stdio.h>

float mysqrt(float in){
    __uint32_t mezi = ((*(__uint32_t*)&in & 0x7f800000) - 0x3f800000 >> 1) + 0x3f800000 & 0x7f800000;
    float out = *(float*)&mezi;
    __uint32_t* b = (__uint32_t*)&out;
    __uint32_t carry = 1 << 23;
    float rout = out;
    while(carry >>= 1){
        out = rout;
        *b += carry;
        if (out * out <= in) rout = out;
    }
    return rout;
}

float mypow(float a, float pow){
    float out = 1.0;
    __uint32_t bitpow = *(__uint32_t*)&pow;
    __uint32_t point = bitpow >> 23 & 0xff;
    float inter = a;
    for (size_t i = 0x7f; i < point; i++){
        if(((bitpow & 0x7fffff)+0x800000) >> (point > i+23 ? 31 : 23+i-point) & 1) out *= inter;
        inter *= inter;
    }
    inter = a;
    for (size_t i = 0x7f; i > point-23; i--){
        if(((bitpow & 0x7fffff)+0x800000) >> 23+i-point & 1) out *= inter;
        inter = mysqrt(inter);
    }
    return out;
}
