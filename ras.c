
#include "ras.h"



typedef struct {
    Event *callback_event;      //  pointer to Event object
    uint32_t raw_data;          //  raw reading from the associated ADC
    bool new_input;             //  result of logic verifying input changes
} RotaryAngleSensorState;   //      State Structure for RAS

// State Object for the RAS
RotaryAngleSensorState rotary_angle_sensor;



// RAS ISR: IGNORE --> ras_asm.asm
/*static void RotaryAngleSensorISR(){

}*/

// Initialize the RAS
void RotaryAngleSensorInit(){
    // State Object initial values
    rotary_angle_sensor.callback_event = NULL;  // no event before enables
    //rotary_angle_sensor.raw_data;             // *** ignore
    rotary_angle_sensor.new_input = false;      // no input has been recorded yet.

    // ADC Peripheral
    /*
     * Enable ADC0
     * Configure ADC0 to use Sequencer #1 for the RAS
     * Configure ADC0 Sequencer #1 on Channel #7 Step #0 to enable an interrupt at the end
     * ---
     * Register the ADC #0 Sequencer #1 to use the RAS ISR
     * Enable Interrupts for ADC0 Sequencer #1 (configuration built-in)
     * Enable the Sequence pass for Sequencer #1
     */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCSequenceConfigure(ADC0_BASE, 1 /* sequencer */, ADC_TRIGGER_PROCESSOR, 0 /* priority */);
    ADCSequenceStepConfigure(ADC0_BASE, 1 /* sequencer */, 0 /* step */, ADC_CTL_CH7 | ADC_CTL_IE | ADC_CTL_END);

    ADCIntRegister(ADC0_BASE, 1 /* sequencer */, RotaryAngleSensorISR);
    ADCIntEnable(ADC0_BASE, 1 /* sequencer */);
    ADCSequenceEnable(ADC0_BASE, 1 /* sequencer */);
}
// Register the callback event
void RotaryAngleSensorRegister(Event* callback_event){
    assert(EventInitialized(callback_event));
    rotary_angle_sensor.callback_event = callback_event;    // sets the state object's event to this.
}


// Trigger a rotation angle reading
void RasTriggerReading()
{
    // Trigger the sampling
    ADCProcessorTrigger(ADC0_BASE, 1 /* sequencer*/ );
}

/* Read the current input from the rotation angle sensor*/

int RasDataRead()
{
    rotary_angle_sensor.new_input = false;


    /*
     * convert from digital to analog,
     * scale degrees to voltage,
     * reverse direction so clockwise is positive,
     * then scale by 10 to include digit in the tenths places,
     * then cast to int while including the tenths place digit
    */
    return (int)((180 - (180/3.3 * (3.3 * (float) rotary_angle_sensor.raw_data / 4096)))*10);
}





