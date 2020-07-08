#include "timer.h"
#include <avr/interrupt.h>

void timer8_reset(timer8_t* timer)
{
    *timer->tcnt = 0;
}

void timer16_reset(timer16_t* timer)
{
    *timer->tcnt = 0;
}

uint8_t timer8_measure(timer8_t* timer)
{
    return *timer->tcnt;
}

uint32_t timer8_measure_us(timer8_t* timer)
{
    uint32_t result = *timer->tcnt;
    result *= timer->prescaler;
    result /= FREQUENCY / 1000000UL;
    return result;
}

uint16_t timer16_measure(timer16_t* timer)
{
    return *timer->tcnt;
}

uint32_t timer16_measure_us(timer16_t* timer)
{
    uint32_t result = *timer->tcnt;
    result *= timer->prescaler;
    result /= FREQUENCY / 1000000UL;
    return result;
}

void timer8_interrupt_overflow_enable(timer8_t* timer)
{
    *timer->timsk |= (1 << 0);
}

void timer16_interrupt_overflow_enable(timer16_t* timer)
{
    *timer->timsk |= (1 << 0);
}

void timer8_interrupt_overflow_disable(timer8_t* timer)
{
    *timer->timsk &= ~(1 << 0);
}

void timer16_interrupt_overflow_disable(timer16_t* timer)
{
    *timer->timsk &= ~(1 << 0);
}

void timer8_interrupt_compare_a_enable(timer8_t* timer)
{
    *timer->timsk |= (1 << 1);  // A compare
}

void timer16_interrupt_compare_a_enable(timer16_t* timer)
{
    *timer->timsk |= (1 << 1);  // A compare
}

void timer8_interrupt_compare_a_disable(timer8_t* timer)
{
    *timer->timsk &= ~(1 << 1);  // A compare
}

void timer16_interrupt_compare_a_disable(timer16_t* timer)
{
    *timer->timsk &= ~(1 << 1);  // A compare
}

inline uint16_t prescaler_from_flag(uint8_t prescaler)
{
    switch (prescaler)
    {
        case TIMER_PRESCALER_1:
            return 1;
        case TIMER_PRESCALER_8:
            return 8;
        case TIMER_PRESCALER_64:
            return 64;
        case TIMER_PRESCALER_256:
            return 256;
        case TIMER_PRESCALER_1024:
            return 1024;
        default:
            return 0;
    }
}

void timer8_set_prescaler(timer8_t* timer, uint8_t prescaler)
{
    *timer->tccrb &= ~0b00000111;
    *timer->tccrb |= 0b00000111 & prescaler;
    timer->prescaler = prescaler_from_flag(prescaler);
}

void timer16_set_prescaler(timer16_t* timer, uint8_t prescaler)
{
    *timer->tccrb &= ~0b00000111;
    *timer->tccrb |= 0b00000111 & prescaler;
    timer->prescaler = prescaler_from_flag(prescaler);
}

/// Treat it as a combined register of WGM[3:0]
void timer8_set_generation(timer8_t* timer, uint8_t wgm)
{
    *timer->tccra &= ~0b00000011;
    *timer->tccra |= 0b00000011 & wgm;
    *timer->tccrb &= ~0b00011000;
    *timer->tccrb |= (0b00001100 & wgm) << 1;
}

void timer16_set_generation(timer16_t* timer, uint8_t wgm)
{
    *timer->tccra &= ~0b00000011;
    *timer->tccra |= 0b00000011 & wgm;
    *timer->tccrb &= ~0b00011000;
    *timer->tccrb |= (0b00001100 & wgm) << 1;
}

void timer8_set_overflow(timer8_t* timer, uint8_t overflow)
{
    *timer->ocra = overflow;
}

void timer16_set_overflow(timer16_t* timer, uint16_t overflow)
{
    *timer->ocra = overflow;
}

void timer8_set_overflow_us(timer8_t* timer, double us)
{
    *timer->ocra = (FREQUENCY / timer->prescaler) * 1000000.0 * us;
}

void timer16_set_overflow_us(timer16_t* timer, double us)
{
    *timer->ocra = (FREQUENCY / timer->prescaler) * 1000000.0 * us;
}
