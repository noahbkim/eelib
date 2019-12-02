#include "rotary.h"

#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>

void rotary_construct(rotary_t* rotary, uint16_t value)
{
    rotary->value = value;
    *rotary->reg->ddr &= ~((1 << rotary->bit0) | (1 << rotary->bit1));
    *rotary->reg->port |= (1 << rotary->bit0) | (1 << rotary->bit1);
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << rotary->bit0) | (1 << rotary->bit1);
    rotary->pin_last = *rotary->reg->pin;
}

int8_t rotary_difference(rotary_t* rotary)
{
    uint8_t pin = *rotary->reg->pin;
    bool s0 = rotary->pin_last & (1 << rotary->bit0);
    bool s1 = rotary->pin_last & (1 << rotary->bit1);
    bool n0 = pin & (1 << rotary->bit0);
    bool n1 = pin & (1 << rotary->bit1);
    if (s0 == n0 && s1 == n1)
    {
        return 0;
    }
    else
    {
        rotary->pin_last = pin;
        return (!s1 && !n0) || (!s0 && n1) || (s1 && n0) ? 1 : -1;
    }
}

void rotary_change_interrupt(rotary_t* rotary)
{
    switch (rotary_difference(rotary))
    {
        case -1:
            if (rotary->value > 0)
            {
                --rotary->value;
            }
            break;
        case 1:
            if (rotary->value < rotary->value_maximum)
            {
                ++rotary->value;
            }
            break;
    }
}
