#ifndef TEA_H
#define TEA_H

#include <memory.h>
#include <stdint.h>
#include <stdio.h>

struct TEA
{
    static void Encrypt(char *cdata, uint32_t len, uint32_t *key);
    static void Decrypt(char *cdata, uint32_t len, uint32_t *key);
    static void TEA_Decrypt(uint32_t *v, uint32_t *k);
    static void TEA_Encrypt(uint32_t *v, uint32_t *k);
};

#endif // TEA_H
