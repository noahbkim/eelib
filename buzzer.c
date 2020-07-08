#include "buzzer.h"
#include "timer.h"

void buzzer_construct(buzzer_t* buzzer)
{
    *buzzer->reg->ddr |= (1 << buzzer->bit);
}

void buzzer_set_frequency(buzzer_t* buzzer, double frequency)
{
    buzzer->frequency = frequency;
    timer8_set_overflow_us(buzzer->timer, 1000000.0 / frequency / 2);
}

void buzzer_play_us(buzzer_t* buzzer, uint32_t us)
{
    buzzer->counter = (buzzer->frequency * 2) * (us / 1000000);
}

void buzzer_interrupt(buzzer_t* buzzer)
{
    if (buzzer->counter > 0)
    {
        if (buzzer->counter % 2 == 0)
        {
            *buzzer->reg->port &= ~(1 << buzzer->bit);
        }
        else
        {
            *buzzer->reg->port |= (1 << buzzer->bit);
        }
        --buzzer->counter;
    }
}
