; General.inc

;
; Various routines for miscelaneous uses
; that are not for any specific module of
; the embedded unit
;

;
; Subroutine to generate a Checksum of the
; microcontroller's cseg and then display
; it on the LCD
;
Gen_Check:
		LDI R30, LOW(CHKSUM<<1)
		LDI R31, HIGH(CHKSUM<<1)
		MOV R14, R30
		MOV R15, R31
		CLR R30
		CLR R31
		CLR R18
		CLR R19
		CLR R20
		CLR R21
addvalues:
		LPM R16, Z+
		ADD R18, R16
		ADC R19, R21
		ADC R20, R21
		CP  R30, R14
		BRNE addvalues
		CP  R31, R15
		BRNE addvalues
ChkSum_disp:
		MOV R16, R20
		RCALL Gen_hex2asc
		RCALL delay_1ms
		STS LCD_OUT, R16
		RCALL delay_1ms
		STS LCD_OUT, R17
		MOV R16, R19
		RCALL Gen_hex2asc
		RCALL delay_1ms
		STS LCD_OUT, R16
		RCALL delay_1ms
		STS LCD_OUT, R17
		MOV R16, R18
		RCALL Gen_hex2asc
		RCALL delay_1ms
		STS LCD_OUT, R16
		RCALL delay_1ms
		STS LCD_OUT, R17
		RET

;
; This routine converts the value of R16
; into ASCII text for either transmission
; using USART or display on the LCD
;
Gen_hex2asc:
		CLR R14
		MOV R15, R16
		LSR R16
		LSR R16
		LSR R16
		LSR R16
asc_chk:
		CPI R16, $0A
		BRLO number
letter:
		SUBI R16, $09
		LDI R18, $40
		ADD R16, R18
		RJMP asc_done
number:
		LDI R18, $30
		ADD R16, R18
		RJMP asc_done
next_byte:
		MOV R17, R16
		MOV R16, R15
		ANDI R16, $0F
		RJMP asc_chk
asc_done:
		INC R14
		LDI R18, 2
		CP R14, R18
		BRNE next_byte
		RET

;
; Subroutine to pull a value from the ADC
; and then send the value through USART to
; the Raspberry Pi server
;
Gen_ADC:
		RCALL simple_msg
		LDS R16, $7000
		RCALL Gen_hex2asc
		RCALL Serial_get
		MOV R18, R17
		RCALL Serial_send
		NOP
		RCALL Serial_get
		MOV R18, R16
		RCALL Serial_send
		RET

;
; Subroutine to activate the solonoid, unlocking
; the SPDS for 5 seconds
;
Gen_unlock:
		PUSH R16
		PUSH R17
		LDI R16, $01
		OUT PORTB, R16
		RCALL delay_5s
		CLR R16
		OUT PORTB, R16
		POP R17
		POP R16
		RET

;
; Subroutine to set the default passcode of
; '******' upon startup after powerfailure
;
default_pass:
		LDI R16, '*'
		LDI R29, HIGH(pass_code)
		LDI R28, LOW(pass_code)
		ST  Y+, R16
		ST  Y+, R16
		ST  Y+, R16
		ST  Y+, R16
		ST  Y+, R16
		ST  Y+, R16
		RET
;
; Subroutine to set a new passcode by retrieving
; the values from the Raspberry Pi server and
; storing them in the data segment
;
Gen_set_pass:
		RCALL simple_msg
		LDI R29, HIGH(pass_code)
		LDI R28, LOW(pass_code)
		LDI R16, 6
Gen_set_pass_loop:
		RCALL Serial_get
		ST Y+, R18
		RCALL Serial_send
		DEC R16
		BRNE Gen_set_pass_loop
		RET

;
; Subroutine to check an attempted password
; against the one stored in the data segment
;
Gen_code_check:
		CPI R23, 6
		BRNE bad_attempt

		LDI R29, HIGH(pass_code)
		LDI R28, LOW(pass_code)
		LDI R27, HIGH(pass_atmp)
		LDI R26, LOW(pass_atmp)

Gen_code_check_loop:
		LD R16, X+
		LD R17, Y+
		CP  R17, R16
		BRNE bad_attempt

		DEC R23
		BRNE Gen_code_check_loop

good_attmept:
		RCALL LCD_rst
		LDI R25, 12
		LDI R30, LOW(GOOD<<1)
		LDI R31, HIGH(GOOD<<1)
		RCALL LCD_print
		RCALL Gen_unlock
		RJMP Gen_code_check_end	

bad_attempt:
		RCALL LCD_rst
		LDI R25, 12
		LDI R30, LOW(BAD<<1)
		LDI R31, HIGH(BAD<<1)
		RCALL LCD_print
		RCALL delay_2s

Gen_code_check_end:
		RCALL LCD_rst
		LDI R25, 16
		LDI R30, LOW(PROMPT<<1)
		LDI R31, HIGH(PROMPT<<1)
		RCALL LCD_print
		CLR R23
		RET

; End of General.inc