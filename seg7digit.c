/*
 * File: seg7digit.c
 *
 * Seven segment digit update component for seven segment display
 * Author credits: Zhao Zhang at UIC for ECE 266 SP26 (C/M: FA19/SP24)
 */

#include <stdint.h>
#include <stdbool.h>
#include "seg7.h"


/*
 * Special indicies into the coding table beyong 0-9,
 * This lets me able to implement both a totally blank screen on the Seg7 and a screen of dashes.
 */
#define SEG7_MINUS  10
#define SEG7_BLANK  11

/*
 * 7-segment coding table. See https://en.wikipedia.org/wiki/Seven-segment_display. The segments
 * are named as A, B, C, D, E, F, G. In this coding table, segments A-G are mapped to bits 0-7.
 * Bit 7 is not used in the coding. This display uses active high signal, in which '1' turns ON a
 * segment, and '0' turns OFF a segment.
 */
static uint8_t seg7_coding_table[12] = {
        0b00111111, //digit 0
        0b00000110, //digit 1
        0b01011011, //digit 2
        0b01001111, //digit 3
        0b01100110, //digit 4
        0b01101101, //digit 5
        0b01111101, //digit 6
        0b00000111, //digit 7
        0b01111111, //digit 8
        0b01101111, //digit 9
        0b01000000, // 10: minus sign (segment G only)
        0b00000000, // 11: blank (nothing lit)
};

/*
 * Update the 7-segment display using the Seg7Display structure.
 */
void Seg7Update(Seg7Display *seg7)
{
    uint8_t seg7_code[4];
    uint8_t colon_code;

    // Get the raw encoding for the colon
    colon_code = seg7->colon_on ? 0b10000000 : 0b00000000;

    // Get the raw encoding for 7-segment digits
    seg7_code[0] = seg7_coding_table[seg7->digit[0]] + colon_code;
    seg7_code[1] = seg7_coding_table[seg7->digit[1]] + colon_code;
    seg7_code[2] = seg7_coding_table[seg7->digit[2]] + colon_code;
    seg7_code[3] = seg7_coding_table[seg7->digit[3]] + colon_code;

    // Update the 7-segment
    Seg7RawUpdate(seg7_code);
}

/*
 * Decompose an integer (via assembly) and push it to the display.
 */
void Seg7DisplayInt(int value)
{
    Seg7Display display;

    // Clamp so we never index outside seg7 coding table[0..9].
    if (value < 0){
        value = 0;
    }

    if (value > 9999){
        value = 9999;
    }

    // Fill display.digit[0..3] via assembly.
    Seg7DecomposeInt(value, display.digit);

    // Turns colon off plain number display.
    display.colon_on = false;

    Seg7Update(&display);
}


// Displays a signed integer from the range [-999, 999]
// We must reserve a spot for the minus sign always
void Seg7DisplaySigned(int value)
{
    Seg7Display display;
    uint8_t digits[4];

    // Clamp to what fits in "sign + 3 digits"
    if (value >  999){
        value =  999;
    }

    if (value < -999){
        value = -999;
    }

    // Work with magnitude; remember the sign
    bool negative = (value < 0);
    int abs_value;

    if (negative) {
        abs_value = -value;
    } else {
        abs_value = value;
    }

    // Decompose value into digit positions (asm)
    Seg7DecomposeInt(abs_value, digits);

    // Always show ones place. Blank any leading zeros.
    display.digit[0] = digits[0];

    if (abs_value >= 10) {
        display.digit[1] = digits[1];
    } else {
        display.digit[1] = SEG7_BLANK;
    }

    if (abs_value >= 100) {
        display.digit[2] = digits[2];
    } else {
        display.digit[2] = SEG7_BLANK;
    }

    display.digit[3] = SEG7_BLANK;  // reserved for sign or blank

    // Drop the minus sign one position left of the MSB
    if (negative) {
        if (abs_value >= 100){
            display.digit[3] = SEG7_MINUS;
        }
        else if (abs_value >= 10){
            display.digit[2] = SEG7_MINUS;
        }
        else {
            display.digit[1] = SEG7_MINUS;
        }
    }

    display.colon_on = false;
    Seg7Update(&display);
}

/*
 * Display a 4-character label.  Each digit is an index into seg7_coding_table.
 * d3 is the leftmost position, d0 is the rightmost.
 *
 * Each argument is an index into seg7 coding table so that callers can pass digits 0-9, seg7 minus and blank
 * to build specific patterns.
 *
 */

void Seg7DisplayLabel(uint8_t d3, uint8_t d2, uint8_t d1, uint8_t d0)
{
    Seg7Display display;
    display.digit[3] = d3;
    display.digit[2] = d2;
    display.digit[1] = d1;
    display.digit[0] = d0;
    display.colon_on = false;
    Seg7Update(&display);
}


