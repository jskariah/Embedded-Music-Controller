# Embedded Music Controller

## Overview

This project is an embedded music controller built for the TM4C/Tiva C LaunchPad. The system uses a PWM-controlled buzzer, rotary angle sensor, push buttons, and a 4-digit 7-segment display to let the user control tones, tracks, tuning, octave, volume, and playback speed.

The project was developed as a project by Justin Skariah and Trevor Jedrzejas.

## Features

- PWM-based buzzer output
- Rotary angle sensor input through ADC
- Push-button mode switching
- 4-digit 7-segment display output
- Event-driven control loop
- Interrupt-driven sensor handling
- ARM assembly routines for selected hardware interactions
- Adjustable tone selection
- Adjustable tuning offset
- Adjustable octave range
- Adjustable volume
- Adjustable playback speed
- Preprogrammed melody playback

## Hardware Used

- TM4C/Tiva C LaunchPad
- Grove Base BoosterPack
- Grove buzzer
- Grove rotary angle sensor
- Grove 4-digit 7-segment display
- On-board push buttons

## Hardware Connections

| Component | Connection |
|---|---|
| Buzzer | Grove J17 |
| Buzzer Signal | GPIO PC5 |
| PWM Timer | Wide Timer 0, WT0CCP1 |
| Rotary Angle Sensor | Grove J5 |
| Rotary Angle Sensor Signal | GPIO PD0 / ADC Channel 7 |
| 7-Segment Display | Grove J10 |

## User Controls

The system has multiple control modes. The user can cycle through modes and use the rotary angle sensor to change the selected value.

| Mode | Description |
|---|---|
| Tone | Selects one of 12 base tones |
| Track | Plays a preprogrammed melody track |
| Tuning | Fine-tunes the frequency offset |
| Octave | Changes the octave range |
| Volume | Adjusts buzzer volume |
| Speed | Adjusts playback speed |

## Display Behavior

The 7-segment display provides feedback based on the current system state.

| Display State | Meaning |
|---|---|
| `----` | Buzzer is disabled |
| Mode number | Briefly shows the selected mode after switching |
| Value display | Shows the current value for tone, track, tuning, octave, volume, or speed |

## Project Structure

```text
Embedded-Music-Controller/
├── lab_project_main.c
├── music.h
├── music_buzzer.c
├── pwm_buzzer.c
├── pwm_buzzer.h
├── ras.c
├── ras.h
├── ras_asm.asm
├── seg7.h
├── seg7_asm.asm
├── seg7digit.c
├── seg7raw.c
├── handlers.asm
├── handlers_asm.h
├── tracks.h
├── tm4c123gh6pm_startup_ccs.c
├── tm4c123gh6pm.cmd
└── README.md
```

## File Descriptions

| File | Description |
|---|---|
| `lab_project_main.c` | Main program logic, event scheduling, button handling, display updates, and mode control |
| `music.h` | Music interface and note definitions |
| `music_buzzer.c` | Converts tone, volume, tuning, and octave settings into buzzer output |
| `pwm_buzzer.c` | Configures and controls the PWM hardware for buzzer playback |
| `pwm_buzzer.h` | Header file for PWM buzzer functions |
| `ras.c` | Rotary angle sensor initialization, ADC triggering, and angle conversion |
| `ras.h` | Header file for rotary angle sensor functions |
| `ras_asm.asm` | ARM assembly interrupt service routine for ADC sensor readings |
| `seg7.h` | Header file for 7-segment display functions |
| `seg7_asm.asm` | ARM assembly routine for decomposing integers into display digits |
| `seg7digit.c` | Converts numbers and signed values into 7-segment display output |
| `seg7raw.c` | Low-level communication with the TM1637 7-segment display driver |
| `handlers.asm` | ARM assembly display update handler |
| `handlers_asm.h` | Header file for assembly handler functions |
| `tracks.h` | Preprogrammed note and duration arrays for melody playback |
| `tm4c123gh6pm_startup_ccs.c` | Startup code for Code Composer Studio |
| `tm4c123gh6pm.cmd` | Linker command file for the TM4C123GH6PM microcontroller |

## How It Works

The system uses an event-driven design. The main loop waits for interrupts and then executes scheduled events.

The main events include:

1. Checking push-button input
2. Playing or stopping the buzzer
3. Triggering rotary angle sensor ADC readings
4. Processing rotary angle sensor data
5. Updating the 7-segment display

The system continuously updates the selected parameter based on the rotary angle sensor and changes buzzer behavior based on the current mode.

## PWM Buzzer Control

The buzzer is controlled using PWM through Wide Timer 0. The PWM period determines the pitch, and the PWM duty cycle determines the volume.

The project supports:

- Individual tone playback
- Track playback
- Volume control
- Octave shifting
- Fine tuning through frequency offsets

## Rotary Angle Sensor

The rotary angle sensor is read through ADC0 Sequencer 1. The ADC value is converted into an angle-based value and mapped to different parameter ranges depending on the current mode.

Examples:

- Tone mode maps the rotary input to 12 tones
- Tuning mode maps the input to a frequency offset range
- Octave mode maps the input to octave levels
- Volume mode maps the input to a percentage
- Speed mode maps the input to playback speed options

## 7-Segment Display

The 7-segment display shows the current system state and selected values.

The display can show:

- Nonnegative integers
- Signed values for tuning
- Dashes when the buzzer is disabled
- Temporary mode numbers after switching modes

Some display logic is supported by ARM assembly for digit decomposition.

## ARM Assembly Components

This project includes ARM assembly routines for lower-level embedded functionality.

Assembly was used for:

- ADC interrupt handling for the rotary angle sensor
- Scheduling sensor callback events
- Clearing ADC interrupt flags
- Decomposing integer values into display digits
- Supporting display update logic

## How to Build and Run

This project is intended to be built and flashed using Texas Instruments Code Composer Studio.

General steps:

1. Open Code Composer Studio.
2. Import the project into the workspace.
3. Make sure the TM4C/Tiva C LaunchPad is connected.
4. Build the project.
5. Flash the program to the board.
6. Use the push buttons and rotary angle sensor to control the buzzer.

## What I Learned

Through this project, I practiced:

- Embedded C programming
- ARM assembly programming
- PWM signal generation
- ADC configuration and sampling
- Interrupt-driven input handling
- Event-driven embedded system design
- Hardware timer configuration
- 7-segment display control
- Sensor-to-output system integration
- Debugging embedded hardware/software interactions
- Collaborating on a larger lab project

## Future Improvements

Potential future improvements include:

- Adding an LCD display for clearer mode labels
- Adding more physical buttons for direct mode selection
- Supporting multiple saved tracks
- Adding pause and resume controls
- Adding a visual LED indicator for active modes
- Improving track timing accuracy
- Adding support for custom melodies
- Creating a wiring diagram for easier setup

## Authors

Created by Justin Skariah and Trevor Jedrzejas.

Developed for ECE 266.
