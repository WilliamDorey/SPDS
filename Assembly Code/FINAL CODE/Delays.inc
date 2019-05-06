; Delays.inc

;
; The subroutines each load their required
; loop counts and then jump to the loop
;
delay_37us:
		PUSH R27
		PUSH R26
		LDI R26, $06
		LDI R27, $00
		RJMP delay_loop

delay_1ms:
		PUSH R27
		PUSH R26
		LDI R26, $C8
		LDI R27, $00
		RJMP delay_loop

delay_1_52ms:
		PUSH R27
		PUSH R26
		LDI R26, $30
		LDI R27, $01
		RJMP delay_loop

delay_5ms:
		PUSH R27
		PUSH R26
		LDI R26, $6F
		LDI R27, $02
		RJMP delay_loop

delay_40ms:
		PUSH R27
		PUSH R26
		LDI R26, $40
		LDI R27, $1F
		RJMP delay_loop

delay_loop:
		SBIW X, 1
		NOP
		BRNE delay_loop
		POP R26
		POP R27
		RET

; Longer dalays that require an additional register
; for loop counts
delay_5s:
		PUSH R28
		PUSH R27
		PUSH R26
		LDI  R26, $40
		LDI  R27, $42
		LDI  R28, $10
		RJMP delay_extended_loop

delay_2s:
		PUSH R28
		PUSH R27
		PUSH R26
		LDI  R26, $80
		LDI  R27, $1A
		LDI  R28, $07
		RJMP delay_extended_loop

delay_extended_loop:
		SBIW X, 1
		NOP
		BRNE delay_extended_loop
		DEC  R28
		BRNE delay_extended_loop
		POP R26
		POP R27
		POP R28
		RET

; End of Delays.inc