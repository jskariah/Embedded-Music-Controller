// all rights reserved to respective creators. this is just implemented for fun.

// NOTE: All tracks are one channel (one buzzer, no chords) for now
// Track #1: Part of the Pirates of the Caribbean main song (https://onlinesequencer.net/1657950#)

#include "music.h"

#define DURATION_120_EIGHTH      250
#define DURATION_120_QUARTER     500
#define DURATION_120_HALF        1000
#define DURATION_120_WHOLE       2000

int track1_notes[] = {
                   NOTE_A4,
                   //...
                   NOTE_C5,
                   NOTE_D5, NOTE_D5, NOTE_D5,
                   NOTE_E5, NOTE_F5, NOTE_F5, NOTE_F5,
                   NOTE_G5,
                   NOTE_E5, NOTE_E5,
                   NOTE_D5,
                   //...
                   NOTE_C5, NOTE_C5,
                   NOTE_D5,
                   //...
                   NOTE_C5,
                   NOTE_D5, NOTE_D5, NOTE_D5,
                   NOTE_E5, NOTE_F5, NOTE_F5, NOTE_F5,
                   NOTE_G5,
                   NOTE_E5, NOTE_E5,
                   NOTE_D5,
                   //...
                   NOTE_C5,
                   NOTE_D5,
                   0,   // 4 s
                   NOTE_C5,
                   NOTE_D5, NOTE_D5, NOTE_D5,
                   NOTE_F5,
                   NOTE_G5, NOTE_G5, NOTE_G5,
                   NOTE_A5, 53630, 53630, NOTE_A5,
                   NOTE_G5,
                   NOTE_F5,
                   NOTE_D5, NOTE_D5,
                   NOTE_E5, NOTE_F5, NOTE_F5,
                   NOTE_G5,
                   NOTE_F5,
                   NOTE_D5, NOTE_D5,
                   NOTE_F5, NOTE_E5, NOTE_E5, NOTE_F5,
                   NOTE_D5,
                   0, 0,    // 7 s
                   // ....
                   NOTE_A5,
                   NOTE_C6,
                   NOTE_D6, NOTE_D6, NOTE_D6,
                   NOTE_E6, NOTE_F6, NOTE_F6, NOTE_F6, 0, NOTE_E6, NOTE_E6,
                   NOTE_D6,
                   // ....
                   NOTE_C6, NOTE_C6,
                   NOTE_D6,
                   // ....
                   NOTE_A5,
                   NOTE_C6,
                   NOTE_D6, NOTE_D6, NOTE_D6,
                   NOTE_E6, NOTE_F6, NOTE_F6, NOTE_F6, 0, NOTE_E6, NOTE_E6,
                   NOTE_D6,
                   // ....
                   NOTE_D6,
                  NOTE_C6,
                  NOTE_D6,
                  0, // 10 s
                  NOTE_A5,
                  NOTE_C6,
                  NOTE_D6, NOTE_D6, NOTE_D6,
                  NOTE_F6,
                  NOTE_G6, NOTE_G6, NOTE_G6,
                  NOTE_A6, 26815, 26815, NOTE_A6,
                  NOTE_G6,
                  NOTE_A6,
                  NOTE_D6, 0 /*11.5*/,NOTE_D6,
                  NOTE_E6, NOTE_F6, NOTE_F6,
                  NOTE_G6,
                  NOTE_A6,
                  NOTE_D6, 0, NOTE_D6, // 12.25
                  NOTE_F6, NOTE_E6, NOTE_E6,
                  NOTE_D6, 45097, NOTE_D6,
                  // 13
                  // ***********************



};

int track1_duration[]= {
                           DURATION_120_EIGHTH,
                           //...
                           DURATION_120_EIGHTH,
                           DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH, DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH,
                           DURATION_120_QUARTER, DURATION_120_QUARTER,
                           DURATION_120_EIGHTH,
                           //...
                           DURATION_120_EIGHTH, DURATION_120_EIGHTH,
                           DURATION_120_HALF,
                           //...
                           DURATION_120_EIGHTH,
                           DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH, DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH,
                           DURATION_120_QUARTER, DURATION_120_QUARTER,
                           DURATION_120_EIGHTH,
                           //...
                           DURATION_120_EIGHTH,
                           DURATION_120_HALF,
                           DURATION_120_QUARTER, // 0
                           DURATION_120_EIGHTH,
                           DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH,
                           DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH, DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH,
                           DURATION_120_HALF, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH, DURATION_120_QUARTER, DURATION_120_QUARTER,
                           DURATION_120_QUARTER,
                           DURATION_120_EIGHTH,
                           DURATION_120_HALF, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH, DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH,
                           DURATION_120_HALF, DURATION_120_EIGHTH, // 0
                           // ....
                           DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH,
                           DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH, DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH, DURATION_120_QUARTER/*0*/, DURATION_120_QUARTER, DURATION_120_QUARTER,
                           DURATION_120_EIGHTH,
                           // ....
                           DURATION_120_EIGHTH, DURATION_120_EIGHTH,
                           DURATION_120_QUARTER,
                           // ....
                           DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH,
                           DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH, DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH, DURATION_120_QUARTER/*0*/, DURATION_120_QUARTER, DURATION_120_QUARTER,
                           DURATION_120_EIGHTH,
                           // ....
                           DURATION_120_EIGHTH,
                           DURATION_120_EIGHTH,
                          DURATION_120_QUARTER,
                          DURATION_120_EIGHTH,
                          DURATION_120_EIGHTH,
                          DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                          DURATION_120_EIGHTH,
                          DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                          DURATION_120_EIGHTH, DURATION_120_QUARTER, DURATION_120_QUARTER, DURATION_120_EIGHTH,
                          DURATION_120_EIGHTH,
                          DURATION_120_EIGHTH,
                          DURATION_120_QUARTER, DURATION_120_EIGHTH/*0*/,DURATION_120_EIGHTH,
                          DURATION_120_EIGHTH, DURATION_120_QUARTER, DURATION_120_QUARTER,
                          DURATION_120_QUARTER,
                          DURATION_120_EIGHTH,
                          DURATION_120_QUARTER, DURATION_120_EIGHTH/*0*/,DURATION_120_EIGHTH,
                          DURATION_120_EIGHTH, DURATION_120_QUARTER, DURATION_120_QUARTER,
                          DURATION_120_EIGHTH, DURATION_120_EIGHTH, DURATION_120_QUARTER,
                          // ***********************





};
