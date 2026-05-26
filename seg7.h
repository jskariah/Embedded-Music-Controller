/*
 * File: seg7.h
 *
 * Seven segment display header interface
 * Author credits: Zhao Zhang at UIC for ECE 266 SP26 (C/M: FA19/??)
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef SEG7_H_
#define SEG7_H_

#define SEG7_MINUS  10
#define SEG7_BLANK  11

/*
 * The state of the 4-digit 7-segment display
 */
typedef struct {
    uint8_t digit[4];           // 4 digits, digit[0] for the right most
    bool colon_on;              // if the colon (dots) is on or off
} Seg7Display;

/*
 * Interface functions
 */

// Initialize the port connection to TiM1637 and the 7-segment display
void Seg7Init();

// Update all 4 digits of the 7-segment displays
void Seg7RawUpdate(uint8_t code[]);

// Update the 4-digit 7-segment display with digit numbers (not 7-segment display pattern)
void Seg7Update(Seg7Display *seg7);

// into 4 decimal digits. digits[0] = ones ... digits[3] = thousands.
void Seg7DecomposeInt(int value, uint8_t *digits);

// Display a nonnegative integer (0-9999) on the 7-segment display.
void Seg7DisplayInt(int value);

// Display a nonnegative integer (0-9999) on the 7-segment display.
void Seg7DisplayInt(int value);

// Display a signed integer (-999 to 999) with a minus sign when negative.
void Seg7DisplaySigned(int value);

#endif /* SEG7_H_ */
