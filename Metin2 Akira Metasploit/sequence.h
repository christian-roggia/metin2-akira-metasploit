#ifndef __SEQUENCE__
#define __SEQUENCE__

#include <stdint.h>

extern unsigned char gc_abSequence[32768];
extern uint32_t g_seq_counter;
extern uint32_t inc_seq_counter(void);

#endif
