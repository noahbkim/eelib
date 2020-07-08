#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include <stdbool.h>
#include "register.h"
#include "timer.h"

typedef struct buzzer_t
{
    double frequency;
    volatile uint32_t counter;

    register_t* const reg;
    uint8_t const bit;
    timer8_t* const timer;
} buzzer_t;

void buzzer_construct(buzzer_t* buzzer);
void buzzer_set_frequency(buzzer_t* buzzer, double frequency);
void buzzer_play_us(buzzer_t* buzzer, uint32_t us);
static inline void buzzer_play_ms(buzzer_t* buzzer, uint32_t ms) { buzzer_play_us(buzzer, ms * 1000); }
static inline void buzzer_play_s(buzzer_t* buzzer, uint32_t s) { buzzer_play_us(buzzer, s * 1000000); }
void buzzer_interrupt(buzzer_t* buzzer);

#define BUZZER_SETUP(name, reg, bit, timer, timer_id)\
static buzzer_t name##_stack = { 0, 0, &reg, bit, &timer };\
static buzzer_t* const name = &name##_stack;\
ISR(TIMER##timer_id##_COMPA_vect) { buzzer_interrupt(name); }

#endif  // BUZZER_H
