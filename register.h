#ifndef REGISTER_H
#define REGISTER_H

#include <avr/io.h>
#include <avr/interrupt.h>

typedef struct register_t
{
    uint8_t const start;
    volatile uint8_t* const ddr;
    volatile uint8_t* const port;
    volatile uint8_t* const pin;
} register_t;

#define REGISTER_SETUP(letter, start)\
static register_t REGISTER##letter = { start, &DDR##letter, &PORT##letter, &PIN##letter };\
static register_t* const R##letter = &REGISTER##letter;

REGISTER_SETUP(B, 8);
REGISTER_SETUP(C, 14);
REGISTER_SETUP(D, 0);

#define PCIE(reg)\
(reg->start == 8 ? PCIE0 :\
 reg->start == 14 ? PCIE1 :\
 reg->start == 0 ? PCIE2 : 0)

#define PCMSK(reg)\
(reg->start == 8 ? &PCMSK0 :\
 reg->start == 14 ? &PCMSK1 :\
 reg->start == 0 ? &PCMSK2 : (uint8_t*)0)

#endif  // REGISTER_H
