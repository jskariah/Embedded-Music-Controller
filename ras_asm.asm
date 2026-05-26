		.cdecls "ras.h"


		; Reference to RAS State Object in "ras.c"
		.ref	rotary_angle_sensor
		; Struct:
		; 	typedef struct {
		;		Event *callback_event;
		;		uint32_t raw_data;
		;		bool new_input;
		;	} RotaryAngleSensorState
		; [REF]: callback_event
		; {REF}: 4 bytes, 4 bytes, 1 byte



		; *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***



		.text
		; Field Pointers to ADC and RAS
_rotary_angle_sensor    .field		rotary_angle_sensor
_ADC0_BASE      		.field  	ADC0_BASE


RotaryAngleSensorISR
		.asmfunc
		PUSH	{LR}; save link address


		; Read the ADC Data using TivaWare ADCSequenceDataGet
		LDR		r0,	_ADC0_BASE			; (which) base
		MOV		r1, #1					; (which) sequence
		LDR		r2,	_rotary_angle_sensor; RAS State Object (-> callback_event)
		ADD		r2, #4					; RAS State Object (-> raw_data)
		BL		ADCSequenceDataGet		; ... gets the data in ADC Sequence #1 => r0 = *ADC0 sequence 1 data*

		; Update the new input flag based on the ADC Data in r0
		LDR		r0,	_rotary_angle_sensor; RAS State Object (-> callback_event)
		MOV		r1, #true				; update to true every time a call occurs
		STRB	r1, [r0, #8]			; store update => rotary_angle_sensor.new_input

		; Schedule a callback event for the current time (TivaWare EventGetCurrentTime) using Util EventSchedule
		BL		EventGetCurrentTime		; ... r0 = *Current time for event*
		MOV		r1,	r0					; param #2 = r1 = *time*
		LDR		r0,	_rotary_angle_sensor; RAS State Object (-> callback_event)
		LDR		r0, [r0]				; param #1 = r0 = *callback event*
		BL		EventSchedule			; ... schedule the update for the callback event at this time

		; Clear the Interrupt Flag using TivaWare ADCIntClear
		LDR		r0,	_ADC0_BASE			; (which) base
		MOV		r1,	#1					; (which) sequence
		BL		ADCIntClear				; clear the interrupt flag before exiting to allow for more interrupts.


		POP		{PC}; return to linked
		.endasmfunc
