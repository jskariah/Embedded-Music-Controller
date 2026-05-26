/*
 * File: music.h
 *
 * Music player header interface
 * Author credits: Zhao Zhang at UIC for ECE 266 SP26 (C/M: SP26/SP26)
 * Adapted by Trevor Jedrzejas and Justin Skariah (C/M: SP26/SP26)
 */

#include <stdbool.h>
#include <stdint.h>

#ifndef MUSIC_H_
#define MUSIC_H_





// Define the number of supported music pitches and volume levels
#define NUM_BASE_TONE            12
#define NOTE_C4     191110      // C4 (50 MCC/261.63 Hz ~ 191.110 kCC)
#define NOTE_C4S    180388      // C4#/D4F
#define NOTE_D4     170265      // D4 (50 MCC/293.66 Hz ~ 170.265 kCC)
#define NOTE_D4S    160705      // D4#/E4F
#define NOTE_E4     151685      // E4 (50 MCC/329.63 Hz ~ 151.685 kCC)
#define NOTE_F4     143172      // F4 (50 MCC/349.23 Hz ~ 143.172 kCC)
#define NOTE_F4S    135138      // F4#/G4F
#define NOTE_G4     127551      // G4 (50 MCC/392.00 Hz ~ 127.551 kCC)
#define NOTE_G4S    120395      // G4#/A4F
#define NOTE_A4     113636      // A4 (50 MCC/440.00 Hz ~ 113.636 kCC)
#define NOTE_A4S    107259      // A4#/B4F
#define NOTE_B4     101239      // B4 (50 MCC/493.88 Hz ~ 101.239 kCC)

#define NOTE_C5     95557
#define NOTE_D5     85133
#define NOTE_E5     75843
#define NOTE_F5     71486
#define NOTE_G5     63776
#define NOTE_A5     56818
#define NOTE_B5     50620

#define NOTE_C6     47779
#define NOTE_D6     42567
#define NOTE_E6     37922
#define NOTE_F6     35743
#define NOTE_G6     31888
#define NOTE_A6     28409
#define NOTE_B6     25310

// Initialize the buzzer for music note playing
void MusicInitBuzzer();
// Turn off buzzer
void MusicTurnOffBuzzer();


void MusicSetBuzzer(int tone, int volume, int tuning, int octave);
void MusicSetBuzzer_Track(int note_cc, int volume);

#endif /* MUSIC_H_ */
