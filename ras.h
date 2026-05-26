
#ifndef RAS_H_
#define RAS_H_

#include <stdbool.h>
#include "launchpad.h"



// RAS ISR: NOT .c --> ras_asm.asm
void RotaryAngleSensorISR();

// Initialize the RAS
/*
 * 1. Initialize the state object of the RAS
 * 2. Enable the ADC and Sequencer Peripheral pair (w/ PRI0)
 * 3. Configure the ADC and Sequencer Peripheral pair (on CH7)
 * 4. Register the ISR handler for the RAS
 * 5. Enable Interrupts and the ADC Sequencer
 */
void RotaryAngleSensorInit();
// Register the callback event
void RotaryAngleSensorRegister(Event* callback_event);

bool getNewInput();

// Trigger rotation angle reading
void RasTriggerReading();

// Return rotation angle reading in degrees
int RasDataRead();






#endif /* RAS_H_ */
