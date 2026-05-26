/*
 * File: lab_project_main.c
 *
 * Final Lab Project ECE 266 Spring 2026 Group C1
 * Main program of the final lab project.
 * Authors: Trevor Jedrzejas and Justin Skariah (C/M: SP26/SP26)
*/

/*
 * Buzzer wire plugs into to grove baseboard port J17
 * Buzzer signal connects to GPIO Port C Pin 5 (PC5)
 * PC5 connects to Wide-timer 0 with CC & PWM0 (WT0CCP1)
 *
 * Rotary angle sensor plugs into grove baseboard port J5
 * RAS signal connects to GPIO Port D Pin 0 (PD0)
 * __
 *
 * Seven segment display plugs into grove baseboard port J10
 * ___
 * ___
 *
 * External Buttons?
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * Put better descriptions later on after cleaning up
 *
 * Put into README.md?
 * UPDATE**********************************
 * - Interface allows us to:
 * - Choose between what to play: Tones, Tracks, or Disable (default).
 * - Choose between how to play it: Volume [0,100] and Speed (x1.00,x1.25,x1.50,x2.00) {100,125,150,200}
 * - Choose between how to modify it: Tuning [-90,90] (fine tuning frequency) and Octave [4,7] (biased) (coarse tuning frequency).
 *
 * <-- which button is being pressed, select mode, modify value using ras
 * --> display tone, track, volume, speed, tuning, and octave as well as possibly print (or display using another display) Note and exact Frequency
 *
 * - **********************************************************Left button modifies which tone or track we're on or disables the system
 * - **********************************************************Right button modifies volume, speed, tuning, and octave
 * - Rotary angle sensor changes the values of the selected value
 * - Seven segment display (and possibly LCD) displays values (and possibly printed outputs)
 *
 * - Ideas:
 * - Possibly implement more buttons so that we don't rely on the two on chip --> Breadboard implementation
 * - Instead of disable on the left button, we have a specific button that is for enabling and disabling
 * - LCD to display specifically what we are doing. (To display if we were on volume, tune or track mode)
 * - LCD for descriptions and LED for value (Seg7)
 * - Left button to control the track and tone, then rotary to control which track we are on
 * - Figure out what to implement in assembly --> whatever is the most performance intensive
 * -
*/

/*Directives*/
#include "launchpad.h"

#include "music.h"
#include "seg7.h"
#include "ras.h"

#include "tracks.h"

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>






/*Structuring Elements*/
typedef enum {
    MODE_TONE,
    MODE_TRACK,
    MODE_TUNING,
    MODE_OCTAVE,
    MODE_VOLUME,
    MODE_SPEED,
    MODE_CTL_NUM,
} ButtonModes;

typedef struct {
    int tone;       // Current tone (value encoded)
    int track;      //
    int tuning;     // Current tuning level
    int octave;     // Current octave level
    int volume;     // Current sound level
    int speed;      // Current speed level
} BuzzerParams;


/*Global Variables and pointers*/
typedef struct{
    ButtonModes button_mode;    //
    BuzzerParams buzzer_params; //
    bool buzzer_on;             // Buzzer is on if true, false otherwise.
    bool buzzer_disabled;       //
    bool is_track_playing;
    int track_note_num;
} BuzzerState;
BuzzerState buzzer_sys = {MODE_TONE, {0,0,0,0,5,100}, false, true, false,0};
BuzzerState* buzzer_sys_ptr = &buzzer_sys;


/*System Events*/
Event check_push_button_event;
Event play_sound_event;
Event ras_trigger_event;
Event ras_data_event;
Event display_update_event;



uint32_t mode_change_time = 0;
const uint32_t LABEL_DURATION_MS = 1000;        // Shows the mode number for one second (1000 ms = 1 second)
                                                // when button two is pressed
