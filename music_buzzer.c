/*
 * File: music_buzzer.h
 *
 * Music player header interface
 * Author credits: Zhao Zhang at UIC for ECE 266 SP26 (C/M: ??/??)
 * Adapted by Trevor Jedrzejas and Justin Skariah (C/M: SP26/SP26)
 */

#include "music.h"
#include "pwm_buzzer.h"

#include <math.h>

float buzzer_baseToneCycles[NUM_BASE_TONE] = // based on the fourth octave
{
 NOTE_C4,       // C4 (50 MCC/261.63 Hz ~ 191.110 kCC)
 NOTE_C4S,      // C4#/D4F
 NOTE_D4,       // D4 (50 MCC/293.66 Hz ~ 170.265 kCC)
 NOTE_D4S,      // D4#/E4F
 NOTE_E4,       // E4 (50 MCC/329.63 Hz ~ 151.685 kCC)
 NOTE_F4,       // F4 (50 MCC/349.23 Hz ~ 143.172 kCC)
 NOTE_F4S,      // F4#/G4F
 NOTE_G4,       // G4 (50 MCC/392.00 Hz ~ 127.551 kCC)
 NOTE_G4S,      // G4#/A4F
 NOTE_A4,       // A4 (50 MCC/440.00 Hz ~ 113.636 kCC)
 NOTE_A4S,      // A4#/B4F
 NOTE_B4,       // B4 (50 MCC/493.88 Hz ~ 101.239 kCC)
};




void MusicInitBuzzer()
{
    PwmBuzzerInit();
}
void MusicTurnOffBuzzer()
{
    PwmBuzzerSet(1000, 0);
}

void MusicSetBuzzer(int tone, int volume, int tuning, int octave) //note: octave = 0 is the fourth octave (using a shifted scale).
{
    float octaveMultiplier = powf(2,(octave));
    volatile float clockCycles=(50000000)/(octaveMultiplier*(50000000/buzzer_baseToneCycles[tone])+tuning);
    PwmBuzzerSet(clockCycles, (clockCycles*volume)/400); // only 0% to 25% duty cycle to save our ears
}
void MusicSetBuzzer_Track(int note_cc, int volume){
    PwmBuzzerSet(note_cc, (note_cc*volume)/400); // only 0% to 25% duty cycle to save our ears
}
