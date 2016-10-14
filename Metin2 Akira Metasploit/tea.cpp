#include "tea.h"

void TEA::Encrypt(char *cdata, uint32_t len, uint32_t *key)
{
    uint32_t *udata = reinterpret_cast<uint32_t *>(cdata);

    for(uint32_t i = 0; i < len / 8; i++)
        TEA::TEA_Encrypt(&udata[i * 2], key);

    cdata = reinterpret_cast<char *>(udata);
}

void TEA::Decrypt(char *cdata, uint32_t len, uint32_t *key)
{
    uint32_t *udata = reinterpret_cast<uint32_t *>(cdata);

    for(uint32_t i = 0; i < len / 8; i++)
        TEA::TEA_Decrypt(&udata[i * 2], key);

    cdata = reinterpret_cast<char *>(udata);
}

void TEA::TEA_Decrypt(uint32_t *v, uint32_t *k)
{
    uint32_t sum = 0xC6EF3720, delta = 0x61C88647;
    uint32_t v0 = v[0], v1 = v[1];

    for (int i = 0; i < 32; i++)
    {
            v1 -= (v0 + (16 * v0 ^ (v0 >> 5))) ^ (sum + k[(sum >> 11) & 3]);
            sum += delta;
            v0 -= (v1 + (16 * v1 ^ (v1 >> 5))) ^ (sum + k[sum & 3]);
    }

    v[0] = v0; v[1] = v1;
}

void TEA::TEA_Encrypt(uint32_t *v, uint32_t *k)
{
    uint32_t sum = 0, delta = 0x61C88647;
    uint32_t v0 = v[0], v1 = v[1];

    for (int i = 0; i < 32; i++)
    {
            v0 += (v1 + (16 * v1 ^ (v1 >> 5))) ^ (sum + k[sum & 3]);
            sum -= delta;
            v1 += (v0 + (16 * v0 ^ (v0 >> 5))) ^ (sum + k[(sum >> 11) & 3]);
    }

    v[0] = v0; v[1] = v1;
}
