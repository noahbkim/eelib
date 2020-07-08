#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <avr/interrupt.h>

#define FREQUENCY 16000000UL
#define TIMER_PRESCALER_NONE 0b000
#define TIMER_PRESCALER_1 0b001
#define TIMER_PRESCALER_8 0b010
#define TIMER_PRESCALER_64 0b011
#define TIMER_PRESCALER_256 0b100
#define TIMER_PRESCALER_1024 0b101

typedef struct timer8_t
{
    volatile uint8_t* const tccra;
    volatile uint8_t* const tccrb;
    volatile uint8_t* const timsk;
    volatile uint8_t* const ocra;
    volatile uint8_t* const ocrb;
    volatile uint8_t* const tcnt;

    uint16_t prescaler;
} timer8_t;

typedef struct timer16_t
{
    volatile uint8_t* const tccra;
    volatile uint8_t* const tccrb;
    volatile uint8_t* const timsk;
    volatile uint16_t* const ocra;
    volatile uint16_t* const ocrb;
    volatile uint16_t* const tcnt;

    uint16_t prescaler;
} timer16_t;

void timer8_reset(timer8_t* timer);
uint8_t timer8_measure(timer8_t* timer);
uint32_t timer8_measure_us(timer8_t* timer);
void timer8_interrupt_overflow_enable(timer8_t* timer);
void timer8_interrupt_overflow_disable(timer8_t* timer);
void timer8_interrupt_compare_a_enable(timer8_t* timer);
void timer8_interrupt_compare_a_disable(timer8_t* timer);
void timer8_set_prescaler(timer8_t* timer, uint8_t prescaler);
void timer8_set_generation(timer8_t* timer, uint8_t wgm);
void timer8_set_overflow(timer8_t* timer, uint8_t overflow);
void timer8_set_overflow_us(timer8_t* timer, double us);

void timer16_reset(timer16_t* timer);
uint16_t timer16_measure(timer16_t* timer);
uint32_t timer16_measure_us(timer16_t* timer);
void timer16_interrupt_overflow_enable(timer16_t* timer);
void timer16_interrupt_overflow_disable(timer16_t* timer);
void timer16_interrupt_compare_a_enable(timer16_t* timer);
void timer16_interrupt_compare_a_disable(timer16_t* timer);
void timer16_set_prescaler(timer16_t* timer, uint8_t prescaler);
void timer16_set_generation(timer16_t* timer, uint8_t wgm);
void timer16_set_overflow(timer16_t* timer, uint16_t overflow);
void timer16_set_overflow_us(timer16_t* timer, double us);

#define TIMER_SETUP(id, size)\
static timer##size##_t TIMER##id = { &TCCR##id##A, &TCCR##id##B, &TIMSK##id, &OCR##id##A, &OCR##id##B, &TCNT##id };\
static timer##size##_t* const T##id = &TIMER##id;

#endif  // TIMER_H