/*Interrupt-driven mode switcher*/
void CheckPushButton(Event *event)
{
    switch (PushButtonRead())
    {
    case 1:
        if (buzzer_sys.buzzer_disabled){
            buzzer_sys.buzzer_disabled = false;
        }
        else{
            buzzer_sys.buzzer_disabled = true;
            MusicTurnOffBuzzer();
        }
        break;

    case 2:
        buzzer_sys.button_mode = (ButtonModes)(((int)buzzer_sys.button_mode+1)%MODE_CTL_NUM);
        if(buzzer_sys.button_mode==MODE_TRACK){
            buzzer_sys.is_track_playing = true;
        }
        else {
            buzzer_sys.is_track_playing = false;
        }
        mode_change_time = EventGetCurrentTime();   // Records the press so UpdateDisplay knows to flash the mode number
        break;
    }
    // add pb to enable/disable changes to values?
}
/*Buzzer sound driver*/
void PlaySound(Event *event)
{
    int delay = 500;
    if(!buzzer_sys.buzzer_disabled){
        if (!buzzer_sys.buzzer_on){
            if(!buzzer_sys.is_track_playing){
                MusicSetBuzzer(
                    buzzer_sys_ptr->buzzer_params.tone,
                    buzzer_sys_ptr->buzzer_params.volume,
                    buzzer_sys_ptr->buzzer_params.tuning,
                    buzzer_sys_ptr->buzzer_params.octave
                );
            }
            else{
                MusicSetBuzzer_Track(
                        track1_notes[buzzer_sys.track_note_num],
                        buzzer_sys_ptr->buzzer_params.volume
                        );
                buzzer_sys.track_note_num=(buzzer_sys.track_note_num+1)%(sizeof(track1_notes)/sizeof(track1_notes[0]));

            }
            buzzer_sys.buzzer_on = true;
        }
        else{
            MusicTurnOffBuzzer();
            buzzer_sys.buzzer_on = false;
        }
        if(!buzzer_sys.is_track_playing){
            if(buzzer_sys_ptr->buzzer_params.speed>100){
                delay = (int)(500.0*(100.0/buzzer_sys_ptr->buzzer_params.speed)); // buzzer ON and OFF time is equal
            }
            else if(!buzzer_sys.buzzer_on && buzzer_sys_ptr->buzzer_params.speed<100){
                delay = (1000*100/buzzer_sys_ptr->buzzer_params.speed-500); //(100/speed)*1000-500 => 500 ms ON ALWAYS while 1500, 3500, 7500, ... OFF.
            }
        }
        else{
            if(buzzer_sys.buzzer_on){
                delay=track1_duration[buzzer_sys.track_note_num];
            }
            else{
                delay=50;
            }
        }
    }
    // Schedule the next callback
    EventSchedule(&play_sound_event, EventGetCurrentTime() + delay);//use relative to sys time, not event time, MUST CLEAR EACH CYCLE BEFORE MOVING FORWARD
}
void TriggerRotationAngleReading(Event *event)
{
    // Trigger ADC sampling for the RAS
    RasTriggerReading();
    // Schedule the next callback in 1000 milliseconds
    EventSchedule(event, EventGetCurrentTime() + 1000); //use relative to sys time, not event time
}
void ProcessRotationAngleReading(Event *event) //update so it waits till change to ras?
{
    int angle = RasDataRead();
    switch(buzzer_sys.button_mode){
        case MODE_TONE:
            if(angle>=1800){
                buzzer_sys_ptr->buzzer_params.tone = 11;
            }
            else{
                buzzer_sys_ptr->buzzer_params.tone = angle/150; // 12 bins (12 tones: [0,11])
            }
            break;
        case MODE_TUNING:
            buzzer_sys_ptr->buzzer_params.tuning = angle/10-90; // 180 bins (181) shifted to be centered around 0 ([-90, 90] Hz)
            break;
        case MODE_OCTAVE:
            if(angle>=1800){
                buzzer_sys_ptr->buzzer_params.octave = 3;
            }
            else{
                buzzer_sys_ptr->buzzer_params.octave = angle/450; // 4 bins (4 octaves: [0,3])
            }
            break;
        case MODE_VOLUME:
            buzzer_sys_ptr->buzzer_params.volume = angle/18; // 100 bins (101) representing percentages ([0, 100] %)
            break;
        case MODE_SPEED: {
            int bins = angle/300;
            // reschedule events?
            if(bins<2){
                buzzer_sys_ptr->buzzer_params.speed = (25+(25*bins));
            }
            else if(bins<5){
                buzzer_sys_ptr->buzzer_params.speed = (100+(25*(bins-2)));
            }
            else{
                buzzer_sys_ptr->buzzer_params.speed = 200; // 6 bins (6 speeds: {25,50,100,125,150,200}). NOTE: speed must be divided by 100 to get true multiplier.
            }
            break; }
        default: break; // track
    }
}

