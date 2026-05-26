
        .global Seg7DecomposeInt

        .text

; void Seg7DecomposeInt(int value, uint8_t *digits)

;   digits[0] = value        % 10   (ones)
;   digits[1] = (value/10)   % 10   (tens)
;   digits[2] = (value/100)  % 10   (hundreds)
;   digits[3] = (value/1000) % 10   (thousands)

; r0 = value   (arg 1)
; r1 = digits  (arg 2, pointer to 4-byte array)

Seg7DecomposeInt
        .asmfunc
        PUSH    {r4, lr}
        MOV     r2, #10

        ; digit[0] = value % 10
        UDIV    r3, r0, r2      ; r3 = value / 10
        MUL     r4, r3, r2      ; r4 = (value/10) * 10
        SUB     r4, r0, r4      ; r4 = value - (value/10) * 10  = value % 10
        STRB    r4, [r1, #0]    ; store into digits[0]
        MOV     r0, r3          ; value = value / 10 for next pass

        ; digit[1] = (value/10) % 10
        UDIV    r3, r0, r2
        MUL     r4, r3, r2
        SUB     r4, r0, r4
        STRB    r4, [r1, #1]
        MOV     r0, r3

        ; digit[2] = (value/100) % 10
        UDIV    r3, r0, r2
        MUL     r4, r3, r2
        SUB     r4, r0, r4
        STRB    r4, [r1, #2]
        MOV     r0, r3

        ; digit[3] = (value/1000) % 10
        UDIV    r3, r0, r2
        MUL     r4, r3, r2
        SUB     r4, r0, r4
        STRB    r4, [r1, #3]

        POP     {r4, pc}        ; restore r4 + return
        .endasmfunc
