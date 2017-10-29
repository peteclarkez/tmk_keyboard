/* Copyright 2017 Peter Clarke <pete@clarkez.co.uk>
 *
 * This is heavily based on gh60.
 *
 * Copyright 2012 Jun Wako <wakojun@gmail.com>
 *
 * As for liscensing consult with the original files or its author.
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	0
#endif
static uint8_t debouncing = DEBOUNCE;

// bit array of key state(1:on, 0:off)
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    debug_enable   =true;
    debug_matrix   =true;
    debug_keyboard =true;

    // To use PORTF disable JTAG with writing JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // initialize row and col
    unselect_cols();
    init_rows();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++)  {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {  // 0-16
        select_col(col);
        _delay_us(3);       // without this wait it won't read stable value.
        uint8_t rows = read_rows();
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {  // 0-5
            bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
            bool curr_bit = rows & (1<<row);
            if (prev_bit != curr_bit) {
                matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
                if (debouncing) {
                    dprint("bounce!: "); dprintf("%02X", debouncing); dprintln();
                }
                debouncing = DEBOUNCE;
            }
        }
        unselect_cols();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop32(matrix[i]);
    }
    return count;
}

/* Row pin configuration
 * row: 0  1  2  3  4  5  6  7
 * pin: F7 F6 F5 F4 F3 F2 F1 F0 (old)
 */

static void init_rows(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRF  &= ~0b11111111;
    PORTF |= 0b11111111;
}

static uint8_t read_rows(void)
{
    return (PINF&(1<<7) ? 0 : (1<<0)) |
           (PINF&(1<<6) ? 0 : (1<<1)) |
           (PINF&(1<<5) ? 0 : (1<<2)) |
           (PINF&(1<<4) ? 0 : (1<<3)) |
           (PINF&(1<<3) ? 0 : (1<<4)) |
           (PINF&(1<<2) ? 0 : (1<<5)) |
           (PINF&(1<<1) ? 0 : (1<<6)) |
           (PINF&(1<<0) ? 0 : (1<<7));
}

/* Column pin config
  * col: 0  1  2  3  4  5  6  7  8
  * pin: C7 C6 C5 C4 C3 C2 C1 C0 E1
 */
static void unselect_cols(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRE  |= 0b00000010; // PE: 1 0
    PORTE |= 0b00000010;
    DDRC  |= 0b11111111; // PC: 7 6 5 4 3 2 1 0
    PORTC |= 0b11111111;
}

static void select_col(uint8_t col)
{
    // Output low(DDR:1, PORT:0) to select
    switch (col) {
        case 8:
            DDRC  |= (1<<7);
            PORTC &= ~(1<<7);
            break;
        case 7:
            DDRC  |= (1<<6);
            PORTC &= ~(1<<6);
            break;
        case 6:
            DDRC  |= (1<<5);
            PORTC &= ~(1<<5);
            break;
        case 5:
            DDRC  |= (1<<4);
            PORTC &= ~(1<<4);
            break;
        case 4:
            DDRC  |= (1<<3);
            PORTC &= ~(1<<3);
            break;
        case 3:
            DDRC  |= (1<<2);
            PORTC &= ~(1<<2);
            break;
        case 2:
            DDRC  |= (1<<1);
            PORTC &= ~(1<<1);
            break;
        case 1:
            DDRC  |= (1<<0);
            PORTC &= ~(1<<0);
            break;
        case 0:
            DDRE  |= (1<<1);
            PORTE &= ~(1<<1);
            break;
    }
}