;
; main.asm
;
; Author : William Dorey
;

;
; This is the main Assembly code file for 
; the SPDS. This unit controls the locking
; mechanism of the unit as well as the
; monitoring of the weight for contents
; placed in the unit. Information is
; communicated to a Raspberry Pi server
; using UART serial transmission.
;

; Data 
.dseg
pass_code:	.byte 6
.ORG $100
pass_atmp:	.byte 6

; Code
.cseg
.INCLUDE "m8515def.inc"

reset:	RJMP init
		RJMP isr0
		.org $1E

; Main initialization sequence start
init:
		; Stack pointer to allow for subroutines
		LDI R16, LOW(RAMEND)
		OUT SPL, R16
		LDI R16, HIGH(RAMEND)
		OUT SPH, R16

		; Selecting interupts to enable
		LDI R16, (1<<INT0)
		OUT GICR, R16

		; Bus and Interrupt initialization
		LDI R16, $82
		OUT MCUCR, R16

		; Sets Solenoid and kickstarts ADC
		LDI R16, $FF
		OUT DDRB, R16
		STS $1000, R16
		LDI R16, $00
		OUT PORTB, R16

		; LCD and Serial communications
		RCALL Serial_init
		RCALL LCD_init


		; Display banner and Checksum
		LDI R25, 9
		LDI R30, LOW(BANR<<1)
		LDI R31, HIGH(BANR<<1)
		RCALL LCD_print
		LDI R16, $C0
		STS LCD_CON, R16
		LDI R25, 9
		RCALL LCD_print

		RCALL default_pass
			
		RCALL Gen_Check
		RCALL delay_2s
		RCALL LCD_rst
; End of main intialization sequence
		; Enable interupt signal
		SEI

		LDI R25, 16
		LDI R30, LOW(PROMPT<<1)
		LDI R31, HIGH(PROMPT<<1)
		RCALL LCD_print

wait:	; Wait for a signal from server
		; to either set a new passcode
		; or to obtain a value from the ADC
		RCALL Serial_get

		CPI R18, 'W'
		BRNE skip0
		RCALL Gen_ADC

skip0:
		CPI R18, 'S'
		BRNE fini
		RCALL Gen_set_pass

fini:	; Return to waiting for a signal
		; from the Rapsberry Pi server
		RJMP wait

;
; Interupt subroutine that gegins when a value
; is made available by the keypad module
;
isr0:
		PUSH R16
		LDS R16, $1000
		RCALL Key_map
		;Check if there is an active attempt
		CPI R22, $01
		BREQ attempt

		; The start of a new Passcode Attempt
		CPI  R16, '*'
		BRNE isr0_end
		RCALL LCD_rst
		LDI R25, 15
		LDI R30, LOW(PASS<<1)
		LDI R31, HIGH(PASS<<1)
		RCALL LCD_print
		LDI R16, $C0
		STS LCD_CON, R16
		
		RCALL delay_1_52ms
		LPM R16, Z
		STS LCD_OUT, R16 
		; Load the first location of the
		; passcode attempt data
		LDI R26, LOW(pass_atmp)
		LDI R27, HIGH(pass_atmp)
		LDI R22, $01
		RJMP isr0_end

attempt:	; continue an active passcode
			; attempt unless the character
			; is a '#', in which case, end
			; the attempt
		CPI R16, '#'
		BREQ stop
		ST X+, R16
		STS LCD_OUT, R16
		INC R23

isr0_end:		
		POP R16
		RETI


;End a Passcode Attempt
stop:
		CLR R22
		RCALL Gen_code_check
		RJMP isr0_end


; Patterns
BANR:	.db	"SPDS V2.0Checksum "
PROMPT:	.db	"Press * to Begin"
PASS:	.db	"Enter Passcode:>"
GOOD:	.db	"GOOD Unlock!"
BAD:	.db	"BAD Attempt!"

; List of available Subroutines and their respective files
.include	"General.inc"	; Gen_Check,hex2asc,ADC,unlock,code_check
.include	"Keypad.inc"	; Key_map
.include	"LCD.inc"		; LCD_init,rst,print
.include	"Delays.inc"	; delay_37us,1ms,1_52ms,5ms,40ms,2s,5s
.include	"Serial.inc"	; Serial_init,get,send

; Marker for end of code
CHKSUM:	.db $00,$00

; End of main.asm