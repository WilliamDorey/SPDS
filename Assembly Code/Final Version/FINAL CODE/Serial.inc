; Serial.inc
;
; Suboutines used for serial communication using
; the Atmega8515's USART functionality
;

; Important configuration values
.EQU BAUD = 25
.EQU UTCLB = $18
.EQU FRAME = $86

;
; Subroutine used to initialize the UART
; functionality of the Atmega8515 microcontroller
;
Serial_init:
		; Sets the baud rate
		LDI R16, $00
		OUT UBRRH, R16
		LDI R16, BAUD
		OUT UBRRL, R16
		; Sets the control and status
		LDI R16, UTCLB
		OUT UCSRB, R16
		; Sets the frame properties
		LDI R16, FRAME
		OUT UCSRC, R16
		RET

;
; Subroutine used to recieve a single byte of data
; through USART on the Atmega8515 microcontroller
;
Serial_get:
		IN R18, UCSRA
		ANDI R18, $80
		BREQ Serial_get
		IN R18, UDR
		RET

;
; Subroutine used to transmit a single byte of data
; through USART on the Atmega8515 microcontroller
;
Serial_send:
		OUT UDR, R18
Serial_wait:		; wait for a bit confirming reception
		IN R18, UCSRA
		CPI R18, $20
		BREQ Serial_wait
		RET

;
; Subroutine used to reliably send and recieve data
; between the Atmega8515 microcontroller and a 
; Raspberry Pi using a TCP-like style of communication
;
simple_msg:
		LDI R18, $31
		RCALL Serial_send
		RCALL Serial_get
ready:
		LDI R18, $31
		RCALL Serial_send
		RCALL Serial_get
		RET

; End of Serial.inc