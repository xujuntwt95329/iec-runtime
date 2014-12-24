#ifndef __CALLSTK_H__
#define __CALLSTK_H__

#include <stdint.h>
#include "ivalue.h"

typedef struct {
    uint16_t pou;   /* index of current pou descriptors */
    uint32_t ret; /* return address(AKA index of instructions) */
    IValue *reg;  /* register group base address */
} SFrame; /* Stack Frame */

typedef struct {
    uint16_t capacity; /* stack capacity */
    uint16_t top;      /* top of stack(always point next stack frame) */
    SFrame *base;      /* stack base address */
} CStack; /* Calling Stack */

#define sf_init(sf, ipou, iret, rcount) { \
    (sf).pou = ipou;                     \
    (sf).ret= iret;                      \
    (sf).reg= new IValue[rcount];       \
}
/* sf1.reg[base1 ... base1+count] <-- sf2.reg[base2 ... base1+count] */
#define sf_regcpy(sf1, base1, sf2, base2, count) { \
    for (int i = 0; i < count; i++) {                \
        fprintf(stderr, "regcpy: ");\
        dump_value("sf1.reg", (sf1).reg[base1+i]);\
        fprintf(stderr, " <-- ");\
        dump_value("sf2.reg", (sf2).reg[base2+i]);\
        fprintf(stderr, "\n");\
        (sf1).reg[base1+i] = (sf2).reg[base2+i];   \
    }                                                \
}
/* stack capacity is enough */
#define cs_push(stk, sf) {      \
    (stk).base[(stk).top] = sf; \
    (stk).top++;                \
}
#define cs_pop(stk) {\
    delete[] (stk).base[(stk).top-1].reg; \
    (stk).top--;\
}
int cs_init(CStack *stk, uint16_t cap);
//int cs_push(CStack *stk, SFrame *frame);
//int cs_pop(CStack *stk);

#endif