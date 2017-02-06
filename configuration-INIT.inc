;**********************************************************************
;**********************************************************************
;configuration-INIT.inc
;**********************************************************************
;**********************************************************************

;**********************************************************************
; GENERAL CONFIGURATION SETINGS
;**********************************************************************
	; If an interrupt occurs during the execution of the instruction to disable the interrupts (bcf GIE)
	; the PIC could still sjump to the interrupt service routine. Upon returning with RETFIE,
	; the GIE flag will get set again. We need to verify the GIE flag remains cleared.
	clrf	INTCON			; disable all interrupts
	btfsc	INTCON, GIE		; check if GIE is still disabled
	goto	start			; if not yet disable, keep trying

	; mask all peripheral interrupts
	clrf	PIE1
	clrf	PIE2 ; bit PIE2,C2IE is for comparator 2

	;clear all peripheral interrupt flags
	banksel	PIR1			;bank 0
	clrf	PIR1			
	clrf	PIR2

	;set internal oscillators at 4 MHz
	banksel	OSCCON
	movlw	61h		;Sets internal oscilator for clock at 4 MHz (default)	
	movwf	OSCCON 

	;set initially all analog pins as digital I/O
	banksel	ANSEL			
	clrf	ANSEL		;Set ports ANS0-7 to digital
	clrf	ANSELH		;Set ports ANS8-11 to digital

;************************************************************************************************* 
