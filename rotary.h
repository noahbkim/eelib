#ifndef ROTARY_H
#define ROTARY_H

#include <stdint.h>
#include "register.h"

typedef struct rotary_t
{

    register_t* reg;
    uint8_t const bit0;
    uint8_t const bit1;
    int16_t const value_minimum;
    int16_t const value_maximum;

    volatile uint8_t pin_last;
    volatile uint16_t value;

} rotary_t;

void rotary_construct(rotary_t* rotary, uint16_t value);
int8_t rotary_difference(rotary_t* rotary);
void rotary_change_interrupt(rotary_t* rotary);

#define ROTARY_SETUP(name, reg, pci, bit0, bit1, value_minimum, value_maximum)\
rotary_t name##_stack = { &reg, bit0, bit1, value_minimum, value_maximum };\
rotary_t* const name = &name##_stack;\
ISR(PCINT##pci##_vect) { rotary_change_interrupt(name); }

#endif
