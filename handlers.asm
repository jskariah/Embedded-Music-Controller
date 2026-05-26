;
;
;
;
; DIRECTIVES
; Includes
	.cdecls "handlers_asm.h"


; Declarations

MODE_TONE   	.equ  0
MODE_TRACK   	.equ  1
MODE_TUNING   	.equ  2
MODE_OCTAVE   	.equ  3
MODE_VOLUME   	.equ  4
MODE_SPEED   	.equ  5
MODE_CTL_NUM   	.equ  6

; References
	; Objects
	.ref buzzer_sys
	; Events
	.ref display_update_event

;
;
;
;
; DATA
	.data


;
;
;
;
; MAIN CODE
	.text

; Pointers
_buzzer_sys				.field	buzzer_sys
_display_update_event	.field	display_update_event


	.global UpdateDisplay2
UpdateDisplay2
				.asmfunc
				LDR	r0, _buzzer_sys
				LDR r1, [r0]

				CMP	r1, #MODE_CTL_NUM
				BHS		schedule_display

				LDR r2, [r0, r1, LSL #2]
				MOV r0, r2

				TEQ r1, #MODE_TUNING
				ITE 	EQ
				BLEQ	Seg7DisplaySigned
				BLNE	Seg7DisplayInt


				;LDR	r1, _jump_table_MODE
				;LSL	r0, r0, #2
				;LDR r2, [r1,r0]
				;BX	r2


				;
schedule_display
				;BL	EventGetCurrentTime
				;ADD	r1, r0, #100
				;LDR	r0, _display_update_event
				;BL	EventSchedule; Schedule an display_update_event in 100 ms
				;


				BX	lr
				.endasmfunc