/*
 * 3 different states for UpdateDisplay
 *
 * 1.) Sound Disabled: When button one is pressed to disable all sound, it will display ----
 * 2.) Mode Change: When the right button is pressed to change mode, it briefly shows a number 1 - 5 to indicate what mode we are going to be in
 * 3.) Normal Display: Displays the number of the mode that we are currently on
 *
 * Ranges
 * ------
 * Tone: 0 - 11                         --> Indexes the 12 note table
 * Track: 0 - 124                       --> Plays Pirates of the Caribbean :)
 * Tuning: [-90, 90]                    --> Frequency offset
 * Octave: 0 - 3                        --> Octave Shift
 * Volume: 0 - 100%                     --> Loudness percentage
 * Speed: 25, 50, 100, 125, 150, 200    --> Speed
 *
 */

void UpdateDisplay(Event *event)
{
    uint32_t now = EventGetCurrentTime();
    bool show_mode_number = (now - mode_change_time) < LABEL_DURATION_MS;

    if (buzzer_sys.buzzer_disabled) {
        // Buzzer is off, show four dashes
        Seg7DisplayLabel(SEG7_MINUS, SEG7_MINUS, SEG7_MINUS, SEG7_MINUS);
    }
        // Shows what state we are in | 1 --> Tone | 2 --> Track | 3 --> Tuning | 4 --> Octave | 5 --> Volume | 6 --> Speed |
    else if (show_mode_number) {
        Seg7DisplayInt((int)buzzer_sys.button_mode + 1);
    }
    else {
        switch(buzzer_sys.button_mode){
            case MODE_TONE:                                                         // Switches to Tone
                Seg7DisplayInt(buzzer_sys_ptr->buzzer_params.tone);
                break;
            case MODE_TRACK:                                                        // Switches to Track
                Seg7DisplayInt(buzzer_sys_ptr->track_note_num);
                break;
            case MODE_TUNING:                                                       // Switches to Tuning
                Seg7DisplaySigned(buzzer_sys_ptr->buzzer_params.tuning);
                break;
            case MODE_OCTAVE:                                                       // Switches to Octave
                Seg7DisplayInt(buzzer_sys_ptr->buzzer_params.octave);
                break;
            case MODE_VOLUME:                                                       // Switches to Volume
                Seg7DisplayInt(buzzer_sys_ptr->buzzer_params.volume);
                break;
            case MODE_SPEED:                                                        // Switches to Speed
                Seg7DisplayInt(buzzer_sys_ptr->buzzer_params.speed);
                break;
        }
    }
    EventSchedule(&display_update_event, EventGetCurrentTime() + 100);
}

/*Main program*/
void main(void){
    // Device and module initializations
    LaunchPadInit();
    MusicInitBuzzer();
    Seg7Init();
    RotaryAngleSensorInit();


    // Polling-based events. Initialization and Scheduling
    EventInit(&play_sound_event, PlaySound);
    EventSchedule(&play_sound_event, 100);
    EventInit(&ras_trigger_event, TriggerRotationAngleReading);
    EventSchedule(&ras_trigger_event, 500);
    EventInit(&display_update_event, UpdateDisplay);        // Schedules the Seg7 as a polled event
    EventSchedule(&display_update_event, 700);              // Turns on 700 ms after startup


    // Interrupt-based events. Initialization and Registration
    EventInit(&check_push_button_event, CheckPushButton);
    PushButtonEventRegister(&check_push_button_event);
    EventInit(&ras_data_event, ProcessRotationAngleReading);
    RotaryAngleSensorRegister(&ras_data_event);


    /*Dead loop*/
    while (true){
        __asm("    wfi");
        EventExecute();
    }
}



